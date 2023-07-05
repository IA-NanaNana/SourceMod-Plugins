#include <IA>
#include <IA_l4d2>
#include <dhooks>

bool onbutton[33], shell
Handle hGLPrimaryAttack
DynamicHook hExplodeTouch
int grenade

public Plugin myinfo=
{
	name = "Shotgun Fire Shell",
	author = "IA/NanaNana",
	description = "Funny shit",
	version = "1.0",
	url = "https://github.com/IA-NanaNana/SourceMod-Plugins"
}

public OnAllPluginsLoaded()
{
	GameData h = new GameData("l4d2_shotgun_fire_shell")
	Handle z
	
	/*DHookSetFromConf((z = DHookCreateDetour(Address_Null, CallConv_THISCALL, ReturnType_CBaseEntity, ThisPointer_CBaseEntity)), h, SDKConf_Signature, "LaunchGrenade")
	DHookAddParam(z, HookParamType_CBaseEntity);
	DHookEnableDetour(z, true, DH_LaunchGrenadePost)*/
	
	StartPrepSDKCall(SDKCall_Entity);
	PrepSDKCall_SetFromConf(h, SDKConf_Signature, "CGrenadeLauncher::PrimaryAttack")
	PrepSDKCall_SetReturnInfo(SDKType_Bool, SDKPass_Plain);
	hGLPrimaryAttack = EndPrepSDKCall()
	
	CreateHook(hExplodeTouch, h.GetOffset("ExplodeTouch"), HookType_Entity, ReturnType_Void, ThisPointer_CBaseEntity, 1, {HookParamType_CBaseEntity})
	 
	// CreateDetourFromConf(h, "OnTakeDamagePlayer", DH_OnTakeDamagePlayer)
	// CreateDetourFromSig("@_ZN11CBasePlayer11TraceAttackERK15CTakeDamageInfoRK6VectorP10CGameTrace", CallConv_THISCALL, ReturnType_Void, ThisPointer_CBaseEntity, DH_TraceAttack, _, 3, {HookParamType_Int,HookParamType_Int,HookParamType_Int})
	
	
	
	CloseHandle(h)
}

