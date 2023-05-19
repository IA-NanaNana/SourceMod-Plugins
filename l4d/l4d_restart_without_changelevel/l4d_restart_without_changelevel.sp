/*====================================================
1.5.1 - 2023/5/10
	  - Fixed L4D_GetGameModeType() work problem in L4D1. Thanks to HarryPotter for reporting and provide solution.

1.5 - 2023/4/25
	- Reduce unnecessary code.
	- Function CDirector::EndScenario instead CDirector::Restart
	- Added restart reason number. #usage: sm_restart <L4D2_RestartReason> || empty for auto
	- Fixed broken win signatures.

1.4.1 - 2022/12/8
	- Fixed crash the server after call the restart vote. Thanks to gabuch2 for reporting.
	- Fixed invalid Win signatures.

1.4 - 2022/12/7
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

Handle hExecuteCommand, hRestart//, hRestartFromVoteDetour
int iLastRoundNumber = -1, m_iRoundNumber, m_fRoundEndInterval
// int m_iRestartReason
// bool bShouldBlock
MemoryPatch hRestartVersus

enum L4D2_RestartReason
{
	L4D2_RestartReason_None = 0,
	L4D2_RestartReason_MissionLost = 1,
	L4D2_RestartReason_Unknown = 2,
	L4D2_RestartReason_FinaleWon = 3,
	L4D2_RestartReason_MissionLostRematch = 4,
	L4D2_RestartReason_VersusEndRound = 5,
	L4D2_RestartReason_Transition = 6,
	L4D2_RestartReason_VersusRestart = 7,
	L4D2_RestartReason_VersusShutdown = 8,
	L4D2_RestartReason_VersusNoSwaps = 18
}
enum L4D1_RestartReason
{
	L4D1_RestartReason_None = 0,
	L4D1_RestartReason_MissionLost = 1,
	L4D1_RestartReason_FinaleWon = 3,
	L4D1_RestartReason_FinaleLost = 4,
	L4D1_RestartReason_VersusEndRound = 5,
	L4D1_RestartReason_Transition = 6,
	L4D1_RestartReason_VersusShutdown = 7
}

public Plugin myinfo=
{
	name = "Restart Without Change Level",
	author = "IA/NanaNana",
	description = "Make restart scenario from vote no longer change map to first map of scenario or loading map",
	version = "1.5",
	url = "http://forums.alliedmods.net/showthread.php?t=334009"
}

public void OnPluginStart()
{
	GameData a = new GameData("l4d_restart_without_changelevel")

	if(!a)
		SetFailState( "Can't load gamedata \"l4d_restart_without_changelevel.txt\" or not found" )
	if(!(hExecuteCommand = DHookCreateFromConf(a, "CRestartGameIssue::ExecuteCommand")))
		SetFailState( "DetourFunctions CRestartGameIssue::ExecuteCommand invalid" )
	// if(!(hRestartFromVoteDetour = DHookCreateFromConf(a, "RestartScenarioFromVote")))
		// SetFailState( "Can't create detour \"RestartScenarioFromVote\"" )
	if((m_iRoundNumber = a.GetOffset("CDirector::m_iRoundNumber")) == -1)
		SetFailState( "Offset CDirector::m_iRoundNumber invalid." )
	if((m_fRoundEndInterval = a.GetOffset("CDirector::m_fRoundEndInterval")) == -1)
		SetFailState( "Offset CDirector::m_fRoundEndInterval invalid." )
	if(!(hRestartVersus = MemoryPatch.CreateFromConf(a, "RestartVersus")))
		SetFailState("MemPatches RestartVersus invalid.");
	
	StartPrepSDKCall(SDKCall_Raw);
	PrepSDKCall_SetFromConf(a, SDKConf_Signature, "EndScenario");
	PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain);
	if(!(hRestart = EndPrepSDKCall())) SetFailState("Signature EndScenario invalid.");
	
	RegAdminCmd("sm_restart", RestartRound, ADMFLAG_GENERIC, "Restart current round. usage: sm_restart <L4D2_RestartReason> || empty for auto");

	CloseHandle(a)
	
	ConVar cvar = CreateConVar("l4d_vote_restart_round", "1", "Turn on/off the restart game from vote to restart current level.", 0, true, 0.0, true, 1.0)
	HookConVarChange(cvar, HookConVar);
	if(GetConVarBool(cvar)) DHookEnableDetour(hExecuteCommand, false, DH_OnExecuteCommand)//, DHookEnableDetour(hRestartFromVoteDetour, false, DH_OnRestartFromVote)
	
	HookEvent("round_start_post_nav", round_start_post_nav, EventHookMode_PostNoCopy);
}

Action RestartRound(int client, int args)
{
	if(args)
	{
		char s[12]
		GetCmdArg(1, s, sizeof s)
		RestartGame(view_as<L4D2_RestartReason>(StringToInt(s)))
	}
	else if(L4D2_IsGenericCooperativeMode()) 
	{
		RestartGame(L4D2_RestartReason_MissionLost);
	}
	else if(L4D_IsVersusMode()) 
	{
		EngineVersion e = GetEngineVersion();
		iLastRoundNumber = LoadFromAddress(L4D_GetPointer(POINTER_DIRECTOR)+view_as<Address>(m_iRoundNumber), NumberType_Int8);
		StoreToAddress(L4D_GetPointer(POINTER_DIRECTOR)+view_as<Address>(m_iRoundNumber), e == Engine_Left4Dead2 ? 1 : 0, NumberType_Int8);
		hRestartVersus.Enable();
		RestartGame(L4D2_RestartReason_VersusNoSwaps);
		hRestartVersus.Disable();
	}
	else
	{
		RestartGame(L4D2_RestartReason_None);
	}
	return Plugin_Handled
}

void RestartGame(L4D2_RestartReason i)
{
	/*Handle h = CreateEvent("round_end")
	SetEventInt(h, "winner", 0)
	SetEventInt(h, "reason", view_as<int>(i))
	SetEventString(h, "message", "Restart by command")
	SetEventFloat(h, "time", 0.0)
	FireEvent(h)
	if(i == L4D2_RestartReason_MissionLost) FireEvent(CreateEvent("mission_lost"))*/
	Address p = L4D_GetPointer(POINTER_DIRECTOR)
	// StoreToAddress(p+view_as<Address>(m_iL4D2_RestartReason), i, NumberType_Int8)
	SDKCall(hRestart, p, i)
	StoreToAddress(p+view_as<Address>(m_fRoundEndInterval), 1.0, NumberType_Int32)
}

