/*====================================================
1.1 - 2022/4/12
	Late precache models before set model to prevent crash. Thanks to "CosmicD" for reporting.
1.0
	- Initial release
======================================================*/
#pragma newdecls required

#include <sdktools>
#include <sdkhooks>
#include <sourcemod>
#include <dhooks>
#include <left4dhooks>

// iRoundState Flags
#define TRANSITIONED_MAP		(1<<0)
#define TRANSITION_CHANGELEVEL	(1<<1)
#define TRANSITING				(1<<2)

int m_strNextMap, m_strLandmarkName, iRoundState, m_Patch
Address pTerrorNavMesh, pStartChangelevel
GlobalForward hOnEntityRestoringPreSpawn, hOnEntityRestoringPostSpawn, hOnEntityTransitioning
Handle hGetInitialCheckpoint, hGetLastCheckpoint, hStartChangeLevel
Handle hDetour_ChangeLevelNow
ArrayList hPatch, hPatchOrigin
//bool IsL4D2
ConVar hConVar_CfgFile

enum CheckpointType
{
	Checkpoint_Initial = 0,
	Checkpoint_Last
}

public Plugin myinfo = 
{
	name = "Customize Transition Entities",
	author = "IA/NanaNana",
	description = "Customize save entities for next level to spawn",
	version = "1.1",
	url = "https://forums.alliedmods.net/showthread.php?t=336896"
}

public APLRes AskPluginLoad2(Handle myself, bool late, char[]error, int err_max)
{
	CreateNative("IsEntityInCheckpoint", Native_IsEntityInCheckpoint);
	hOnEntityRestoringPreSpawn = new GlobalForward("OnEntityRestoringPreSpawn", ET_Ignore, Param_Cell, Param_Cell);
	hOnEntityRestoringPostSpawn = new GlobalForward("OnEntityRestoringPostSpawn", ET_Ignore, Param_Cell, Param_Cell);
	hOnEntityTransitioning = new GlobalForward("OnEntityTransitioning", ET_Event, Param_Cell, Param_Cell);
}

public void OnPluginStart()
{
	hPatch = new ArrayList(), hPatchOrigin = new ArrayList()
	Handle h = LoadGameConfigFile("l4d_customize_transition_entities")

	pStartChangelevel = GameConfGetAddress(h, "StartChangelevel")
	
	m_strNextMap = GameConfGetOffset(h, "InfoChangeLevel::m_strNextMap")
	m_strLandmarkName = GameConfGetOffset(h, "InfoChangeLevel::m_strLandmarkName")
	m_Patch = GameConfGetOffset(h, "InfoChangeLevel::StartChangeLevel_Patch")
	
	hGetInitialCheckpoint = CreateSDKCall(h, "TerrorNavMesh::GetInitialCheckpoint")
	hGetLastCheckpoint = CreateSDKCall(h, "TerrorNavMesh::GetLastCheckpoint")
	
	StartPrepSDKCall(SDKCall_Entity);
	PrepSDKCall_SetFromConf(h, SDKConf_Signature, "InfoChangelevel::StartChangeLevel");
	PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain);
	if(!(hStartChangeLevel = EndPrepSDKCall())) SetFailState("sig \"InfoChangelevel::StartChangeLevel\" invalid.")
	
	if(!DHookSetFromConf((hDetour_ChangeLevelNow = DHookCreateDetour(Address_Null, CallConv_THISCALL, ReturnType_Void, ThisPointer_CBaseEntity)), h, SDKConf_Signature, "InfoChangelevel::ChangeLevelNow"))
		SetFailState("Detour \"InfoChangelevel::ChangeLevelNow\" invalid.");
	
	Address p = pStartChangelevel+view_as<Address>(m_Patch)
	int j, x, y
	char s[60]
	GameConfGetKeyValue(h, "StartChangeLevel_Patch", s, sizeof(s));
	while(strlen(s) > j)
	{
		if((x = CharToUpper(s[j])-48)>9) x-=7
		if((y = CharToUpper(s[j+1])-48)>9) y-=7
		hPatchOrigin.Push(LoadFromAddress(p, NumberType_Int8))
		hPatch.Push(x*16+y)
		j += 3
	}
	
	CloseHandle(h)
	
	HookEvent("round_start", round_start, EventHookMode_PostNoCopy);
	HookEvent("player_team", player_team);
	
	RegAdminCmd("sm_transition", Cmd_transition, ADMFLAG_ROOT, "Start transition change level immediately.");
	
	//IsL4D2 = (GetEngineVersion() == Engine_Left4Dead2)
	
	Enable(true)
	HookConVarChange(CreateConVar("l4d_customize_transition_entities", "1", "Enable the plugin.", 0, true, _, true, 1.0), Hook_ConVar);
	hConVar_CfgFile = CreateConVar("l4d_customize_transition_entities_config", "addons/sourcemod/data/l4d_customize_transition_entities.cfg", "Config file for entities and data to save.")
	AutoExecConfig(true, "l4d_customize_transition_entities")
}

