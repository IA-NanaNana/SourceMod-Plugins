/*====================================================
1.0
	- Initial release
======================================================*/
#pragma newdecls required

#include <sdktools>
#include <sdkhooks>
#include <sourcemod>
#include <dhooks>

Handle hConVar

public Plugin myinfo = 
{
	name = "Independent Magnum Max Ammo",
	author = "IA/NanaNana",
	description = "Add ConVar 'ammo_magnum_max' to control magnum's ammo limitation",
	version = "1.0",
	url = "http://steamcommunity.com/profiles/76561198291983872"
}

public void OnPluginStart()
{
	hConVar = CreateConVar("ammo_magnum_max", "-2", "")

	Handle h = LoadGameConfigFile("l4d2_magnum_max_ammo"), z
	/*DHookSetFromConf((z = DHookCreateDetour(Address_Null, CallConv_THISCALL, ReturnType_Bool, ThisPointer_Address)), h, SDKConf_Signature, "CanCarryInfiniteAmmo")
	DHookAddParam(z, HookParamType_Int);
	DHookEnableDetour(z, true, DH_OnCanCarryInfiniteAmmo)

	DHookSetFromConf((z = DHookCreateDetour(Address_Null, CallConv_THISCALL, ReturnType_Int, ThisPointer_Address)), h, SDKConf_Signature, "MaxCarry")
	DHookAddParam(z, HookParamType_Int);
	DHookAddParam(z, HookParamType_CBaseEntity);
	DHookEnableDetour(z, true, DH_OnMaxCarry)*/

	if((z = DHookCreateFromConf(h, "CanCarryInfiniteAmmo"))) DHookEnableDetour(z, true, DH_OnCanCarryInfiniteAmmo)
	else LogError("Detour CanCarryInfiniteAmmo invalid.");

	if((z = DHookCreateFromConf(h, "MaxCarry"))) DHookEnableDetour(z, true, DH_OnMaxCarry)
	else LogError("Detour MaxCarry invalid.");

	CloseHandle(h)
}

public MRESReturn DH_OnCanCarryInfiniteAmmo(int i, Handle hReturn, Handle hParams)
{
	if(DHookGetParam(hParams, 1) == 2)
	{
		DHookSetReturn(hReturn, GetConVarInt(hConVar) == -2)
		return MRES_Supercede
	}
	return MRES_Ignored
}

public MRESReturn DH_OnMaxCarry(int i, Handle hReturn, Handle hParams)
{
	if(DHookGetParam(hParams, 1) == 2)
	{
		DHookSetReturn(hReturn, GetConVarInt(hConVar))
		return MRES_Supercede
	}
	return MRES_Ignored
}