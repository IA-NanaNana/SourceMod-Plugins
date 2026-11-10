#include <sourcemod>
#include <dhooks>

// #define CONVAR_ENABLE

int iOS, iPatchOriValue[2]
Handle hGetMissionInfo, hKvGetString
StringMap hMissionPath, hMissionVpk
Address pPatch

public Plugin:myinfo =
{
	name = "Addon Script Filter",
	author = "IA/NanaNana",
	description = "Prohibited to load addon scripts that do not belong to the mission",
	version = "1.0",
	url = "https://steamcommunity.com/profiles/76561198291983872"
}
#if defined CONVAR_ENABLE
ConVar IA_addon_script_filter_reload_map
public OnConfigsExecuted()
{
	if(IA_addon_script_filter_reload_map.BoolValue)
	{
		static bool map_reloaded = false
		if(!map_reloaded)
		{
			CreateTimer(1.0, ChangeMapTimer)
			map_reloaded = true
			PrintToServer("[ASF] Reload map in 1s...")
		}
	}
}
Action ChangeMapTimer(Handle timer)
{
	char map[64]
	GetCurrentMap(map, sizeof map)
	return Plugin_Continue
} 
#endif

public OnAllPluginsLoaded()
{
	GameData h = LoadGameConfigFile("IA_addon_script_filter")
	if(!h)
		SetFailState("failed to load gamedata/l4d2_addon_script_filter.txt");
	
	iOS = h.GetOffset("Os")

	CreateDetourFromConf(h, "VScriptServerRunScript", DH_VScriptServerRunScript)
	CreateDetourFromConf(h, "V_FileBase", _, DH_V_FileBasePost)
	
	StartPrepSDKCall(SDKCall_Static);
	PrepSDKCall_SetFromConf(h, SDKConf_Signature, "CTerrorGameRules::GetMissionInfo")
	PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain)
	if(!(hGetMissionInfo = EndPrepSDKCall())) SetFailState("sigs CTerrorGameRules::GetMissionInfo invalid.");
	
	StartPrepSDKCall(SDKCall_Raw);
	PrepSDKCall_SetFromConf(h, SDKConf_Signature, "KeyValues::GetString")
	PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer);
	PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer);
	PrepSDKCall_SetReturnInfo(SDKType_String, SDKPass_Pointer)
	if(!(hKvGetString = EndPrepSDKCall())) SetFailState("sigs KeyValues::GetString invalid.");
	
	pPatch = h.GetMemSig("VScriptServerRunScriptForAllAddons")
	if(!pPatch) LogError("Can't get VScriptServerRunScriptForAllAddons address")
	else if(iOS)
	{
		pPatch += view_as<Address>(0xA5)
		if(LoadFromAddress(pPatch, NumberType_Int8) == 0xFF)
		{
			iPatchOriValue[0] = LoadFromAddress(pPatch, NumberType_Int32)
			StoreToAddress(pPatch, 0x90909090, NumberType_Int32)
			iPatchOriValue[1] = LoadFromAddress(pPatch, NumberType_Int16)
			StoreToAddress(pPatch+view_as<Address>(4), 0x9090, NumberType_Int16)
		}
		else LogError("VScriptServerRunScriptForAllAddons offset is invalid"), pPatch = Address_Null
	}
	else
	{
		pPatch += view_as<Address>(0xDD)
		if(LoadFromAddress(pPatch, NumberType_Int16) == 0x4489)
		{
			StoreToAddress(pPatch, 0x0EEB, NumberType_Int16)
		}
		else LogError("VScriptServerRunScriptForAllAddons offset is invalid"), pPatch = Address_Null
	}
	
	AddCommandListener(mission_reload, "mission_reload")
	
	ServerCommand("mission_reload"); // Need to reload the mission to get mission's vpk and path
	// ServerExecute();
	
	hMissionPath = new StringMap()
	hMissionVpk = new StringMap()
	
	h.Close()
	
	#if defined CONVAR_ENABLE
	IA_addon_script_filter_reload_map = CreateConVar("IA_addon_script_filter_reload_map", "0", "You may need to reload the map after this plugin is loaded to skip unnecessary scripts. This setting only takes effect once after the plugin finishes loading; if you have an alternative way to perform the reload, simply set the value to 0.", _, true, _, true, 1.0);
	AutoExecConfig(true, "IA_addon_script_filter")
	#endif
}
Action mission_reload(int client, const char[] command, int argc)
{
	hMissionPath.Clear()
	hMissionVpk.Clear()
	return Plugin_Continue
}

public OnPluginEnd()
{
	if(pPatch)
	{
		if(iOS)
		{
			StoreToAddress(pPatch, iPatchOriValue[0], NumberType_Int32)
			StoreToAddress(pPatch+view_as<Address>(4), iPatchOriValue[1], NumberType_Int16)
		}
		else StoreToAddress(pPatch, 0x4489, NumberType_Int16)
	}
}
MRESReturn DH_VScriptServerRunScript(DHookReturn hReturn, DHookParam hParams)
{
	char s[256]
	hParams.GetString(1, s, sizeof s)
	if(iOS) ReplaceString(s, sizeof s, "\\", "/")
	if(StrContains(s, "/addons/") == -1) return MRES_Ignored
	char copy[256]
	SplitString(s, "/scripts/", copy, sizeof copy)
	if(hMissionVpk.ContainsKey(copy))
	{
		char m[128], t[256]
		SDKCall(hKvGetString, SDKCall(hGetMissionInfo), m, sizeof m, "CfgFile", "");
		if(!hMissionPath.GetString(m, t, sizeof t) || strcmp(copy, t))
		{
			PrintToServer("[ASF] Skipping addon script %s", s)
			hReturn.Value = 0
			return MRES_Supercede
		}
	}
	PrintToServer("[ASF] Loading addon script %s", s) // DH_VScriptServerRunScript /root/l4d2_sv/left4dead2/addons/requiem_sv.vpk/scripts/vscripts/director_base_addon.nut L4D2C2
	//  PrintToServer("DH_VScriptServerRunScript %s %s", s, m) // DH_VScriptServerRunScript /root/l4d2_sv/left4dead2/addons/requiem_sv.vpk/scripts/vscripts/director_base_addon.nut L4D2C2
	return MRES_Ignored
}
MRESReturn DH_V_FileBasePost(DHookReturn hReturn, DHookParam hParams)
{
	char s[256], n[64]
	hParams.GetString(1, s, sizeof s)
	if(iOS) ReplaceString(s, sizeof s, "\\", "/")
	if(StrContains(s, "/addons/") == -1) return MRES_Ignored
	int i = StrContains(s, "/missions")
	if(i != -1)
	{
		strcopy(n, sizeof n, s[i+1])
		s[i] = 0
		// PrintToServer("\nMisson Path %s => %s\n", n, s)
		hMissionPath.SetString(n, s)
		hMissionVpk.SetValue(s, 1)
	}
	return MRES_Ignored
}

DynamicDetour CreateDetourFromConf(GameData h, const char[]s, DHookCallback pre=INVALID_FUNCTION, DHookCallback post=INVALID_FUNCTION)
{
	DynamicDetour z = DynamicDetour.FromConf(h, s)
	if(z)
	{
		if(pre != INVALID_FUNCTION) z.Enable(Hook_Pre, pre)
		if(post != INVALID_FUNCTION) z.Enable(Hook_Post, post)
	}
	else SetFailState("Detour %s invalid.", s);
	return z
}