public Action Cmd_transition(int client, int args)
{
	int i = SDKCall(hGetLastCheckpoint, pTerrorNavMesh), e = FindEntityByClassname(-1, "info_changelevel")
	if(i && e != -1) SDKCall(hStartChangeLevel, e, i)
}
public void OnAllPluginsLoaded()
{
	pTerrorNavMesh = L4D_GetPointer(POINTER_NAVMESH)
}

public void OnPluginEnd()
{
	Enable(false)
}

void Hook_ConVar(Handle convar, const char[]oldValue, const char[]newValue)
{
	Enable(StringToInt(newValue) == 1)
}

void Enable(bool b)
{
	Address p = pStartChangelevel+view_as<Address>(m_Patch)
	for(int i=0;i<hPatch.Length;i++)
	{
		StoreToAddress(p++, (b?hPatch:hPatchOrigin).Get(i), NumberType_Int8)
	}
	if(b) DHookEnableDetour(hDetour_ChangeLevelNow, false, DH_ChangeLevelNow)
	else DHookDisableDetour(hDetour_ChangeLevelNow, false, DH_ChangeLevelNow)
}

void RestoreEntityData(int i, KeyValues h, const char[]spawn)
{
	PropFieldType type
	int offset
	float f[3]
	char s[128]
	if(h.JumpToKey("Offsets") && h.JumpToKey(spawn) && h.GotoFirstSubKey())
	{
		char m[64]
		do
		{
			h.GetSectionName(m, sizeof(m))
			offset = StringToInt(m)
			type = view_as<PropFieldType>(h.GetNum("type", -1))
			switch(type)
			{
				case PropField_Integer: SetEntData(i, offset, h.GetNum("Value"), h.GetNum("byte", 4), true)
				case PropField_Float: SetEntDataFloat(i, offset, h.GetFloat("Value"), true)
				case PropField_Entity: SetEntDataEnt2(i, offset, h.GetNum("Value"), true)
				case PropField_Vector:
				{
					h.GetVector("Value", f)
					SetEntDataVector(i, offset, f, true)
				}
				case PropField_String: 
				{
					h.GetString("Value", s, sizeof(s))
					SetEntDataString(i, offset, s, strlen(s), true)
				}
			}
		}while(h.GotoNextKey())
	}
	h.Rewind()
}

