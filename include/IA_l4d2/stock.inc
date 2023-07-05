/**************
 *	Stock
***************/
#define ACT_VM_DEPLOY				179 // 拔出武器并上膛（一般为捡起后的动画）
#define ACT_VM_DEPLOY_LAYER			1276 // 拔出武器并上膛（一般为捡起后的动画）

#define ACT_VM_DRAW_DEPLOYED		493 // 正常-拔出武器
#define ACT_VM_IDLE					183 // 正常-待机
#define ACT_VM_RELOAD				193 // 正常-换弹夹
#define ACT_VM_PRIMARYATTACK		191 // 正常-开火
#define ACT_VM_PRIMARYATTACK_LAYER	1252 // 正常-开火
#define ACT_VM_SECONDARYATTACK_LAYER	1253 // 正常-左边开火
#define ACT_VM_MELEE_LAYER			1254 // 正常-推
#define ACT_VM_HOLSTER				182 // 正常-收起武器
#define ACT_VM_FIDGET				184 // 正常-检视

// 双枪右边空仓换弹
#define ACT_VM_RELOAD_DUAL_PISTOL		1303
#define ACT_VM_RELOAD_DUAL_PISTOL_LAYER	1304

#define ACT_VM_DRAW						181 // 空仓-拔出武器
#define ACT_VM_IDLE_EMPTY_LEFT			480 // 空仓-双枪待机
#define ACT_VM_IDLE_LOWERED				212 // 空仓-待机
#define ACT_VM_RELOAD_EMPTY				180 // 空仓-换弹夹
#define ACT_VM_RELOAD_EMPTY_LAYER		1269 // 空仓-换弹夹
#define ACT_VM_DRYFIRE					194 // 空仓-开火
#define ACT_VM_DRYFIRE_LEFT				481 // 空仓-左边开火
#define ACT_VM_SECONDARYATTACK_LAYER	1253 // 空仓-推
#define ACT_VM_FIZZLE					1565 // 空仓-检视


#define ACT_PRIMARY_VM_IDLE_TO_LOWERED		1879 // 使用机瞄
#define ACT_VM_IDLE_DUAL_PISTOL				1296 // 机瞄-双枪空仓待机
#define ACT_PRIMARY_VM_IDLE					1873 // 机瞄-待机
#define ACT_PRIMARY_VM_DRYFIRE				1878 // 机瞄-最后一发子弹打掉时转空仓待机的动画
#define ACT_PRIMARY_VM_IDLE_LOWERED			1880 // 机瞄-空仓待机
#define ACT_PRIMARY_VM_PRIMARYATTACK		1875 // 机瞄-开火
#define ACT_PRIMARY_VM_SECONDARYATTACK		1876 // 机瞄-推
#define ACT_PRIMARY_VM_RELOAD				1877 // 机瞄-换弹
#define ACT_PRIMARY_VM_LOWERED_TO_IDLE		1881 // 退出机瞄

#define ACT_VM_USABLE_TO_UNUSABLE			1870 // 使用机瞄-空仓
#define ACT_VM_UNUSABLE_TO_USABLE			1869 // 退出机瞄-空仓

#define ACT_SECONDARY_VM_IDLE_TO_LOWERED	1890 // 使用下挂武器
#define ACT_SECONDARY_VM_DRAW				1882 // 下挂武器-拔出
#define ACT_SECONDARY_VM_IDLE				1884 // 下挂武器-待机
#define ACT_SECONDARY_VM_PRIMARYATTACK		1886 // 下挂武器-开火
#define ACT_SECONDARY_VM_DRYFIRE			1889 // 下挂武器-空仓开火
#define ACT_SECONDARY_VM_SECONDARYATTACK	1887 // 下挂武器-推
#define ACT_SECONDARY_VM_RELOAD				1888 // 下挂武器-换弹
#define ACT_SECONDARY_VM_PULLBACK			1885 // 下挂武器-检视
#define ACT_SECONDARY_VM_LOWERED_TO_IDLE	1892 // 退出下挂武器

#define ACT_PDA_VM_IDLE_TO_LOWERED			1912 // 使用下挂武器-空仓
#define ACT_PDA_VM_DRAW						1904 // 下挂武器-空仓-拔出
#define ACT_PDA_VM_IDLE						1906 // 下挂武器-空仓-待机
#define ACT_PDA_VM_SECONDARYATTACK			1909 // 下挂武器-空仓-推
#define ACT_PDA_VM_RELOAD					1910 // 下挂武器-空仓-换弹
#define ACT_PDA_VM_PULLBACK					1907 // 下挂武器-空仓-检视
#define ACT_PDA_VM_LOWERED_TO_IDLE			1914 // 退出下挂武器-空仓


#define ACT_VM_RELOAD_PUMP			1262	// 霰弹枪-结束装填动画
#define ACT_VM_RELOAD_PUMP_LAYER	1263	// 霰弹枪-结束装填动画
#define ACT_VM_RELOAD_END			1418	// 霰弹枪-结束装填动画并上膛
#define ACT_VM_RELOAD_END_LAYER		1419	// 霰弹枪-结束装填动画并上膛
#define ACT_VM_RELOAD_LIST  193,1264,1403

#define ALT_M203 4

// Int Melee Weapon Attributes
#define IMWA_DamageFlags				292
#define IMWA_PrimaryAttacksCount		3116

// Table Melee Weapon Attributes
#define TMWA_PrimaryAttacks				3104
// Melee Weapon Swing Table
#define	IMWSA_Activity				0
#define	IMWSA_PlayerActivity		4
#define	IMWSA_PlayerActivityIdle	8
#define	IMWSA_StartDir				12
#define	IMWSA_EndDir				16
#define	FMWSA_StartTime				20
#define	FMWSA_EndTime				24
#define	FMWSA_Duration				28
#define	FMWSA_Max					48

// Float Melee Weapon Attributes
#define FMWA_Damage						288
#define FMWA_IdleTime					3148

// String Melee Weapon Attributes
#define SMWA_WorldModel					88
#define SMWA_Name						3152


// Melee Weapon Extra Swing Table
#define IMWSEA_Pointer				-1

#define FMWSEA_CycleTime			-51


// Weapon Attributes
#define IWA_Bucket					344
#define IWA_Position				348
#define IWA_ClipSize				352
#define IWA_ClipSize2				356
#define IWA_DefaultClip				360
#define IWA_DefaultClip2			364
#define IWA_Weight					368
#define IWA_AllowAutoSwitchTo		376
#define IWA_AllowAutoSwitchFrom		377
#define IWA_Flags					380
#define IWA_AmmoIndex				2128
#define IWA_Ammo2Index				2132
#define IWA_WeaponType				2196
#define IWA_Penetration				2504
#define IWA_Damage					2508
#define IWA_Bullets					2520
#define IWA_Tier					3048
#define IWA_PenetrationNumLayers	3144


#define FWA_MaxPlayerSpeed				2192
#define FWA_Range						2512
#define FWA_RangeModifier				2516
#define FWA_CycleTime					2524