public OnEntityCreated(a, const String:n[])
{
	if(shell && !strcmp(n, "grenade_launcher_projectile")) grenade = a
}
public Action:OnPlayerRunCmd(a, &buttons, &impulse, Float:vel[3], Float:ang[3], &weapon, &subtype, &cmdnum, &tickcount, &seed, mouse[2])
{
	if(IsClientInTeamAlive(a, 2))
	{
		int w = GetPlayerWeapon(a)
		if(w != -1 && GetWeaponAmmoType(w) == AMMO_AUTOSHOTGUN)
		{
			if(GetWeaponClip(w))
			{
				if(buttons&IN_ATTACK)
				{
					if(!onbutton[a])
					{
						shell = true
						SetEntProp(w, Prop_Send, "m_reloadState", 0)
						int l = GetWeaponClip(w)
						while(l--)
						{
							SetEntDataVector(a, m_vecPunchAngle, Float:{0.0,0.0,0.0})
							SetEntProp(w, Prop_Send, "m_releasedFireButton", 1)
							SetEntProp(w, Prop_Send, "m_isHoldingFireButton", 0)
							GS_ClientNextAttackTime(a, GS_WeaponNextAttackTime(w, 1.0))
							SDKCall(hGLPrimaryAttack, w)
							ShotgunShell(grenade)
						}
						onbutton[a] = true
						shell = false
						// return Plugin_Continue
					}
				}
				else onbutton[a] = false
			}
			if(buttons&IN_RELOAD) GS_ClientNextAttackTime(a, GS_WeaponNextAttackTime(w, 1.0))
			else GS_ClientNextAttackTime(a, GS_WeaponNextAttackTime(w, 99999.0))
		}
	}
	return Plugin_Continue
}
ShotgunShell(e)
{
	// PrintToChatAll("%i", GetWeaponOwner(w)) 
	
	int E//, l = GetWeaponClip(w)
	float f[3], pos[3], ang[3]//, ang2[3]
	GetEntityOrigin(e, pos)
	GetEntityRotation(e, ang)
	// GetEntityVelocity(e, ang2) 
	GetEntityVelocity(e, f)
	ScaleVector(f, 2.0)
	SetEntityGravity(e, 0.01) 
	SetEntityModelEx(e, "models/ia-nananana/12g.mdl")
	// RequestFrame(az, e)
	f[0] += GetRandomFloat(-100.0, 100.0)
	f[1] += GetRandomFloat(-100.0, 100.0)
	f[2] += GetRandomFloat(-100.0, 100.0)
	TeleportEntity(e, NULL_VECTOR, NULL_VECTOR, f)
	SetEntProp(e, Prop_Data, "m_takedamage", 0)
	
	SDKHook(e, SDKHook_SetTransmit, HideWeaponAttach);
	// SetEntityRenderMode(e, RENDER_NONE)
	E = CreateEntityByName("prop_physics_override");
	SetEntityModel(E, "models/ia-nananana/12g.mdl")
	DispatchSpawn(E);
	SetEntProp(E, Prop_Data, "m_CollisionGroup", 1)
	SetEntityOwnerEntity(E, e)
	RequestFrame(fly, E)
	// SetVariantString("!activator");
	// AcceptEntityInput(E, "SetParent", e);
	// TeleportEntity(E, Float:{0.0,0.0,0.0}, Float:{0.0,0.0,0.0}, NULL_VECTOR)
	/*while(l--)
	{
		E = CreateEntityByName("physics_prop");
		SetEntityModelEx(E, "models/ia-nananana/12g.mdl")
		DispatchSpawn(E);
		SetEntityLifeTime(E, 60.0)
		SDKHook(E,  SDKHook_Touch, GrenadeTouch);
		bTouched[E] = false
		SetEntPropEnt(E, Prop_Send, "m_hOwnerEntity", GetWeaponOwner(w))
		
		f[0] = ang2[0] + GetRandomFloat(-100.0, 100.0)
		f[1] = ang2[1] + GetRandomFloat(-100.0, 100.0)
		f[2] = ang2[2] + GetRandomFloat(-100.0, 100.0)
		
		TeleportEntity(E, pos, ang, f)
		SetEntityGravity(E, 0.01)
	}
	SetWeaponClip(w, 1)*/
	// RemoveEntity(e)
	hExplodeTouch.HookEntity(Hook_Pre, e, DH_GrenadeTouch)
}
fly(E)
{
	int e = GetEntityOwnerEntity(E)
	if(e != -1)
	{
		TeleportEntityToEntity(E, e)
		RequestFrame(fly, E)
		return
	}
	RemoveEntity(E)
}
Action:HideWeaponAttach(e, a)
{
	return Plugin_Handled
}
MRESReturn DH_GrenadeTouch(int e, DHookParam hParam)
{
	int b = DHookGetParam(hParam, 1)
	if(GetEntData(b, 436) &0x28 && GetEntData(b, 564) != 11) return MRES_Ignored
	float f[3], F[3], d = 200.0
	int g = GetEntityGender(e), a = GetEntityOwnerEntity(e)
	GetEntityOrigin(e, f)
	GetEntityRotation(e, F)
	if(0 < b <= MaxClients && GetClientTeam(b) == 2 && GetClientTeam(a) == 2) d *= 0.35*GetFriendlyFireFactor()
	else if(!(0 < b <= MaxClients && GetPlayerZombieClass(b) == TANK))
	{
		TR_TraceRayFilter(f, F, MASK_SHOT, RayType_Infinite, TR_DontHitTarget, e);
		if(TR_DidHit() && TR_GetEntityIndex() == b) d *= GetHitboxDamageModifier(TR_GetHitGroup(), 2.0, 1.0, 0.5)
	}
	SDKHooks_TakeDamage(b, e, a == -1 ? 0 : a, d, DMG_BULLET, _, _, f);
	// PrintToChatAll("%f %f %f", f[0], f[1], f[2])

	char m[79] 
	float v[3]/*, d = CalculateDamage(GetEntPropFloat(e, Prop_Send, "m_flDamage")/2.0, l, 0.97, 0.5)*/, y[3], x[3], z[3]
	// GetEntityRotation(e, F)
	GetEntityVelocity(e, v)
	GetEntityModel(e, m, 79)
	
	GetAngleVectors(F, y, x, z);
	// ScaleVector(x, -35.0)
	ScaleVector(y, -30.0) // 前方距离？
	// ScaleVector(z, -10.0)
	AddVectors(f, x, f)
	AddVectors(f, y, f)
	AddVectors(f, z, f)
	
	
	
	int E = CreateEntityByName("physics_prop");
	SetEntityModel(E, m)
	DispatchSpawn(E);
	GetEntPropString(e, Prop_Data, "m_iName", m, 79)
	DispatchKeyValue(E, "targetname", m)
	ScaleVector(v, 0.5)
	TeleportEntity(E, f, F, v)
	SetEntityLifeTime(E, 60.0)
	GS_EntityMaxHealth(E, GS_EntityMaxHealth(e))
	GS_EntityHealth(E, GS_EntityHealth(e))
	SetEntitySkin(E, GetEntitySkin(e))
	SetEntProp(E, Prop_Data, "m_takedamage", 0);
	SetEntProp(E, Prop_Data, "m_iTeamNum", GetEntProp(e, Prop_Data, "m_iTeamNum"))
	SetEntityOwnerEntity(E, a)
	SetEntityGender(E, g)
	
	RemoveEntity(e)
	return MRES_Supercede
}

/*az(e)
{
	float f[3]
	GetEntityVelocity(e, f)
	ScaleVector(f, 5.0)
	TeleportEntity(e, NULL_VECTOR, NULL_VECTOR, f)
}*/

/*public MRESReturn DH_OnTakeDamagePlayer(int a, Handle hParams)
{
	if(god) return MRES_Supercede
	return MRES_Ignored
}

public MRESReturn DH_TraceAttack(int a, Handle hParams)
{
	if(god) return MRES_Supercede
	return MRES_Ignored
}*/

stock CreateHook(DynamicHook &a, int offset, HookType calltype, ReturnType returntype, ThisPointerType thisType, l=0, any:d[]={})
{
	a = DHookCreate(offset, calltype, returntype, thisType)
	for(int i=0;i<l;i++)
	{
		DHookAddParam(a, HookParamType:d[i]);
	}
}