public Action RestoreTransitionEntities(Handle hTimer)
{
	char m[64], s[128]
	GetCurrentMap(m, 64)
	KeyValues hSaveEntities = new KeyValues(m), h, hKvConfig = GetConfig()
	
	BuildPath(Path_SM, s, sizeof(s), "data/save_entities")
	Format(s, sizeof(s), "%s/%s.txt", s, m)
	hSaveEntities.ImportFromFile(s)
	int i, l = GetMaxEntities()
	bool b
	/*ArrayList p = new ArrayList(64)
	
	if(hSaveEntities.JumpToKey("Filter") && hSaveEntities.GotoFirstSubKey(false))
	{
		do
		{
			hSaveEntities.GetString(NULL_STRING, m, sizeof(m))
			p.PushString(m)
		}while(hSaveEntities.GotoNextKey(false))
		hSaveEntities.Rewind()
	}*/
	
	PrintToServer("[Customize Transition] Start restoring entities.")
	for(i = 33;i<=l;i++)
	{
		if(IsValidEntity(i) && IsInList(i, hKvConfig, "RemoveList") && sIsEntityInCheckpoint(i, Checkpoint_Initial))
		{
			GetEdictClassname(i, s, sizeof(s))
			PrintToServer("Removing %s", s)
			AcceptEntityInput(i, "Kill")
		}
	}
	hKvConfig.Close()
	float f[3], z[3], F[3], g[3], v[3]
	if(hSaveEntities.JumpToKey("Landmark"))
	{
		hSaveEntities.GetString("Name", m, sizeof(m))
		b = strcmp(m, "coldstream3_coldstream4") == 0
		i = -1
		while((i = FindEntityByClassname(i, "info_landmark")) != -1)
		{
			GetEntPropString(i, Prop_Data, "m_iName", s, sizeof(s))
			if(!strcmp(s, m))
			{
				GetEntPropVector(i, Prop_Data, "m_vecAbsOrigin", z)
				break
			}
		}
		hSaveEntities.GetVector("pos", f)
		hSaveEntities.GoBack()
	}
	if(hSaveEntities.JumpToKey("SaveEntities") && hSaveEntities.GotoFirstSubKey())
	{
		do
		{
			hSaveEntities.GetSectionName(m, sizeof(m))
			h = new KeyValues(m)
			h.Import(hSaveEntities)
			h.GetString("classname", m, sizeof(m))
			i = CreateEntityByName(m)
			h.GetString("model", s, sizeof(s))
			PrecacheModel(s)
			SetEntityModel(i, s)
			h.GetVector("pos", F)
			SubtractVectors(z, f, g)
			AddVectors(F, g, F)
			h.GetVector("angles", g)
			if(b)
			{
				F[0] = z[0] - (F[0] - z[0]);
				F[1] = z[1] - (F[1] - z[1]);
				g[1] += 180.0;
			}
			h.GetVector("vel", v)
			
			//F[2] = z[2] + (F[2] - z[2]);
			
			TeleportEntity(i, F, g, v)
			PrintToServer("Restoring %s at (%f %f %f)", m, F[0], F[1], F[2])
			//else if(FindDataMapInfo(i, "m_weaponID") != -1) SetEntProp(i, Prop_Data, "m_weaponID", h.GetNum("weaponID")) 
			
			/*if(h.JumpToKey("Key") && h.GotoFirstSubKey(false))
			{
				do
				{
					h.GetSectionName(m, 64)
					h.GetString(NULL_STRING, s, sizeof(s))
					DispatchKeyValue(i, m, s)
				}while(h.GotoNextKey(false))
				h.GoBack(), h.GoBack()
			}
			if(IsWeaponSpawn(i)) SetEntProp(i, Prop_Data, "m_weaponID", h.GetNum("weaponID"))*/
			
			RestoreEntityData(i, h, "PreSpawn")
		
			Call_StartForward(hOnEntityRestoringPreSpawn);
			Call_PushCell(i);
			Call_PushCell(h);
			Call_Finish();
			DispatchSpawn(i)
			h.Rewind()
			/*SetEntProp(i, Prop_Data, "m_MoveType", h.GetNum("moveTpye"))
			if(FindDataMapInfo(i, "m_iPrimaryAmmoType") != -1 && !IsWeaponMelee(i))
			{
				SetEntProp(i, Prop_Send, "m_iClip1", h.GetNum("currentMagazine"))
				SetEntProp(i, Prop_Send, "m_iExtraPrimaryAmmo", h.GetNum("extraAmmo"))
				if(IsL4D2 && IsWeaponGun(i))
				{
					SetEntProp(i, Prop_Send, "m_upgradeBitVec", h.GetNum("upgradeBitVec"))
					SetEntProp(i, Prop_Send, "m_nUpgradedPrimaryAmmoLoaded", h.GetNum("upgradeAmmo"))
				}
			}*/
			RestoreEntityData(i, h, "PostSpawn")
			
			Call_StartForward(hOnEntityRestoringPostSpawn);
			Call_PushCell(i);
			Call_PushCell(h);
			Call_Finish();
			h.Close()
		}while(hSaveEntities.GotoNextKey())
		hSaveEntities.GoBack(), hSaveEntities.GoBack()
	}
	PrintToServer("[Customize Transition] End restoring entities.")
	hSaveEntities.Close()
}