#define FWA_VerticalPunch				3076
#define FWA_HorizontalPunch				3080
#define FWA_HorizontalPunchDirChance	3084
#define FWA_SpreadPerShot				3088
#define FWA_MaxSpread					3092
#define FWA_SpreadDecay					3096
#define FWA_MinDuckingSpread			3100
#define FWA_MinStandingSpread			3104
#define FWA_MinInAirSpread				3108
#define FWA_MaxMovementSpread			3112
#define FWA_PelletScatterPitch			3116
#define FWA_PelletScatterYaw			3120
//----------------------------
#define FWA_ReloadDuration				3128
#define FWA_DualReloadDuration			3132
#define FWA_DeployDuration				3136
#define FWA_DualDeployDuration			3140
//----------------------------
#define FWA_PenetrationPower			3148
#define FWA_PenetrationMaxDist			3152
#define FWA_CharPenetrationMaxDist		3156
#define FWA_GainRange					3160


#define SWA_ViewModel					166
#define SWA_PlayerModel					246
#define TSWA_ShootSound					528
#define TSWA_ShootSoundMax				20

#define SWA_ViewModelDual				3192
#define SWA_PlayerModelDual				3272
#define SWA_WorldModel					3456

// DT_BreakableProp // CPhysicsProp
#define m_iPropType			5424
#define PropType_PropTank	1
#define PropType_GasCan		2
#define PropType_FireCrate	3

#define SMOKER	1
#define BOOMER	2
#define HUNTER	3
#define SPITTER	4
#define JOCKEY	5
#define CHARGER	6
#define WITCH	7
#define TANK	8

#define TRACER_NONE				0
#define TRACER_LINE				1
#define TRACER_RAIL				2
#define TRACER_BEAM				3
#define TRACER_LINE_AND_WHIZ	4

// BulletType
enum BulletType
{
	BulletType_Auto	= -1,
	BulletType_Normal,
	BulletType_Explode,
	BulletType_Fire,
	BulletType_EF,
	BulletType_Alt
}

// 
 
// CTerrorPlayer Offset
#define m_vecPunchAngle		6832
#define m_flAFKTime			9216
#define m_pPlayerAnimState  10512
#define m_godTimer			11872

// CTerrorWeapon Offset
// #define m_bInReload					5209
#define m_nIdealSequence			5216
#define m_IdealActivity				5220
#define m_iWeaponID					5236
#define m_flShotgunReloadStartTime	5456
#define m_hLastOwner				6040
#define m_hTransmitTarget			6044

// CDirector Offset
#define m_flRestartDelay	Address:432
#define m_iRoundNumber		Address:1061
#define m_iTankPassedCount	Address:88
#define m_iRestartReason	Address:452
#define m_bIsTransition		Address:462
#define m_bInIntro			Address:464
#define m_fMobSpawnTimer			468
/*enum struct InfectedSpawnTimer
{
	Smoker = 
}*/
#define m_fSISpawnTimerStart	552
#define m_fSISpawnTimerSmoker	564

// CWeaponMeleeSpawn Offset
#define m_iMeleeID			5224

// CTerrorNavMesh Offset
#define m_fMaxFlowDistance	1524

#define Upgrade_FireBullect			(1<<0)
#define Upgrade_ExplosiveBullect	(1<<1)
#define Upgrade_LaserSight			(1<<2)

// CWeaponSpawn
#define spawnflag_InfiniteItems		(1<<3)	//

stock float CalculateDamage(float dmg, float range, float rangmodify, float base=500.0)
{
	int c = RoundFloat(range / base)
	float d = rangmodify
	while(c--) d *= rangmodify
	return dmg * d
}

stock int CreateMeleeSpawn(id, count, const Float:x[3]=NULL_VECTOR, const Float:y[3]=NULL_VECTOR)
{
	int e = CreateEntityByName("weapon_melee_spawn");
	SetEntData(e, 5224, id)
	DispatchKeyValue(e, "targetname", "IA_weapon_spawn");
	TeleportEntity(e, x, y, NULL_VECTOR)
	DispatchKeyValueInt(e, "count", count);
	DispatchSpawn(e);
	return e
}

stock int CreateWeapon(const String:s[], int a=0, bool:b=false, const Float:x[3]=NULL_VECTOR, const Float:y[3]=NULL_VECTOR)
{
	new e = CreateEntityByName(s)
	if(e != -1) DispatchSpawn(e)
	else
	{
		char m[64]
		e = CreateEntityByName("weapon_melee")
		SetEntPropString(e, Prop_Data, "m_strMapSetScriptName", s);
		DispatchSpawn(e)
		GetEntPropString(e, Prop_Data, "m_ModelName", m, 64);
		if(!strcmp(m, "models/v_models/weapons/v_claw_hunter.mdl", false))
		{
			RemoveEntity(e)
			return -1
		}
	}
	if(a)
	{
		float f[3]
		GetClientEyePosition(a, f)
		TeleportEntity(e, f, NULL_VECTOR, NULL_VECTOR)
		if(b) AcceptEntityInput(e, "Use", a)
	}
	else TeleportEntity(e, x, y, NULL_VECTOR)
	return e
}

stock CreateFireWerk(int t, const Float:P[3], const Float:F[3]=NULL_VECTOR)
{
	if(t > 4 || t < 1) return
	char s[32]
	Format(s, 32, "fireworks_0%i", t)
	int e = CreateParticle(s, P, F, 5.0)
	PlayGameSound(0, "c2m5.fireworks_launch", e)
	CreateTimer(2.2, EmitBurstSound, e)
}

stock int CreateParticle(const char[]n, const float P[3], const float F[3], float l=0.0, float delay=0.0)
{
	int e = CreateEntityByName("info_particle_system")
	DispatchKeyValue(e, "effect_name", n);
	DispatchSpawn(e);
	ActivateEntity(e);
	TeleportEntity(e, P, F, NULL_VECTOR);
	if(l) SetEntityLifeTime(e, l+delay)
	if(delay)
	{
		char s[32]
		Format(s, 32, "OnUser2 !self:start::%f:1", delay);
		SetVariantString(s);
		AcceptEntityInput(e, "AddOutput");
		AcceptEntityInput(e, "FireUser2");
	}
	else AcceptEntityInput(e, "start");
	
	return e
}

