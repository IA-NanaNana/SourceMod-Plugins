/*====================================================
1.4
	- Added Versus Support
	- Added admin command (GENERIC) "sm_restart" : Restart current round/level immediately
	- CRestartGameIssue::ExecuteCommand instead RestartScenarioFromVote
	- Fixed may crash on Win server. Thanks to Silvers for reporting.

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
#include <left4dhooks>
#include <sourcescramble>

Handle hRestartFromVoteDetour, hRestart
int m_iRestartReason
MemoryPatch hRestartVersus

enum RestartReason
{
	RestartReason_None,
	RestartReason_MissionLost
}

public Plugin myinfo=
{
	name = "Restart Without Change Level",
	author = "IA/NanaNana",
	description = "Make restart scenario from vote no longer change map to first map of scenario or loading map",
	version = "1.4",
	url = "http://forums.alliedmods.net/showthread.php?t=334009"
}

public void OnPluginStart()
{
	GameData a = new GameData("l4d_restart_without_changelevel")

	if(!a)
		SetFailState( "Can't load gamedata \"l4d_restart_without_changelevel.txt\" or not found" )
	if(!(hRestartFromVoteDetour = DHookCreateFromConf(a, "CRestartGameIssue::ExecuteCommand")))
		SetFailState( "DetourFunctions CRestartGameIssue::ExecuteCommand invalid" )
	if((m_iRestartReason = a.GetOffset("CDirector::m_iRestartReason")) == -1)
		SetFailState( "Offset CDirector::m_iRestartReason invalid." )
	if(!(hRestartVersus = MemoryPatch.CreateFromConf(a, "RestartVersus")))
		SetFailState("MemPatches RestartVersus invalid.");
	
	StartPrepSDKCall(SDKCall_Raw);
	PrepSDKCall_SetFromConf(a, SDKConf_Signature, "Restart");
	if(!(hRestart = EndPrepSDKCall())) SetFailState("Signature Restart invalid.");
	
	RegAdminCmd("sm_restart", RestartRound, ADMFLAG_GENERIC, "Restart current round");

	CloseHandle(a)
	
	ConVar cvar = CreateConVar("l4d_vote_restart_round", "1", "Turn on/off the restart game from vote to restart current level. (Coop mode only)", 0, true, 0.0, true, 1.0)
	HookConVarChange(cvar, HookConVar);
	if(GetConVarBool(cvar)) DHookEnableDetour(hRestartFromVoteDetour, false, DH_OnExecuteCommand)
}

Action RestartRound(int client, int args)
{
	switch(L4D_GetGameModeType())
	{
		case GAMEMODE_COOP: RestartGame(RestartReason_MissionLost)
		case GAMEMODE_VERSUS:
		{
			hRestartVersus.Enable()
			SDKCall(hRestart, L4D_GetPointer(POINTER_DIRECTOR))
			hRestartVersus.Disable()
		}
		default: RestartGame(RestartReason_None)
	}
	return Plugin_Handled
}

void RestartGame(RestartReason i)
{
	Handle h = CreateEvent("round_end")
	SetEventInt(h, "winner", 0)
	SetEventInt(h, "reason", view_as<int>(i))
	SetEventString(h, "message", "Restart by command")
	SetEventFloat(h, "time", 0.0)
	FireEvent(h)
	if(i == RestartReason_MissionLost) FireEvent(CreateEvent("mission_lost"))
	Address p = L4D_GetPointer(POINTER_DIRECTOR)
	StoreToAddress(p+view_as<Address>(m_iRestartReason), i, NumberType_Int8)
	SDKCall(hRestart, p)
}

void HookConVar(Handle cvar, const char[]o, const char[]n)
{
	if(GetConVarBool(cvar)) DHookEnableDetour(hRestartFromVoteDetour, false, DH_OnExecuteCommand)
	else DHookDisableDetour(hRestartFromVoteDetour, false, DH_OnExecuteCommand)
}

MRESReturn DH_OnExecuteCommand(Address a)
{
	if(L4D_GetGameModeType() == GAMEMODE_COOP)
	{
		RestartGame(RestartReason_MissionLost)
		return MRES_Supercede
	}
	return MRES_Ignored
}