MRESReturn DH_ChangeLevelNow(int iInfo)
{
	if(L4D_HasPlayerControlledZombies()) return
	//if(hSaveEntities) hSaveEntities.Close()
	KeyValues hSaveEntities = new KeyValues("SaveEntities"), hSavedEntity, hKvConfig = GetConfig()
	

	//SDKCall(hSaveEntities, FindEntity ByClassname(-1, "info_changelevel"))
	char s[128], c[40]
	int i = -1, j
	float f[3]
	// -------- Landmark
	hSaveEntities.JumpToKey("Landmark", true)
	GetEntDataString(iInfo, m_strLandmarkName, c, sizeof(c))
	hSaveEntities.SetString("Name", c)
	while((i = FindEntityByClassname(i, "info_landmark")) != -1)
	{
		GetEntPropString(i, Prop_Data, "m_iName", s, sizeof(s))
		if(!strcmp(s, c))
		{
			GetEntPropVector(i, Prop_Data, "m_vecAbsOrigin", f)
			hSaveEntities.SetVector("Pos", f)
			break
		}
	}
	hSaveEntities.GoBack()
	
	// -------- Filter
	/*ArrayList p = new ArrayList(64)
	if(hKvConfig.GotoFirstSubKey(false))
	{
		hSaveEntities.JumpToKey("Filter", true)
		do
		{
			hKvConfig.GetSectionName(c, sizeof(c))
			p.PushString(c)
			IntToString(i++, s, sizeof(s))
			hSaveEntities.SetString(s, c)
		}while(hKvConfig.GotoNextKey(false))
		hKvConfig.Rewind()
		hSaveEntities.GoBack()
	}*/
	
	// -------- SaveEntities
	hSaveEntities.JumpToKey("SaveEntities", true)
	
	Action x
	PrintToServer("[Customize Transition] Start saving entities.")
	for(i=33;i<=GetMaxEntities();i++)
	{
		if(!IsValidEntity(i) || !IsInList(i, hKvConfig, "SaveList") || !sIsEntityInCheckpoint(i, Checkpoint_Last)) continue
		GetEdictClassname(i, c, sizeof(c))
		IntToString(j++, s, sizeof(s))
		hSaveEntities.JumpToKey(s, true)
		hSavedEntity = new KeyValues(s)
		
		hSavedEntity.SetString("classname", c)
		GetEntPropString(i, Prop_Data, "m_ModelName", s, sizeof(s))
		hSavedEntity.SetString("model", s)
		GetEntPropVector(i, Prop_Data, "m_vecAbsOrigin", f)
		hSavedEntity.SetVector("pos", f)
		PrintToServer("Saving %i.%s at (%f %f %f)", i, c, f[0], f[1], f[2])
		GetEntPropVector(i, Prop_Data, "m_angRotation", f)
		hSavedEntity.SetVector("angles", f)
		GetEntPropVector(i, Prop_Data, "m_vecVelocity", f)
		hSavedEntity.SetVector("vel", f)
		hSavedEntity.SetNum("moveTpye", GetEntProp(i, Prop_Data, "m_MoveType"))
		
		/*if(FindDataMapInfo(i, "m_iPrimaryAmmoType") != -1 && !IsWeaponMelee(i))
		{
			hSavedEntity.SetNum("currentMagazine", GetEntProp(i, Prop_Send, "m_iClip1"))
			hSavedEntity.SetNum("extraAmmo", GetEntProp(i, Prop_Data, "m_iExtraPrimaryAmmo"))
			if(IsL4D2 && IsWeaponGun(i))
			{
				hSavedEntity.SetNum("upgradeBitVec", GetEntProp(i, Prop_Send, "m_upgradeBitVec"))
				hSavedEntity.SetNum("upgradeAmmo", GetEntProp(i, Prop_Send, "m_nUpgradedPrimaryAmmoLoaded"))
			}
		}
		else if(IsWeaponSpawn(i)) hSavedEntity.SetNum("weaponID", GetEntProp(i, Prop_Data, "m_weaponID"))
		
		hSavedEntity.JumpToKey("Key", true)
		hSavedEntity.SetNum("skin", GetEntProp(i, Prop_Data, "m_nSkin"))
		if(IsWeaponMelee(i))
		{
			GetEntPropString(i, Prop_Data, "m_strMapSetScriptName", s, sizeof(s))
			hSavedEntity.SetString("melee_script_name", s)
		}
		else if(IsWeaponSpawn(i))
		{
			hSavedEntity.SetNum("count", GetEntProp(i, Prop_Data, "m_itemCount"))
			if(IsL4D2) hSavedEntity.SetNum("weaponskin", GetEntProp(i, Prop_Data, "m_nWeaponSkin"))
		}
		else if(IsMountedGun(i))
		{
			hSavedEntity.SetFloat("MaxYaw", GetEntPropFloat(i, Prop_Data, "m_maxYaw"))
			hSavedEntity.SetFloat("MaxPitch", GetEntPropFloat(i, Prop_Data, "m_maxPitch"))
			hSavedEntity.SetFloat("MinPitch", GetEntPropFloat(i, Prop_Data, "m_minPitch"))
		}
		hSavedEntity.GoBack()*/
		
		hKvConfig.Rewind()
		if(hKvConfig.JumpToKey("all"))
		{
			SaveSection(i, hSavedEntity, "PropData", "PreSpawn", hKvConfig)
			SaveSection(i, hSavedEntity, "Offsets", "PreSpawn", hKvConfig)
			SaveSection(i, hSavedEntity, "PropData", "PostSpawn", hKvConfig)
			SaveSection(i, hSavedEntity, "Offsets", "PostSpawn", hKvConfig)
			
			
			/*if(p.JumpToKey("Offsets") && p.GotoFirstSubKey(false))
			{
				hSavedEntity.JumpToKey("Offsets", true)
				do
				{
					p.GetSectionName(c, sizeof(c))
					p.GetString(NULL_STRING, s, sizeof(s))
					
				}while(p.GotoNextKey(false))
				p.GoBack(), p.GoBack()
			}*/
		}
		hKvConfig.Rewind()
		if(hKvConfig.JumpToKey("classname") && hKvConfig.JumpToKey(c))
		{
			SaveSection(i, hSavedEntity, "PropData", "PreSpawn", hKvConfig)
			SaveSection(i, hSavedEntity, "Offsets", "PreSpawn", hKvConfig)
			SaveSection(i, hSavedEntity, "PropData", "PostSpawn", hKvConfig)
			SaveSection(i, hSavedEntity, "Offsets", "PostSpawn", hKvConfig)
		}
		hKvConfig.Rewind()
		if(hKvConfig.JumpToKey("propname") && hKvConfig.GotoFirstSubKey())
		{
			do
			{
				hKvConfig.GetSectionName(c, sizeof(c))
				if(HasProp(i, c))
				{
					SaveSection(i, hSavedEntity, "PropData", "PreSpawn", hKvConfig)
					SaveSection(i, hSavedEntity, "Offsets", "PreSpawn", hKvConfig)
					SaveSection(i, hSavedEntity, "PropData", "PostSpawn", hKvConfig)
					SaveSection(i, hSavedEntity, "Offsets", "PostSpawn", hKvConfig)
				}
			}while(hKvConfig.GotoNextKey())
		}
		Call_StartForward(hOnEntityTransitioning);
		Call_PushCell(i);
		Call_PushCell(hSavedEntity);
		Call_Finish(x);
		if(x != Plugin_Handled)
		{
			hSavedEntity.Rewind()
			hSaveEntities.Import(hSavedEntity)
		}
		hSavedEntity.Close()
		hSaveEntities.GoBack()
	}
	PrintToServer("[Customize Transition] End saving entities.")
	hSaveEntities.Rewind()
	
	hKvConfig.Close()
	GetEntDataString(iInfo, m_strNextMap, c, sizeof(c))
	BuildPath(Path_SM, s, sizeof(s), "data/save_entities")
	CreateDirectory(s, 0x1FF);
	Format(s, sizeof(s), "%s/%s.txt", s, c)
	hSaveEntities.ExportToFile(s)
	hSaveEntities.Close()
	iRoundState |= TRANSITION_CHANGELEVEL|TRANSITIONED_MAP|TRANSITING
	//PrintToServer("[Customize Transition] Entities saved.")
}

