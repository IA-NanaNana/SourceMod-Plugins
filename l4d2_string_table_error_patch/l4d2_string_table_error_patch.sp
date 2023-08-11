/*====================================================
1.0
	- Initial release
======================================================*/
#pragma newdecls required

#include <sdktools>
#include <sourcemod>

Address pAddress

public Plugin myinfo = 
{
	name = "String Table Error Patch",
	author = "IA/NanaNana",
	description = "",
	version = "1.0",
	url = "http://steamcommunity.com/profiles/76561198291983872"
}

public void OnPluginStart()
{
	GameData h = new GameData("l4d2_string_table_error_patch")
	if(!(pAddress = h.GetMemSig("WriteBaselines")))
		SetFailState( "Fail to get address of \"WriteBaselines\"" )
	h.Close()

	StoreToAddress(pAddress+view_as<Address>(0xFD), 0xEB, NumberType_Int8)
}

public void OnPluginEnd()
{
	StoreToAddress(pAddress+view_as<Address>(0xFD), 0x75, NumberType_Int8)
}