void HookConVar(Handle cvar, const char[]o, const char[]n)
{
	if(GetConVarBool(cvar)) DHookEnableDetour(hExecuteCommand, false, DH_OnExecuteCommand)//, DHookEnableDetour(hRestartFromVoteDetour, false, DH_OnRestartFromVote)
	else DHookDisableDetour(hExecuteCommand, false, DH_OnExecuteCommand)//, DHookDisableDetour(hRestartFromVoteDetour, false, DH_OnRestartFromVote)
}

MRESReturn DH_OnExecuteCommand(Address p, Handle hReturn)
{
	// if(L4D_GetGameModeType() == GAMEMODE_COOP) bShouldBlock = true
	// return MRES_Ignored
	RestartRound(0, 0)
	DHookSetReturn(hReturn, 0)
	return MRES_Supercede
}

/*MRESReturn DH_OnRestartFromVote(Address a, Handle hParams)
{
	if(bShouldBlock)
	{
		bShouldBlock = false
		RestartGame(L4D2_RestartReason_MissionLost)
		return MRES_Supercede
	}
	return MRES_Ignored
}*/

// Reserve the round number
public void round_start_post_nav(Event event, char[]name, bool dontBroadcast)
{
	if(iLastRoundNumber != -1)
	{
		StoreToAddress(L4D_GetPointer(POINTER_DIRECTOR)+view_as<Address>(1061), iLastRoundNumber, NumberType_Int8)
		iLastRoundNumber = -1
	}
}
public void OnMapEnd()
{
	iLastRoundNumber = -1
}