public Action round_start(Handle event, const char[]name, bool dontBroadcast)
{
	if(iRoundState&TRANSITIONED_MAP && !(iRoundState&TRANSITING)) CreateTimer(0.1, RestoreTransitionEntities)
}
public Action player_team(Handle event, const char[]name, bool dontBroadcast)
{
	if(GetClientOfUserId(GetEventInt(event, "userid")) && GetEventInt(event, "team") == 2 && iRoundState&TRANSITING)
	{
		CreateTimer(0.1, RestoreTransitionEntities)
		iRoundState &=~TRANSITING
	}
}

public void OnMapEnd()
{
	if(iRoundState &TRANSITION_CHANGELEVEL) iRoundState &=~TRANSITION_CHANGELEVEL
	else iRoundState = 0
}

public int Native_IsEntityInCheckpoint(Handle plugin, int numParams)
{
	return sIsEntityInCheckpoint(GetNativeCell(1), GetNativeCell(2))
}

bool sIsEntityInCheckpoint(int entity, CheckpointType i)
{
	Address l
	switch(i)
	{
		case 0: l = SDKCall(hGetInitialCheckpoint, pTerrorNavMesh)
		case 1: l = SDKCall(hGetLastCheckpoint, pTerrorNavMesh)
	}
	if(!l) return false
	l += view_as<Address>(24)
	float f[3], F[3], o[3], p[3], q[3]
	f[0] = view_as<float>(LoadFromAddress(l, NumberType_Int32))-150.0
	f[1] = view_as<float>(LoadFromAddress(l+view_as<Address>(4), NumberType_Int32))-150.0
	f[2] = view_as<float>(LoadFromAddress(l+view_as<Address>(8), NumberType_Int32))-150.0
	F[0] = view_as<float>(LoadFromAddress(l+view_as<Address>(12), NumberType_Int32))+150.0
	F[1] = view_as<float>(LoadFromAddress(l+view_as<Address>(16), NumberType_Int32))+150.0
	F[2] = view_as<float>(LoadFromAddress(l+view_as<Address>(20), NumberType_Int32))+150.0
	//PrintToServer("%f %f %f %f %f %f", f[0], f[1], f[2], F[0], F[1], F[2])
	GetEntPropVector(entity, Prop_Send, "m_vecMins", o)
	GetEntPropVector(entity, Prop_Send, "m_vecMaxs", p)
	GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", q)
	AddVectors(o, q, o)
	AddVectors(p, q, p)
	return IsBoxIntersectingBox(f, F, o, p)
}

