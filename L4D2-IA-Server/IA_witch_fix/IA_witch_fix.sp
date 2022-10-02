#include <sourcemod>
#include <dhooks>

#define m_iVictimEhandle	(Address:52)
#define m_iEhandle			948

int iLastBot[33], iFindOtherSurvivor, iWitch
bool bAFKfix
Handle hDetour_Update

CreateDetourFromConf(Handle h, const char[]s, DHookCallback callback)
{
	Handle z = DHookCreateFromConf(h, s)
	if(z)
	{
		DHookEnableDetour(z, false, callback)
		CloseHandle(z)
	}
	else SetFailState("Detour %s invalid.", s);
}

public Plugin:myinfo =
{
	name = "IA_witch_fix",
	author = "IA/NanaNana",
	description = "Nothing",
	version = "1.27.2012",
	url = "https://steamcommunity.com/profiles/76561198291983872"
}

public OnPluginStart()
{
	GameData h = LoadGameConfigFile("IA_witch_fix")

	CreateDetourFromConf(h, "OnGetVictim", DH_OnGetVictim)
	CreateDetourFromConf(h, "WitchAttack_IsValidEnemy", DH_WitchAttack_IsValidEnemy)
	if(!(hDetour_Update = DHookCreateFromConf(h, "Witch_Update"))) SetFailState("Detour Witch_Update invalid.");

	CloseHandle(h)
	
	HookEvent("player_bot_replace", ReplacePlayer);
	HookEvent("bot_player_replace", ReplacePlayer);
	
	HookConVarChange(CreateConVar("IA_witch_afk_fix", "1", "Fix the Witch can't get survivor when player has been AFK", _, true, _, true, 1.0), Hook_ConVar);
	HookConVarChange(CreateConVar("IA_witch_find_other_survivor", "0", "Find another target when the first target is down. 0 = disable; 1 = closest one; 2 = random", _, true, _, true, 2.0), Hook_ConVar);
	Hook_ConVar(null, "", "")
}

Hook_ConVar(Handle:cvar, const String:o[], const String:n[])
{
	bool b = iFindOtherSurvivor == 1
	iFindOtherSurvivor = GetConVarInt(FindConVar("IA_witch_find_other_survivor"))
	if(!b && iFindOtherSurvivor == 1) DHookEnableDetour(hDetour_Update, false, DH_WitchAttack_Update)
	else if(b && iFindOtherSurvivor != 1) DHookDisableDetour(hDetour_Update, false, DH_WitchAttack_Update)
	
	bAFKfix = GetConVarBool(FindConVar("IA_witch_afk_fix"))
}

MRESReturn DH_OnGetVictim(Address p, Handle hReturn)
{
	/*int e = FindEntityByClassname(-1, "witch"), InfectedIntention = GetEntData(e, 7332)
	
	int x = LoadFromAddress(Address:(InfectedIntention+28), NumberType_Int32)
	PrintToChatAll("%i %i %i", x, p, GetEntityOfAddress(LoadFromAddress(Address:(InfectedIntention+24), NumberType_Int32)))
	for(int i=0;i<20480;i++)
	{
		if(LoadFromAddress(Address:(x+i), NumberType_Int32) == p) PrintToChatAll("%i", i) 
	}*/
	
	int victim = GetEntityOfEHandle(LoadFromAddress(p+m_iVictimEhandle, NumberType_Int32))
	if(iLastBot[victim]) victim = SetVictim(p, iLastBot[victim])
	if(iFindOtherSurvivor && (!IsClientInTeamAlive(victim, 2) || IsIncap(victim)))
	{
		int i
		if(iFindOtherSurvivor == 1)
		{
			float f[3], F[3], l, L = -1.0
			GetEntPropVector(iWitch, Prop_Data, "m_vecAbsOrigin", f)
			for(int b=1;b<=MaxClients;b++)
			{
				if(IsClientInTeamAlive(b, 2) && !IsIncap(b))
				{
					GetEntPropVector(b, Prop_Data, "m_vecAbsOrigin", F)
					l = GetVectorDistance(f, F)
					if(L == -1.0 || l <= L) L = l, i = b
				}
			}
		}
		else
		{
			int z[33], l
			for(int b=1;b<=MaxClients;b++)
			{
				if(IsClientInTeamAlive(b, 2) && !IsIncap(b))
				{
					z[l++] = b
				}
			}
			if(l) i = z[GetRandomInt(0,l-1)]
		}
		if(i) victim = SetVictim(p, i)
	}
	DHookSetReturn(hReturn, victim)
	return MRES_Supercede
}

int SetVictim(Address p, int a)
{
	StoreToAddress(p+m_iVictimEhandle, GetEntData(a, m_iEhandle), NumberType_Int32)
	return a
}

int GetEntityOfEHandle(int i)
{
	for(int a=1;a<=2048;a++)
	{
		if(IsValidEntity(a) && GetEntData(a, m_iEhandle) == i) return a
	}
	return -1
}

MRESReturn DH_WitchAttack_IsValidEnemy(Handle hReturn, Handle hParams)
{
	int a = DHookGetParam(hParams, 1)
	if(0 < a <= MaxClients && bAFKfix && iLastBot[a] && IsClientInTeamAlive(iLastBot[a], 2))
	{
		DHookSetReturn(hReturn, true)
		return  MRES_Supercede
	}
	return MRES_Ignored
}
MRESReturn DH_WitchAttack_Update(int witch)
{
	iWitch = witch
	return MRES_Ignored
}
// 270600560
// -2160776 270600560
// 270600560
public ReplacePlayer(Handle:event, const String:name[], bool:dontBroadcast)
{
	int a = GetClientOfUserId(GetEventInt(event, "player"))
	if(GetClientTeam(a) == 2)
	{
		int b = GetClientOfUserId(GetEventInt(event, "bot"));
		if(name[0] == 'b')
		{
			iLastBot[a] = 0
			iLastBot[b] = a
		}
		else
		{
			iLastBot[a] = b
			iLastBot[b] = 0
		}
	}
}

stock bool IsClientInTeamAlive(int a, int b)
{
	return IsClientInGame(a) && IsPlayerAlive(a) && GetClientTeam(a) == b
}

stock bool IsIncap(a)
{
	return GetEntProp(a, Prop_Send, "m_isIncapacitated") != 0
}