stock CreateFlare(a, float f, float size=1.0)
{
	SetEntityLifeTime(a, f)
	PlayGameSound(0, "General.BurningObject",a)
	new e = CreateEntityByName("info_particle_system"), Float:P[3], Float:F[3]={180.0,0.0,90.0}//, String:s[12], b = GetEntPropEnt(a, Prop_Send, "m_hOwnerEntity")
	//PrecacheParticle("flare_burning");
	DispatchKeyValue(e, "effect_name", "flare_burning");
	DispatchSpawn(e);
	ActivateEntity(e);
	AcceptEntityInput(e, "start");
	SetVariantString("!activator"); 
	AcceptEntityInput(e, "SetParent", a);
	TeleportEntity(e, P, F, NULL_VECTOR);
	SetEntityLifeTime(e, f)
	e = CreateEntityByName("env_sprite");
	DispatchKeyValue(e, "rendercolor", "200 20 15");
	SetEntityModelEx(e, "models/sprites/glow01.spr")
	DispatchKeyValue(e, "spawnflags", "3");
	DispatchKeyValue(e, "rendermode", "9");
	DispatchKeyValueFloat(e, "GlowProxySize", 256.0*size);
	DispatchKeyValue(e, "renderamt", "120");
	DispatchKeyValueFloat(e, "scale", 256.0*size);
	DispatchSpawn(e);
	SetVariantString("!activator");
	AcceptEntityInput(e, "SetParent", a);
	TeleportEntity(e, P, F, NULL_VECTOR);
	SetEntityLifeTime(e, f)
	e = CreateEntityByName("light_dynamic");
	DispatchKeyValue(e, "_light", "200 20 15 255");
	DispatchKeyValue(e, "brightness", "1");
	DispatchKeyValueFloat(e, "spotlight_radius", 225.0*size);
	DispatchKeyValueFloat(e, "distance", 450.0*size);
	DispatchKeyValue(e, "style", "6");
	DispatchSpawn(e);
	AcceptEntityInput(e, "TurnOn");
	SetVariantString("!activator");
	AcceptEntityInput(e, "SetParent", a);
	TeleportEntity(e, P, F, NULL_VECTOR);
	SetEntityLifeTime(e, f)
	//IgniteEntity(a, 60.0, _, 5.0);
	/*e = CreateEntityByName("point_hurt")
	SetEntPropFloat(e, Prop_Data, "m_flRadius", 30.0)
	SetEntPropFloat(e, Prop_Data, "m_flDelay", 0.2)
	SetEntProp(e, Prop_Data, "m_bitsDamageType", DMG_BURN|DMG_BULLET)
	SetEntProp(e, Prop_Data, "m_nDamage", 1)
	Format(s, 12, "%i", b)
	DispatchKeyValue(b, "targetname", s);
	DispatchKeyValue(e, "target", s)
	DispatchSpawn(e);
	AcceptEntityInput(e, "TurnOn");*/
	/*e = CreateEntityByName("trigger_hurt")
	DispatchKeyValue(e, "damage", "1.0");
	DispatchKeyValue(e, "damagetype", "10");
	AcceptEntityInput(e, "Enable", b);
	AcceptEntityInput(e, "StartTouch", b);
	//AcceptEntityInput(e, "Hurt", GetEntPropEnt(a, Prop_Send, "m_hOwnerEntity"));
	SetVariantString("!activator");
	AcceptEntityInput(e, "SetParent", a);
	SetEntPropVector(e, Prop_Send, "m_vecMins", Float:{-50.0, -50.0, -50.0})
	SetEntPropVector(e, Prop_Send, "m_vecMaxs", Float:{50.0, 50.0, 50.0})
	SetEntPropVector(e, Prop_Send, "m_vecSpecifiedSurroundingMins", Float:{-50.0, -50.0, -50.0})
	SetEntPropVector(e, Prop_Send, "m_vecSpecifiedSurroundingMaxs", Float:{50.0, 50.0, 50.0})
	SetEntPropVector(e, Prop_Data, "m_vecSurroundingMins", Float:{-50.0, -50.0, -50.0})
	SetEntPropVector(e, Prop_Data, "m_vecSurroundingMaxs", Float:{50.0, 50.0, 50.0})
	Format(s, 12, "th_%i", b)
	DispatchKeyValue(b, "targetname", s);
	SetEntPropString(e, Prop_Data, "m_sMaster", s)
	TeleportEntity(e, NULL_VECTOR, Float:{30.0,0.0,0.0}, F, NULL_VECTOR);
	SetEntityLifeTime(e, f)*/
}


/* Sliver Storm Plugins */

stock int CreateClouds()
{
	int entity = FindEntityByClassname(-1, "sky_camera"), i;
	if(entity != -1 )
	{
		float vPos[3];
		GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", vPos);

		i = CreateEntityByName("info_particle_system");
		PrecacheParticle("storm_cloud_parent")
		DispatchKeyValue(i, "effect_name", "storm_cloud_parent");
		DispatchKeyValue(i, "targetname", "silver_fx_skybox_general_lightning");
		DispatchSpawn(i);
		ActivateEntity(i);
		AcceptEntityInput(i, "Start");
		TeleportEntity(i, vPos, NULL_VECTOR, NULL_VECTOR);
	}
	return i
}