bool IsBoxIntersectingBox(float a1[3], float a2[3], float a3[3], float a4[3])
{
	return a1[0] <= a4[0] && a3[0] <= a2[0] && a1[1] <= a4[1] && a3[1] <= a2[1] && a1[2] <= a4[2] && a2[2] >= a3[2]
}

/*bool IsWeaponGun(int a)
{
	switch(GetEntProp(a, Prop_Data, "m_iPrimaryAmmoType"))
	{
		case 1,2,3,5,6,7,8,9,10,17: return true
	}
	return false
}
bool IsMountedGun(int a)
{
	return FindDataMapInfo(a, "m_maxYaw") != -1
}
bool IsWeaponMelee(int a)
{
	return FindDataMapInfo(a, "m_strMapSetScriptName") != -1
}
bool IsWeaponSpawn(int a)
{
	return FindDataMapInfo(a, "m_weaponID") != -1
}*/

Handle CreateSDKCall(Handle b, const char[]s)
{
	StartPrepSDKCall(SDKCall_Raw);
	PrepSDKCall_SetFromConf(b, SDKConf_Signature, s);
	PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain);
	Handle z = EndPrepSDKCall()
	if(!z) SetFailState("sig \"%s\" invalid.", s);
	return z
}

/*bool IsTransitionEntity(int i, ArrayList p)
{
	if(FindDataMapInfo(i, "m_iPrimaryAmmoType") != -1) return GetEntPropEnt(i, Prop_Data, "m_hOwner") == -1
	if(IsWeaponSpawn(i) || IsMountedGun(i)) return true
	char s[40]
	GetEdictClassname(i, s, 40)
	return (!strcmp(s, "prop_physics") || p.FindString(s) != -1)
}*/

