#include <sourcemod>

int iStore[4]
Address pAddress

public Plugin:myinfo =
{
	name = "IA_50cal_damage",
	author = "IA/NanaNana",
	description = "Nothing",
	version = "1.27.2012",
	url = "https://steamcommunity.com/profiles/76561198291983872"
}

public OnPluginStart()
{
	GameData h = new GameData("IA_50cal_damage")
	pAddress = h.GetAddress("MountedGunFire") + Address:0x375
	h.Close()
	
	for(int i=0;i<3;i++)
	{
		iStore[i] = LoadFromAddress(pAddress+Address:(i*4), NumberType_Int32)
	}
	iStore[3] = LoadFromAddress(pAddress+Address:12, NumberType_Int8)
	
	StoreToAddress(pAddress, 0x85C7, NumberType_Int16)
	StoreToAddress(pAddress+Address:2, 0xFFFFFE54, NumberType_Int32)
	StoreToAddress(pAddress+Address:10, 0x9090, NumberType_Int16)
	StoreToAddress(pAddress+Address:12, 0x90, NumberType_Int8)
	
	ConVar b = FindConVar("IA_50cal_damage")
	HookConVarChange(b, Hook_ConVar);
	Hook_ConVar(b, "", "")
}

public OnPluginEnd()
{
	for(int i=0;i<3;i++)
	{
		StoreToAddress(pAddress+Address:(i*4), iStore[i], NumberType_Int32)
	}
	StoreToAddress(pAddress+Address:12, iStore[3], NumberType_Int8)
}

Hook_ConVar(ConVar cvar, const char []o, const char []n)
{
	StoreToAddress(pAddress+Address:6, GetConVarFloat(cvar), NumberType_Int32)
}

