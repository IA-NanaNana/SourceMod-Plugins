/*====================================================
1.2
	- Added l4d1 support. Thanks to Beatles for suggestion.
	- Reduce unnecessary code.
	
1.1
	- Fixed plugin conflict with left4dhooks while in windows server. Thanks to HarryPotter for reporting.
	- Fixed wrong detour setting cause crash the windows server. Thanks to Psyk0tik for technical support.

1.0
	- Initial release
======================================================*/
#pragma newdecls required
#include <sourcemod>
#include <sdktools>
#include <dhooks>

Handle hRestartDetour, hRestartFromVoteDetour
ConVar hRestartGame
//Address iPatch1
int m_bMissionLost

public Plugin myinfo=
{
	name = "Restart Without Change Level",
	author = "IA/NanaNana",
	description = "Make the mp_restartgame and restart scenario from vote no longer change map to first map of scenario",
	version = "1.2",
	url = "http://forums.alliedmods.net/showthread.php?t=334009"
}

public void OnPluginStart()
{
	Handle a = LoadGameConfigFile("l4d_restart_without_changelevel")

	if(!a)
		SetFailState( "Can't load gamedata \"l4d_restart_without_changelevel.txt\" or not found" )
	if(!(hRestartDetour = DHookCreateFromConf(a, "Restart")))
		SetFailState( "Can't create detour \"Restart\"" )
	if(!(hRestartFromVoteDetour = DHookCreateFromConf(a, "RestartScenarioFromVote")))
		SetFailState( "Can't create detour \"RestartScenarioFromVote\"" )
	
	if((m_bMissionLost = GameConfGetOffset(a, "CDirector::m_bMissionLost")) == -1) SetFailState( "Offset CDirector::m_bMissionLost invalid." )
	
	//iPatch1 = GameConfGetAddress(a, "Restart") + view_as<Address>(GameConfGetOffset(a, "CDirector::Restart__Patch1"));
	CloseHandle(a)
	hRestartGame = FindConVar("mp_restartgame")

	//EnableDetour(true)
	DHookEnableDetour(hRestartDetour, false, DH_OnRestart)
	DHookEnableDetour(hRestartFromVoteDetour, false, DH_OnRestartFromVote)
		
	// HookConVarChange(CreateConVar("l4d2_restart_without_changelevel", "0", "Turn on/off plugin.", 0, true, 0.0, true, 1.0), HookConVar);
}
public void OnPluginEnd()
{
	//EnableDetour(false)
	DHookDisableDetour(hRestartDetour, false, DH_OnRestart)
	DHookDisableDetour(hRestartFromVoteDetour, false, DH_OnRestartFromVote)
}

/* void HookConVar(Handle cvar, const char[]o, const char[]n)
{
	EnableDetour(StringToInt(n) != 0)
} */

/*bool EnableDetour(bool b)
{
	if(b)
	{
		DHookEnableDetour(hRestartDetour, false, DH_OnRestart)
		DHookEnableDetour(hRestartFromVoteDetour, false, DH_OnRestartFromVote)
		switch(LoadFromAddress(iPatch1, NumberType_Int8))
		{
			case 0x00: StoreToAddress(iPatch1, 0x01, NumberType_Int8)
			case 0x75: StoreToAddress(iPatch1, 0xEB, NumberType_Int8)
		}
	}
	else
	{
		DHookDisableDetour(hRestartDetour, false, DH_OnRestart)
		DHookDisableDetour(hRestartFromVoteDetour, false, DH_OnRestartFromVote)
		switch(LoadFromAddress(iPatch1, NumberType_Int8))
		{
			case 0x01: StoreToAddress(iPatch1, 0x00, NumberType_Int8)
			case 0xEB: StoreToAddress(iPatch1, 0x75, NumberType_Int8)
		}
	}
}*/

MRESReturn DH_OnRestart(Address a)
{
	StoreToAddress(a+view_as<Address>(m_bMissionLost), 1, NumberType_Int8)
}

MRESReturn DH_OnRestartFromVote(Address a, Handle hParams)
{
	hRestartGame.SetInt(1)
	return MRES_Supercede
}