bool IsInList(int i, KeyValues h, const char[]s)
{
	h.Rewind()
	if(!h.JumpToKey(s) || !h.GotoFirstSubKey(false)) return false
	char c[64], cls[64], d[64]
	GetEdictClassname(i, cls, 64)
	do
	{
		h.GetSectionName(c, sizeof(c))
		h.GetString(NULL_STRING, d, sizeof(c))
		if( ( (!strcmp(c, "classname", false) && !strcmp(cls, d)) || (!strcmp(c, "propname", false) && (FindDataMapInfo(i, d) != -1 || (GetEntityNetClass(i, c, sizeof(c)) && FindSendPropInfo(c, d) != -1) ) ) ) && (FindDataMapInfo(i, "m_hOwner") == -1 || GetEntPropEnt(i, Prop_Data, "m_hOwner") == -1) ) return true
	}while(h.GotoNextKey(false))
	return false
}
KeyValues GetConfig()
{
	char s[128]
	hConVar_CfgFile.GetString(s, sizeof(s))
	KeyValues k = new KeyValues("cfg")
	k.ImportFromFile(s)
	return k
}


void SaveOffsetData(int entity, int offset, PropFieldType t, int size, KeyValues hSavedEntity)
{
	hSavedEntity.SetNum("type", view_as<int>(t))
	switch(t)
	{
		case PropField_Integer: {
			hSavedEntity.SetNum("Value", GetEntData(entity, offset, size))
			hSavedEntity.SetNum("byte", size)
		}
		case PropField_Float: hSavedEntity.SetFloat("Value", GetEntDataFloat(entity, offset))
		case PropField_Entity: hSavedEntity.SetNum("Value", GetEntDataEnt2(entity, offset))
		case PropField_Vector:
		{
			float f[3]
			GetEntDataVector(entity, offset, f)
			hSavedEntity.SetVector("Value", f)
		}
		case PropField_String: 
		{
			char s[128]
			GetEntDataString(entity, offset, s, sizeof(s))
			hSavedEntity.SetString("Value", s)
		}
	}
}