stock CreateSkyCamera(int color1, int color2)
{
	new g_iSkyCamera = FindEntityByClassname(-1, "sky_camera")
	if(g_iSkyCamera != -1)
	{
		int iSkyCamData[5];
		float fSkyCamData[5];

		iSkyCamData[0] = GetEntProp(g_iSkyCamera, Prop_Data, "m_bUseAngles");
		iSkyCamData[1] = GetEntProp(g_iSkyCamera, Prop_Data, "m_skyboxData.scale");
		iSkyCamData[2] = GetEntProp(g_iSkyCamera, Prop_Data, "m_skyboxData.bClip3DSkyBoxNearToWorldFar");
		iSkyCamData[3] = GetEntProp(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.blend");
		iSkyCamData[4] = GetEntProp(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.enable");
		fSkyCamData[0] = GetEntPropFloat(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.start");
		fSkyCamData[1] = GetEntPropFloat(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.end");
		fSkyCamData[2] = GetEntPropFloat(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.maxdensity");
		fSkyCamData[3] = GetEntPropFloat(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.HDRColorScale");
		fSkyCamData[4] = GetEntPropFloat(g_iSkyCamera, Prop_Data, "m_skyboxData.flClip3DSkyBoxNearToWorldFarOffset");

		float vAng[3], vPos[3];
		GetEntPropVector(g_iSkyCamera, Prop_Data, "m_vecAbsOrigin", vPos);
		GetEntPropVector(g_iSkyCamera, Prop_Data, "m_angRotation", vAng);
		AcceptEntityInput(g_iSkyCamera, "Kill");


		g_iSkyCamera = CreateEntityByName("sky_camera");

		SetEntProp(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.colorPrimary", color1);
		SetEntProp(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.colorSecondary", color2);
		SetEntProp(g_iSkyCamera, Prop_Data, "m_bUseAngles", iSkyCamData[0]);
		SetEntProp(g_iSkyCamera, Prop_Data, "m_skyboxData.scale", iSkyCamData[1]);
		SetEntProp(g_iSkyCamera, Prop_Data, "m_skyboxData.bClip3DSkyBoxNearToWorldFar", iSkyCamData[2]);
		SetEntProp(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.blend", iSkyCamData[3]);
		SetEntProp(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.enable", iSkyCamData[4]);
		SetEntPropFloat(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.start", fSkyCamData[0]);
		SetEntPropFloat(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.end", fSkyCamData[1]);
		SetEntPropFloat(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.maxdensity", fSkyCamData[2]);
		SetEntPropFloat(g_iSkyCamera, Prop_Data, "m_skyboxData.fog.HDRColorScale", fSkyCamData[3]);
		SetEntPropFloat(g_iSkyCamera, Prop_Data, "m_skyboxData.flClip3DSkyBoxNearToWorldFarOffset", fSkyCamData[4]);

		TeleportEntity(g_iSkyCamera, vPos, vAng, NULL_VECTOR);
		DispatchSpawn(g_iSkyCamera);
		AcceptEntityInput(g_iSkyCamera, "ActivateSkybox");
	}
}

stock int CreateFog()
{
	char sTemp[8];
	new e = -1;
	while((e = FindEntityByClassname(e, "env_fog_controller")) != -1)
	{
		/*if( count < MAX_FOG )
		{
			GetEntPropString(entity, Prop_Data, "m_iName", g_sFogStolen[count], 64);
			g_iFogStolen[count][0] = EntIndexToEntRef(entity);
			g_iFogStolen[count][1] = GetEntProp(entity, Prop_Send, "m_fog.colorPrimary");
			g_iFogStolen[count][2] = GetEntProp(entity, Prop_Send, "m_fog.colorSecondary");
			g_iFogStolen[count][3] = GetEntProp(entity, Prop_Send, "m_fog.colorPrimaryLerpTo");
			g_iFogStolen[count][4] = GetEntProp(entity, Prop_Send, "m_fog.colorSecondaryLerpTo");
			g_fFogStolen[count][0] = GetEntPropFloat(entity, Prop_Send, "m_fog.start");
			g_fFogStolen[count][1] = GetEntPropFloat(entity, Prop_Send, "m_fog.end");
			g_fFogStolen[count][2] = GetEntPropFloat(entity, Prop_Send, "m_fog.maxdensity");
			g_fFogStolen[count][3] = GetEntPropFloat(entity, Prop_Send, "m_fog.farz");
			g_fFogStolen[count][4] = GetEntPropFloat(entity, Prop_Send, "m_fog.skyboxFogFactor");
			g_fFogStolen[count][5] = GetEntPropFloat(entity, Prop_Send, "m_fog.startLerpTo");
			g_fFogStolen[count][6] = GetEntPropFloat(entity, Prop_Send, "m_fog.endLerpTo");
			g_fFogStolen[count][7] = GetEntPropFloat(entity, Prop_Send, "m_fog.maxdensityLerpTo");
			g_fFogStolen[count][8] = GetEntPropFloat(entity, Prop_Send, "m_fog.duration");
			count++;
		}*/
		SetEntPropFloat(e, Prop_Send, "m_fog.start", 0.0);
		SetEntPropFloat(e, Prop_Send, "m_fog.end", 1000.0);
		SetEntPropFloat(e, Prop_Send, "m_fog.farz", 1000.0);
		DispatchKeyValue(e, "use_angles", "1");
		DispatchKeyValue(e, "fogmaxdensity", "1");
		DispatchKeyValue(e, "heightFogStart", "0.0");
		DispatchKeyValue(e, "heightFogMaxDensity", "1.0");
		DispatchKeyValue(e, "heightFogDensity", "0.0");
		DispatchKeyValue(e, "fogdir", "1 0 0");
		DispatchKeyValue(e, "angles", "0 180 0");
		
		IntToString(4, sTemp, sizeof(sTemp));
		DispatchKeyValue(e, "foglerptime", sTemp);

		DispatchKeyValue(e, "fogcolor", "0 0 0");
		DispatchKeyValue(e, "fogcolor2", "0 0 0");
		SetVariantString("0 0 0");
		AcceptEntityInput(e, "SetColorLerpTo");
	}
	e = FindEntityByClassname(-1, "fog_volume")
	AcceptEntityInput(e, "Disable");
	AcceptEntityInput(e, "Enable");
	return 0
		/*g_iFog = CreateEntityByName("env_fog_controller");
		if( g_iFog != -1 )
		{
			DispatchKeyValue(g_iFog, "targetname", "silver_fog_storm");
			DispatchKeyValue(g_iFog, "use_angles", "1");
			SetEntPropFloat(g_iFog, Prop_Send, "m_fog.start", 0.0);
			SetEntPropFloat(g_iFog, Prop_Send, "m_fog.end", 1000.0);
			DispatchKeyValue(g_iFog, "fogmaxdensity", "1.0");
			DispatchKeyValue(g_iFog, "heightFogStart", "0.0");
			DispatchKeyValue(g_iFog, "heightFogMaxDensity", "1.0");
			DispatchKeyValue(g_iFog, "heightFogDensity", "0.0");
			DispatchKeyValue(g_iFog, "fogenable", "1");
			DispatchKeyValue(g_iFog, "fogdir", "1 0 0");
			DispatchKeyValue(g_iFog, "angles", "0 180 0");

			IntToString(4, sTemp, sizeof(sTemp));
			DispatchKeyValue(g_iFog, "foglerptime", sTemp);

			IntToString(1200, sTemp, sizeof(sTemp));
			DispatchKeyValue(g_iFog, "farz", sTemp);

			//if( strcmp(g_sCfgFogColor, "") )
			//{
			DispatchKeyValue(g_iFog, "fogcolor", "10 15 20");
			DispatchKeyValue(g_iFog, "fogcolor2", "10 15 20");
			//}

			DispatchSpawn(g_iFog);
			ActivateEntity(g_iFog);
			AcceptEntityInput(g_iFog, "TurnOn")

			//TeleportEntity(g_iFog, Float:{10.0, 15.0, 20.0}, NULL_VECTOR, NULL_VECTOR);
		}
		return g_iFog*/
}

/*stock int CreateRain()
{
	new entity = CreateEntityByName("func_precipitation");
	if( entity != -1 )
	{
		char buffer[128];
		GetCurrentMap(buffer, sizeof(buffer));
		Format(buffer, sizeof(buffer), "maps/%s.bsp", buffer);

		DispatchKeyValue(entity, "model", buffer);
		DispatchKeyValue(entity, "targetname", "silver_rain");
		IntToString(4, buffer, sizeof(buffer));
		DispatchKeyValue(entity, "preciptype", buffer);
		
		DispatchKeyValue(entity, "minSpeed", "25");
		DispatchKeyValue(entity, "maxSpeed", "35");
		DispatchKeyValue(entity, "renderfx", "21");
		DispatchKeyValue(entity, "rendercolor", "31 34 52");
		DispatchKeyValue(entity, "renderamt", "100");

		float vMins[3], vMaxs[3];
		GetEntPropVector(0, Prop_Data, "m_WorldMins", vMins);
		GetEntPropVector(0, Prop_Data, "m_WorldMaxs", vMaxs);
		SetEntPropVector(entity, Prop_Send, "m_vecMins", vMins);
		SetEntPropVector(entity, Prop_Send, "m_vecMaxs", vMaxs);

		float vBuff[3];
		vBuff[0] = vMins[0] + vMaxs[0];
		vBuff[1] = vMins[1] + vMaxs[1];
		vBuff[2] = vMins[2] + vMaxs[2];

		DispatchSpawn(entity);
		ActivateEntity(entity);
		TeleportEntity(entity, vBuff, NULL_VECTOR, NULL_VECTOR);
	}
	return entity
}

stock int CreateSnow()
{
	new entity = CreateEntityByName("func_precipitation");
	char buffer[128];
	GetCurrentMap(buffer, sizeof(buffer));
	Format(buffer, sizeof(buffer), "maps/%s.bsp", buffer);
	DispatchKeyValue(entity, "model", buffer);
	DispatchKeyValue(entity, "targetname", "silver_snow");
	DispatchKeyValue(entity, "preciptype", "3");
	DispatchKeyValue(entity, "renderamt", "100");
	DispatchKeyValue(entity, "rendercolor", "200 200 200");

	float vBuff[3], vMins[3], vMaxs[3];
	GetEntPropVector(0, Prop_Data, "m_WorldMins", vMins);
	GetEntPropVector(0, Prop_Data, "m_WorldMaxs", vMaxs);
	//SetEntPropVector(entity, Prop_Send, "m_vecMins", vMins);
	//SetEntPropVector(entity, Prop_Send, "m_vecMaxs", vMaxs);
	vBuff[0] = vMins[0] + vMaxs[0];
	vBuff[1] = vMins[1] + vMaxs[1];
	vBuff[2] = vMins[2] + vMaxs[2];

	new a = GetRandomClient()
	if(a) GetClientAbsOrigin(a, vBuff);
	DispatchSpawn(entity);
	ActivateEntity(entity);
	TeleportEntity(entity, vBuff, NULL_VECTOR, NULL_VECTOR);
	return entity
}*/

// ***** End *****

stock DisplayHint(a, const String:text[], const String:icon[], time, const String:bind[]="")
{
	int e
	while((e = FindEntityByClassname(e, "env_instructor_hint")) != -1)
	{
		if(GetEntPropEnt(e, Prop_Data, "m_hOwnerEntity") == a)
		{
			//AcceptEntityInput(e, "EndHint")
			//RemoveEntity(e)
			break
		}
	}
	if(e == -1)
	{
		e = CreateEntityByName("env_instructor_hint")
		char s[32]
		//e = CreateEntityByName("env_instructor_hint")
		Format(s, 32, "hint%i", EntIndexToEntRef(e))
		DispatchKeyValue(a, "targetname", s);
		DispatchKeyValue(e, "hint_target", s);
		DispatchKeyValue(e, "hint_range", "0.01");
		DispatchKeyValue(e, "hint_color", "250 195 219");
		DispatchSpawn(e);
		SetEntPropEnt(e, Prop_Data, "m_hOwnerEntity", a)
		SetEntityLifeTime(e, float(time))
	}
	/*new e, String:s[32]
	GetEntPropString(a, Prop_Data, "m_iName", s, 32)
	if(!(e = StrContains(s, "hint")) && (e = EntRefToEntIndex(StringToInt(s[e+4]))) > 0) */
	
	SetEntProp(e, Prop_Data, "m_iTimeout", time)
	DispatchKeyValue(e, "hint_allow_nodraw_target", "1");
	DispatchKeyValue(e, "hint_auto_start", "1");
	DispatchKeyValue(e, "hint_icon_onscreen", icon);
	DispatchKeyValue(e, "hint_caption", text);
	DispatchKeyValue(e, "hint_binding", bind);
	DispatchKeyValue(e, "hint_instance_type", "0");
	DispatchKeyValue(e, "hint_static", "0");
	
	AcceptEntityInput(e, "ShowHint", a);
}

stock DisplayHintTarget(a, b, const String:text[], const String:icon[], time, const String:bind[]="")
{
	int e
	while((e = FindEntityByClassname(e, "info_target")) != -1)
	{
		if(GetEntPropEnt(e, Prop_Data, "m_hOwnerEntity") == a)
		{
			//AcceptEntityInput(e, "EndHint")
			//RemoveEntity(e)
			break
		}
	}
	if(e == -1)
	{
		e = CreateEntityByName("info_target")
		char s[32]
		//e = CreateEntityByName("env_instructor_hint")
		Format(s, 32, "hint%i", EntIndexToEntRef(e))
		DispatchKeyValue(a, "targetname", s);
		DispatchKeyValue(e, "hint_target", s);
		DispatchKeyValue(e, "hint_range", "0.01");
		DispatchKeyValue(e, "hint_color", "250 195 219");
		DispatchSpawn(e);
	}
	/*new e, String:s[32]
	GetEntPropString(a, Prop_Data, "m_iName", s, 32)
	if(!(e = StrContains(s, "hint")) && (e = EntRefToEntIndex(StringToInt(s[e+4]))) > 0) */
	
	SetEntProp(e, Prop_Data, "m_iTimeout", time)
	DispatchKeyValue(e, "hint_icon_onscreen", icon);
	DispatchKeyValue(e, "hint_caption", text);
	DispatchKeyValue(e, "hint_binding", bind);
	
	AcceptEntityInput(e, "ShowHint", a);
	SetEntPropEnt(e, Prop_Data, "m_hOwnerEntity", a)
	SetEntityLifeTime(e, float(time))
}

stock int GetBreakablePropType(a)
{
	return GetEntData(a, m_iPropType, 1)
}

stock any[] GetCharacterCount(b=0)
{
	int a[8], l, i
	for(i = 1;i <= MaxClients;i++)
	{
		if(i != b && IsClientInTeam(i, 2))
		{
			if((l = GetPlayerCharacter(i)) < 8) a[l]++;
		}
	}
	return a
}

stock int GetClientAttacker(a, bool:s=true)
{
	int b
	static m_pummelAttacker = -1
	if(m_pummelAttacker == -1) m_pummelAttacker = FindSendPropInfo("CTerrorPlayer", "m_pummelAttacker")
	if((b = GetEntDataEnt2(a, m_pummelAttacker)) != -1) return b
	static m_carryAttacker = -1
	if(m_carryAttacker == -1) m_carryAttacker = FindSendPropInfo("CTerrorPlayer", "m_carryAttacker")
	if((b = GetEntDataEnt2(a, m_carryAttacker)) != -1) return b
	static m_jockeyAttacker = -1
	if(m_jockeyAttacker == -1) m_jockeyAttacker = FindSendPropInfo("CTerrorPlayer", "m_jockeyAttacker")
	if((b = GetEntDataEnt2(a, m_jockeyAttacker)) != -1) return b
	static m_pounceAttacker = -1
	if(m_pounceAttacker == -1) m_pounceAttacker = FindSendPropInfo("CTerrorPlayer", "m_pounceAttacker")
	if((b = GetEntDataEnt2(a, m_pounceAttacker)) != -1) return b
	if(s)
	{
		static m_tongueOwner = -1
		if(m_tongueOwner == -1) m_tongueOwner = FindSendPropInfo("CTerrorPlayer", "m_tongueOwner")
		if((b = GetEntDataEnt2(a, m_tongueOwner)) != -1) return b
	}
	// int b = GetEntPropEnt(a, Prop_Send, "m_pummelAttacker")
	// if(b != -1 || (b = GetEntPropEnt(a, Prop_Send, "m_carryAttacker")) != -1 || (b = GetEntPropEnt(a, Prop_Send, "m_jockeyAttacker")) != -1 || (b = GetEntPropEnt(a, Prop_Send, "m_pounceAttacker")) != -1 || (s && (b = GetEntPropEnt(a, Prop_Send, "m_tongueOwner")) != -1/* && (!s || GetGameTime()>GetEntPropFloat(b, Prop_Send, "m_tongueVictimTimer", 0))*/)) return b
	return 0;
}

stock float GetClientHealthBuffer(a)
{
	float f = GetEntPropFloat(a, Prop_Send, "m_healthBuffer") - ((GetGameTime()-GetEntPropFloat(a, Prop_Send, "m_healthBufferTime"))*GS_CvarFloat("pain_pills_decay_rate"))
	return f < 0.0 ? 0.0 : f
}

stock int GetClientVictim(a)
{
	int b
	static m_pummelVictim = -1
	if(m_pummelVictim == -1) m_pummelVictim = FindSendPropInfo("CTerrorPlayer", "m_pummelVictim")
	if((b = GetEntDataEnt2(a, m_pummelVictim)) != -1) return b
	static m_carryVictim = -1
	if(m_carryVictim == -1) m_carryVictim = FindSendPropInfo("CTerrorPlayer", "m_carryVictim")
	if((b = GetEntDataEnt2(a, m_carryVictim)) != -1) return b
	static m_jockeyVictim = -1
	if(m_jockeyVictim == -1) m_jockeyVictim = FindSendPropInfo("CTerrorPlayer", "m_jockeyVictim")
	if((b = GetEntDataEnt2(a, m_jockeyVictim)) != -1) return b
	static m_pounceVictim = -1
	if(m_pounceVictim == -1) m_pounceVictim = FindSendPropInfo("CTerrorPlayer", "m_pounceVictim")
	if((b = GetEntDataEnt2(a, m_pounceVictim)) != -1) return b
	static m_tongueVictim = -1
	if(m_tongueVictim == -1) m_tongueVictim = FindSendPropInfo("CTerrorPlayer", "m_tongueVictim")
	if((b = GetEntDataEnt2(a, m_tongueVictim)) != -1) return b
	//int b = GetEntPropEnt(a, Prop_Send, "m_pummelVictim")
	//if(b != -1 || (b = GetEntPropEnt(a, Prop_Send, "m_carryVictim")) != -1 || (b = GetEntPropEnt(a, Prop_Send, "m_jockeyVictim")) != -1 || (b = GetEntPropEnt(a, Prop_Send, "m_pounceVictim")) != -1 || (b = GetEntPropEnt(a, Prop_Send, "m_tongueVictim")) != -1) return b
	return 0;
}

stock float GetEntityCreatedTime(e)
{
	return GetGameTime()-GetEntPropFloat(e, Prop_Data, "m_flCreateTime")
}

/*stock float GetEntityDamageModifier(a, b, i)
{
	if(0 < a <= MaxClients)
	{
		if(GetClientTeam(a) == 2 && GetClientTeam(b) == 2) return 0.35*GetFriendlyFireFactor()
		if(GetPlayerZombieClass(a) == TANK) return 1.0
	}
	return GetHitboxDamageModifier(i)
}*/

stock int GetEntityLifeState(e)
{
	static m_lifeState = -1
	if(m_lifeState == -1) m_lifeState = FindSendPropInfo("CTerrorPlayer", "m_lifeState")
	return GetEntData(e, m_lifeState, 1)
}

// Easy
// Normal
// Hard
// Impossible

stock float GetFriendlyFireFactor()
{
	static ConVar z_difficulty
	if(!z_difficulty) z_difficulty = FindConVar("z_difficulty")
	char s[64]
	z_difficulty.GetString(s, 64)
	if(s[3] == 'o') s = "expert"
	Format(s, 64, "survivor_friendly_fire_factor_%s", s)
	return GetConVarFloat(FindConVar(s))
}

// #define HitGroup_Head 1

stock float GetHitboxDamageModifier(int i, float a=4.0, float b=1.25, float c=0.75)
{
	switch(i)
	{
		case 1: return a
		case 3: return b
		case 4, 5, 6, 7: return c
	}
	return 1.0
}

stock int GetHumanSpectator(a)
{
	return GetClientOfUserId(GetEntProp(a, Prop_Send, "m_humanSpectatorUserID"));
}

stock int GetMainActivity(a)
{
	return LoadFromAddress(Address:(GetEntData(a, 10512)+276), NumberType_Int32)
}

stock float GetRadiusDamage(a, c, float l, float d)
{
	return (l-GetEntityDistance(a, c))*(d/l)
}

stock int GetSurvivorBot(a)
{
	int e = GetEntPropEnt(a, Prop_Data, "m_hObserverTarget")
	return e != -1 && IsFakeClient(e) && IsSurvivorBot(e) && GetEntProp(e, Prop_Send, "m_humanSpectatorUserID") == GetClientUserId(a) ? e : 0
	/*for(new i=1;i<33;i++)
	{
		if(IsClientInTeam(i, 2) && IsSurvivorBot(i) && GetHumanSpectator(i) == a) return i
	}
	return 0*/
}

/*stock int GetWeaponClipSize(a)
{
	char s[64]
	GetEdictClassname(a, s, 64)
	new i = GetWeaponAttribute(s, IWA_ClipSize)
	if(!strcmp(s, "weapon_pistol") && GetEntProp(a, Prop_Send, "m_hasDualWeapons")) i*=2
	return i
}*/

stock int GetZombieClassHealth(a)
{
	new String:s[40]
	switch(GetEntProp(a,Prop_Send,"m_zombieClass"))
	{
		case SMOKER: s = "z_gas_health";
		case BOOMER: s = "z_exploding_health";
		case HUNTER: s = "z_hunter_health";
		case SPITTER: s = "z_spitter_health";
		case JOCKEY: s = "z_jockey_health";
		case CHARGER: s = "z_charger_health";
		case WITCH: s = "z_witch_health";
		case TANK: s = "z_tank_health";
	}
	return GetConVarInt(FindConVar(s))
}

stock bool HasLeftStartArea()
{
	int a = FindEntityByClassname(-1, "terror_player_manager")
	return a != -1 && GetEntProp(a, Prop_Send, "m_hasAnySurvivorLeftSafeArea")
}

stock bool IsCharging(a)
{
	if(GetPlayerZombieClass(a) != CHARGER) return false
	static m_isCharging = -1
	if(m_isCharging == -1) m_isCharging = FindSendPropInfo("CCharge", "m_isCharging")
	return !!GetEntData(GetPlayerZombieAbility(a), m_isCharging)
}
stock bool IsChargingEx(a)
{
	static m_isCharging = -1
	if(m_isCharging == -1) m_isCharging = FindSendPropInfo("CCharge", "m_isCharging")
	return !!GetEntData(GetPlayerZombieAbility(a), m_isCharging)
}

stock bool IsCheckpointDoor(a)	// -1 = any checkpoint door, 0 = start, 1 = last
{
	return FindDataMapInfo(a, "m_hasUnlockSequence") != -1 && !LoadFromAddress(GetEntityAddress(a)+view_as<Address>(6092), NumberType_Int8) 
}

stock bool IsDanger(a)
{
	if(GetEntPropFloat(a, Prop_Send, "m_staggerTimer", 1) != -1.0 || GetEntProp(a, Prop_Send, "m_isHangingFromTongue") || GetEntProp(a, Prop_Send, "m_isHangingFromLedge") || GetClientAttacker(a, false)) return true
	int i = GetMainActivity(a)
	//PrintToChat(a, "%i", i)
	switch(i)
	{
		case 521,522,523,524,525,526,530,529,771,779: return true
	}
	// switch(i)
	// {
		// case 770,771,775,779,783,799/*,528,529,534*/: return true
	// }
	// return (521 <= i <= 535) || (710 <= i <= 713) // 
	return false
	/*if(i > 530)
	{
		if(i == 771) return false
	}
	else if(i >= 529 || 521= < i <= 526) return false*/
	//return true
}

stock bool IsExplosive(e)
{
	// char m[40], s[64]
	// GetEdictClassname(e, m, 40)
	// GetEntityModel(e, s, 64)
	// return !strcmp(m[5], "physics") && (StrContains(s, "propanecanister") > 0 || StrContains(s, "oxygentank") > 0 || StrContains(s, "explosive_box") > 0)
	char m[40]
	GetEdictClassname(e, m, 40)
	if(!strcmp(m, "prop_physics"))
	{
		switch(GetEntData(e, m_iPropType, 1))
		{
			case PropType_FireCrate, PropType_PropTank: return true
		}
	}
	return false
}

stock bool IsGasCan(e, int b=-1)
{
	/*char m[40]
	GetEdictClassname(e, m, 40)
	return !strcmp(m, "prop_physics") && GetEntData(e, m_iPropType, 1) == PropType_GasCan && (b == -1 || GetEntitySkin(e) == b)*/
	char m[40]
	GetEdictClassname(e, m, 40)
	if(strcmp(m[5], "physics") && strcmp(m[7], "gascan")) return false
	char s[64]
	GetEntityModel(e, s, 64)
	return !strcmp(s, "models/props_junk/gascan001a.mdl") && (b == -1 || GetEntitySkin(e) == b)
}

stock bool IsIncap(a)
{
	static m_isIncapacitated = -1
	if(m_isIncapacitated == -1) m_isIncapacitated = FindSendPropInfo("CTerrorPlayer", "m_isIncapacitated")
	return GetEntData(a, m_isIncapacitated, 1) != 0
	//return GetEntProp(a, Prop_Send, "m_isIncapacitated") != 0
}

stock bool IsLeaker(a)
{
	if(GetPlayerZombieClass(a) != 2) return false
	static m_nVariantType = -1
	if(m_nVariantType == -1) m_nVariantType = FindSendPropInfo("CTerrorPlayer", "m_nVariantType")
	return GetEntData(a, m_nVariantType, 1) == 1
}
stock bool IsLeakerEx(a)
{
	static m_nVariantType = -1
	if(m_nVariantType == -1) m_nVariantType = FindSendPropInfo("CTerrorPlayer", "m_nVariantType")
	return GetEntData(a, m_nVariantType, 1) == 1
}

stock bool IsLunging(a)
{
	switch(GetPlayerZombieClass(a))
	{
		case HUNTER:
		{
			/*static m_pounceVictim = -1
			if(m_pounceVictim == -1) m_pounceVictim = FindSendPropInfo("CTerrorPlayer", "m_pounceVictim")
			if(GetEntDataEnt2(a, m_pounceVictim) != -1) return false*/
			static m_isAttemptingToPounce = -1
			if(m_isAttemptingToPounce == -1) m_isAttemptingToPounce = FindSendPropInfo("CTerrorPlayer", "m_isAttemptingToPounce")
			return GetEntData(a, m_isAttemptingToPounce, 1) != 0
		}
		case JOCKEY:
		{
			if(GetEntityFlags(a)&FL_ONGROUND || GetEntityMoveType(a) != MOVETYPE_WALK) return false
			static m_jockeyVictim = -1
			if(m_jockeyVictim == -1) m_jockeyVictim = FindSendPropInfo("CTerrorPlayer", "m_jockeyVictim")
			if(GetEntDataEnt2(a, m_jockeyVictim) != -1) return false
			static m_nextActivationTimer = -1
			if(m_nextActivationTimer == -1) m_nextActivationTimer = FindSendPropInfo("CLeap", "m_nextActivationTimer")+8
			//PrintToChat(a, "%f %f %f", GetEntDataFloat(GetPlayerZombieAbility(a), 1096), GetEntDataFloat(GetPlayerZombieAbility(a), 1128), GetEntDataFloat(GetPlayerZombieAbility(a), 1112)-GetGameTime())
			return GetGameTime() > GetEntDataFloat(GetPlayerZombieAbility(a), m_nextActivationTimer)
		}
	}
	return false
	
	//return (i == HUNTER && GetEntProp(GetEntPropEnt(a, Prop_Send, "m_customAbility"), Prop_Send, "m_isLunging")) || (i == JOCKEY && !(GetEntityFlags(a)&FL_ONGROUND)) 
	//return ((i == HUNTER && GetEntProp(a, Prop_Send, "m_pounceVictim") == -1) || (i == JOCKEY && GetEntProp(a, Prop_Send, "m_jockeyVictim") == -1)) && GetEntData(GetPlayerZombieAbility(a), 1148)
}

stock bool IsMountedGun(a)
{
	return FindDataMapInfo(a, "m_maxYaw") != -1
}

stock bool IsPlayerGhost(a)
{
	static m_isGhost = -1
	if(m_isGhost == -1) m_isGhost = FindSendPropInfo("CTerrorPlayer", "m_isGhost")
	return !!GetEntData(a, m_isGhost, 1)
}

stock bool IsSurvivorBot(a)
{
	static char incBuffer[12]
	GetEntityNetClass(a, incBuffer, 12)
	return !strcmp(incBuffer, "SurvivorBot")
}

stock bool IsWitch(a)
{
	char s[12]
	GetEdictClassname(a, s, 12)
	return !strcmp(s, "witch")
}

stock SetClientHealthBuffer(a, float f)
{
	SetEntPropFloat(a, Prop_Send, "m_healthBuffer", f)
	SetEntPropFloat(a, Prop_Send, "m_healthBufferTime", GetGameTime())
}
// Get and Set
enum /*L4D2_Gender*/
{
	Gender_Neutral			= 0,
	Gender_Male				= 1,
	Gender_Female			= 2,
	Gender_Nanvet			= 3, //Bill
	Gender_TeenGirl			= 4, //Zoey
	Gender_Biker			= 5, //Francis
	Gender_Manager			= 6, //Louis
	Gender_Gambler			= 7, //Nick
	Gender_Producer			= 8, //Rochelle
	Gender_Coach			= 9, //Coach
	Gender_Mechanic			= 10, //Ellis
	Gender_Ceda				= 11,
	Gender_Mudman			= 12, //Mudman
	Gender_Roadcrew			= 13, //Workman (class not reacting to the pipe bomb)
	Gender_Fallen			= 14,
	Gender_Riot				= 15, //RiotCop
	Gender_Clown			= 16,
	Gender_Jimmy			= 17, //JimmyGibbs
	Gender_Hospital_Patient	= 18,
	Gender_Witch_Bride		= 19,
	Gender_Police			= 20, //l4d1 RiotCop (was removed from the game)
	Gender_Male_L4D1		= 21,
	Gender_Female_L4D1		= 22,
	
	Gender_MaxSize //23 size
};

stock int GetEntityGender(a)
{
	static m_Gender = -1
	if(m_Gender == -1) m_Gender = FindSendPropInfo("CBaseEntity", "m_Gender");
	return GetEntData(a, m_Gender)
}
stock SetEntityGender(a, i)
{
	static m_Gender = -1
	if(m_Gender == -1) m_Gender = FindSendPropInfo("CBaseEntity", "m_Gender");
	SetEntData(a, m_Gender, i)
}

stock int GetEntitySkin(a)
{
	static m_nSkin = -1
	if(m_nSkin == -1) m_nSkin = FindSendPropInfo("CBaseAnimating", "m_nSkin");
	return GetEntData(a, m_nSkin)
}
stock SetEntitySkin(a, i)
{
	static m_nSkin = -1
	if(m_nSkin == -1) m_nSkin = FindSendPropInfo("CBaseAnimating", "m_nSkin");
	SetEntData(a, m_nSkin, i)
}

stock int GetEntityTeamNum(a)
{
	static m_iTeamNum = -1
	if(m_iTeamNum == -1) m_iTeamNum = FindSendPropInfo("CBaseEntity", "m_iTeamNum");
	return GetEntData(a, m_iTeamNum)
}
stock SetEntityTeamNum(a, i)
{
	static m_iTeamNum = -1
	if(m_iTeamNum == -1) m_iTeamNum = FindSendPropInfo("CBaseEntity", "m_iTeamNum");
	SetEntData(a, m_iTeamNum, i)
}

stock float GS_WeaponNextAttackTime(a, float b=-1.0)
{
	static m_flNextPrimaryAttack = -1
	if(m_flNextPrimaryAttack == -1) m_flNextPrimaryAttack = FindSendPropInfo("CBaseCombatWeapon", "m_flNextPrimaryAttack");
	if(b >= 0.0) SetEntDataFloat(a, m_flNextPrimaryAttack, b)
	return GetEntDataFloat(a, m_flNextPrimaryAttack)
}

stock int GetPlayerCharacter(a)
{
	static m_survivorCharacter = -1
	if(m_survivorCharacter == -1) m_survivorCharacter = FindSendPropInfo("CTerrorPlayer", "m_survivorCharacter");
	return GetEntData(a, m_survivorCharacter)
}
stock SetPlayerCharacter(a, b)
{
	static m_survivorCharacter = -1
	if(m_survivorCharacter == -1) m_survivorCharacter = FindSendPropInfo("CTerrorPlayer", "m_survivorCharacter");
	SetEntData(a, m_survivorCharacter, b)
}

stock int GetPlayerFOV(a)
{
	/*static Handle hGetFOV
	if(!hGetFOV)
	{
		StartPrepSDKCall(SDKCall_Player) 
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN11CBasePlayer6GetFOVEv", 0);
		PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain)
		hGetFOV = EndPrepSDKCall()
	}
	return SDKCall(hGetFOV, a)*/
	static m_iFOV = -1
	if(m_iFOV == -1) m_iFOV = FindSendPropInfo("CTerrorPlayer", "m_iFOV")
	return GetEntData(a, m_iFOV, 2)
}
stock SetPlayerFOV(a, b)
{
	static m_iFOV = -1
	if(m_iFOV == -1) m_iFOV = FindSendPropInfo("CTerrorPlayer", "m_iFOV")
	SetEntData(a, m_iFOV, b)
}

stock int GetPlayerZombieClass(a)
{
	static m_zombieClass = -1
	if(m_zombieClass == -1) m_zombieClass = FindSendPropInfo("CTerrorPlayer", "m_zombieClass");
	return GetEntData(a, m_zombieClass)
}
stock SetPlayerZombieClass(a, i)
{
	static m_zombieClass = -1
	if(m_zombieClass == -1) m_zombieClass = FindSendPropInfo("CTerrorPlayer", "m_zombieClass");
	SetEntData(a, m_zombieClass, i)
}

stock int GetPlayerZombieAbility(a)
{
	static m_customAbility = -1
	if(m_customAbility == -1) m_customAbility = FindSendPropInfo("CTerrorPlayer", "m_customAbility");
	return GetEntDataEnt2(a, m_customAbility)
}
stock SetPlayerZombieAbility(a, b)
{
	static m_customAbility = -1
	if(m_customAbility == -1) m_customAbility = FindSendPropInfo("CTerrorPlayer", "m_customAbility");
	SetEntDataEnt2(a, m_customAbility, b)
}

stock int GetSequence(a)
{
	static m_nSequence = -1
	if(m_nSequence == -1) m_nSequence = FindDataMapInfo(a, "m_nSequence");
	return GetEntData(a, m_nSequence, 2)
}
stock SetSequence(a, b)
{
	static m_nSequence = -1
	if(m_nSequence == -1) m_nSequence = FindDataMapInfo(a, "m_nSequence");
	SetEntData(a, m_nSequence, b, 2)
}

stock int GetTankFrustration(a)
{
	static m_frustration = -1
	if(m_frustration == -1) m_frustration = FindSendPropInfo("CTerrorPlayer", "m_frustration");
	return GetEntData(a, m_frustration, 1)
}
stock SetTankFrustration(a, i)
{
	static m_frustration = -1
	if(m_frustration == -1) m_frustration = FindSendPropInfo("CTerrorPlayer", "m_frustration");
	SetEntData(a, m_frustration, i, 1)
}

stock GetWeaponOwner(a)
{
	static m_hOwner = -1
	if(m_hOwner == -1) m_hOwner = FindDataMapInfo(a, "m_hOwner");
	return GetEntDataEnt2(a, m_hOwner)
}

stock SetWeaponHelpingHandState(w, i)
{
	static m_helpingHandState = -1
	if(m_helpingHandState == -1) m_helpingHandState = FindSendPropInfo("CTerrorWeapon", "m_helpingHandState")
	SetEntData(w, m_helpingHandState, i, 1)
}
// Extra Functag
stock Action:EmitBurstSound(Handle:h, e)
{
	PlayGameSound(0, "c2m5.fireworks_burst", e)
}