void SaveSection(int i, KeyValues hSavedEntity, const char[]section, const char[]spawn, KeyValues h)
{
	if(!h.JumpToKey(section)) return
	if(h.JumpToKey(spawn) && h.GotoFirstSubKey(false))
	{
		hSavedEntity.JumpToKey("Offsets", true)
		hSavedEntity.JumpToKey(spawn, true)
		int size, offset
		char s[20], c[64]
		PropFieldType t
		do
		{
			h.GetSectionName(c, sizeof(c))
			if(section[0] == 'P')
			{
				if((offset = FindDataMapInfo(i, c, t, size)) == -1)
				{
					if(!GetEntityNetClass(i, s, sizeof(s)) || (offset = FindSendPropInfo(s, c, t, size)) == -1) continue
				}
				if(size != 1) size/=8
				offset += size*h.GetNum(NULL_STRING)
			}
			else if(section[0] == 'O')
			{
				h.GetString(NULL_STRING, s, sizeof(s))
				if(!strcmp(s, "float", false)) t = PropField_Float
				else if(!strcmp(s, "string", false)) t = PropField_String
				else if(!strcmp(s, "vector", false)) t = PropField_Vector
				else if(!strcmp(s, "entity", false)) t = PropField_Entity
				else
				{
					h.GetString("type", s, sizeof(s))
					if(!strcmp(s, "int", false))
					{
						t = PropField_Integer
						size = h.GetNum("byte", 4)
					}
					else continue
				}
				offset = StringToInt(c)
			}
			IntToString(offset, s, sizeof(s))
			hSavedEntity.JumpToKey(s, true)
			if(section[0] == 'P') hSavedEntity.SetString("propname", c)
			SaveOffsetData(i, offset, t, size, hSavedEntity)
			hSavedEntity.GoBack()
		}while(h.GotoNextKey(false))
		h.GoBack(), h.GoBack()
		hSavedEntity.Rewind()
	}
	h.GoBack()
}

bool HasProp(int i, const char[]c)
{
	if(FindDataMapInfo(i, c) != -1) return true
	char cls[64]
	return GetEntityNetClass(i, cls, sizeof(cls)) && FindSendPropInfo(cls, c) != -1
}

/*void RestorePropData(int i, const char[]c, KeyValues h)
{
	PropFieldType t
	int size, element = h.GetNum("element")
	PropType type = Prop_Data
	float f[3]
	char s[128]
	
	if(FindDataMapInfo(i, c, t, size) == -1)
	{
		if(!GetEntityNetClass(i, s, sizeof(s)) || FindSendPropInfo(s, c, t, size) == -1) return
		type = Prop_Send
	}
	switch(t)
	{
		case PropField_Integer:
		{
			if(size != 1) size /= 8
			SetEntProp(i, type, c, h.GetNum("Value"), size, element)
		}
		case PropField_Float: SetEntPropFloat(i, type, c, h.GetFloat("Value"), element)
		case PropField_Entity: SetEntPropEnt(i, type, c, h.GetNum("Value"), element)
		case PropField_Vector:
		{
			h.GetVector("Value", f)
			SetEntPropVector(i, type, c, f, element)
		}
		case PropField_String: 
		{
			h.GetString("Value", s, sizeof(s))
			SetEntPropString(i, type, c, s, element)
		}
	}
}*/

/*void SavePropData(int i, const char[]c, int element, KeyValues hSavedEntity)
{
	PropFieldType t
	int size
	PropType type = Prop_Data
	float f[3]
	char s[128]
	
	if(FindDataMapInfo(i, c, t, size) == -1)
	{
		if(!GetEntityNetClass(i, s, sizeof(s)) || FindSendPropInfo(s, c, t, size) == -1) return
		type = Prop_Send
	}
	hSavedEntity.JumpToKey(c, true)
	switch(t)
	{
		case PropField_Integer:
		{
			if(size != 1) size /= 8
			hSavedEntity.SetNum("Value", GetEntProp(i, type, c, size, element))
		}
		case PropField_Float: hSavedEntity.SetFloat("Value", GetEntPropFloat(i, type, c, element))
		case PropField_Entity: hSavedEntity.SetNum("Value", GetEntPropEnt(i, type, c, element))
		case PropField_Vector:
		{
			GetEntPropVector(i, type, c, f, element)
			hSavedEntity.SetVector("Value", f)
		}
		case PropField_String: 
		{
			GetEntPropString(i, type, c, s, sizeof(s), element)
			hSavedEntity.SetString("Value", s)
		}
	}
	hSavedEntity.SetNum("element", element)
	hSavedEntity.GoBack()
}*/