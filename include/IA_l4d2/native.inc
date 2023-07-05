#define RIOT_MODEL				"models/infected/common_male_riot.mdl"
#define CEDA_MODEL				"models/infected/common_male_ceda.mdl"
#define CLOWN_MODEL				"models/infected/common_male_clown.mdl"
#define MUD_MODEL				"models/infected/common_male_mud.mdl"
#define ROADCREW_MODEL			"models/infected/common_male_roadcrew.mdl"
#define JIMMY_MODEL				"models/infected/common_male_jimmy.mdl"
#define FALLEN_SURIVOR_MODEL	"models/infected/common_male_fallen_survivor.mdl"

enum InfectType
{
	IT_NORMAL,IT_RIOT,IT_CEDA,IT_CLOWN,IT_MUDMAN,IT_ROADCREW,IT_JIMMY,IT_FALLEN
}

enum ICTimer
{
	ICTimer_Mob,ICTimer_Smoker,ICTimer_Boomer,ICTimer_Hunter,ICTimer_Spitter,ICTimer_Jockey,ICTimer_Charger
}

// #define WpnType_Pistol	0
// #define WpnType_Smg		1
// #define WpnType_Rifle	2
// #define WpnType_Shotgun	3
// #define WpnType_Sniper	4

// Weapon Extra Attributes
#define IWEA_Loading					-1
#define IWEA_SpawnCount					-2
#define IWEA_MaxAmmo					-3
#define IWEA_MultiBarrel				-4
#define IWEA_DamageFlags				-5
#define IWEA_ShoveBurstDamage			-6
#define IWEA_SkinCount					-7
// #define IWEA_AmmoType					-8
#define IWEA_LaserBeam					-9
#define IWEA_ExplodeDamage				-10

#define FWEA_ReloadDuration					-51
#define FWEA_RealReloadDuration				-52
#define FWEA_EmptyReloadDuration			-53
#define FWEA_ReloadSpeed				-54
#define FWEA_EmptyRealReloadDuration		-55
#define FWEA_DualRealReloadDuration			-56
#define FWEA_DualEmptyRealReloadDuration	-57
#define FWEA_DeployDuration					-58
#define FWEA_DualDeployDuration				-59
#define FWEA_RealReloadEndTime			-60
#define FWEA_Weight						-61
#define FWEA_AmmoWeight					-62
#define FWEA_DeploySpeed				-63
#define FWEA_FireSpeed					-64
#define	FWEA_ShoveBurst					-65
#define FWEA_SwingDuration				-66
#define FWEA_ExplodeRadius				-67
#define	FWEA_DamageForce				-68

#define SWEA_Name						-100
#define SWEA_Base						-101
#define SWEA_AmmoType					-102

#define CFG_Pov				(1<<0)
#define CFG_PovGod			(1<<1)
#define CFG_Hop				(1<<2)
#define CFG_Trail			(1<<3)
#define CFG_Announcement	(1<<4)
#define CFG_Legs			(1<<5)
#define CFG_VoiceBlock		(1<<6)
#define CFG_AutoReload		(1<<7)
#define CFG_AttachmentHide	(1<<8)
#define CFG_AntiHurtOff		(1<<9)
#define CFG_AttachmentOff	(1<<10)
#define CFG_EnableFireAntiHurt	(1<<11)
#define CFG_OldSwitch		(1<<12)
#define CFG_BulletImpact	(1<<13)

#define BOTCMD_ATTACK	0
#define BOTCMD_MOVE	1
#define BOTCMD_RETREAT	2
#define BOTCMD_RESET	3

#define BOMB_DamageType 134217792

enum Checkpoint
{
	CheckPoint_Initial = 0,
	CheckPoint_Last,
	CheckPoint_Normal
}


forward Action OnChangeFinaleStage(int &finaleType, const char[]arg)

forward Action OnEndVersusModeRound()

/**
 * @brief Call when an entity create.
 *
 * @param		entity		Entity index
 * @param		name		Entity classname
 * @param		coord		Entity spawn location
 * @param		angle		Entity spawn angle
 */
forward Action OnEntityCreate(int entity, const String:name[], const Float:coord[3], const Float:angle[3])

/**
 * @brief Call when attacker hit a entity.
 *
 * @param		entity		Entity index
 * @param		attacker	Attack index
 * @param		dmg			Damage hit
 * @param		dmg_type	Damage type
 * @param		health		Remaining health
 */
forward void OnEntityHurt(int entity, int attacker, int dmg, int type, int health, int weapon)

forward Action OnFirstSurvivorLeftSafeArea(int &client)

forward void OnFirstSurvivorHasLeftSafeArea(int client)

forward void OnCreatePipeBombPost(int entity, int client)

forward void OnReadyFinished()

/*
 * @remarks	sequences(punches): 40(uppercut), 43(right hook), 45(left hook), 46 and 47 (pounding the ground)
 * @remarks	sequences(throws): 48(undercut), 49(1handed overhand), 50(throw from the hip), 51(2handed overhand)
 */
forward Action OnSelectTankAttack(int client, int &sequence)

forward Action OnSpawnMob(int &nums, bool it)

forward Action OnSpawnSpecial(int class)

forward void OnSurvivorDominated(int victim, int attacker)

native CommandABot(a, i, b=0, const float f[3]={0.0,0.0,0.0})

native int CreateInfected(InfectType a=IT_NORMAL, float pos[3]=NULL_VECTOR, float ang[3]=NULL_VECTOR)

native int CreateInferno(const float f1[3], const float f2[3], int client)

native int CreateMolotovProjectile(const float f1[3], const float f2[3], const float f3[3], const float f4[3], int client)

native void DetonateMolotov(int entity)

native bool FindValidSpawnPosition(const float f[3], float F[3], bool b=true)

native void FlingPlayer(int client, int attacker, float vel[3], float time=3.0)

native int GetClientConfig(int client)

native float GetCurrentFlowDistance()

native int GetCustomWeaponAttribute(int entity, const char[]s, int def=0)
native float GetCustomWeaponAttributeFloat(int entity, const char[]s, float def=0.0)

native float GetFlowDistance(int entity, int i=0)

#define GameMode_Coop		0
#define GameMode_Survival	1
#define GameMode_Versus		2
#define GameMode_Scavenge	3

native int GetGameMode()

native GetHitboxPosition(int entity, i, float f[3], float F[3]={0.0,...})

native CTimer GetInfectedSpawnCountdownTimer(ICTimer a)

native float GetMaxFlowDistance()

native any GetMeleeWeaponAttribute(int id, int attr, int slot=0, int tableid=0);

native int GetMvpPlayer()

enum PointerTypes
{
	Pointer_CDirector,
	Pointer_CAmmoDef,
	Pointer_ZombieManager
}
native Address GetPointer(PointerTypes i)

/**
 * @brief Get the map survivor set. 1 = l4d1, 2 = l4d2
 */
native int GetSurvivorSet();

native void GetSpawnPosition(Checkpoint i, float origin[3]=NULL_VECTOR, float angles[3]=NULL_VECTOR, int &NavArea=0)

native int GetSurvivorDeathModel(int client)

native void GetTwoWeapon(int client, int slot, String:bufer[40])

native any GetWeaponAttribute(const char[]weapon, int attr);

native any GetWeaponAttributeEx(int weapon, int attr);

native GetWeaponAttributeString(const char[]weapon, int attr, char[]value, int len, int slot=0, int tableid=0);

native int GetWeaponID(int weapon)

native GetWeaponName(int weapon, char name[40])

native GetWeaponNameEx(int weapon, char[]name, int len)

native int GetWeaponSlot(int weapon)

native bool IsEntityInCheckpoint(int entity, Checkpoint i)

native bool IsInCombat(int client);

native bool IsReachable(int client, const float origin[3])

native PatchMemory(const char[]sig, offset, patch, const char[]code="", const char[]dll="server")

native ResetWeaponAttribute(const char[]weapon, int attr=0)

native ResetWeaponSoundData(const char[]weapon)

native SetMeleeWeaponAttribute(int meleeid, int attr, any value, int slot=0, int tableid=0)

native SetWeaponAttribute(const char[]weapon, int attr, any:value);

native SetWeaponAttributeString(const char[]weapon, int attr, const char[]value, int slot=0, int tableid=0);

native SetWeaponSoundData(const char[]weapon, KeyValues k)

native SwitchTwoWeapon(int client, int slot)

enum
{
	SPAutoType_Auto = -1,
	SPAutoType_Off
}
/**
 * @brief Spawn special infected
 * 
 */
native int SpawnSpecialInfected(int class, int entity, const float pos[3]=NULL_VECTOR, const float ang[3]=NULL_VECTOR, int clientAs=0,int annouce=0)

native StaggerPlayer(int victim, int attacker, const float v[3]=NULL_VECTOR, float len=-1.0)

stock AddAttrCommon(KeyValues h, const char[]s)
{
	int i
	float f
	char t[64]
	if((i = h.GetNum("Damage", -1)) >= 0) SetWeaponAttribute(s, IWA_Damage, i)
	if((i = h.GetNum("clip_size", -1)) >= 0) SetWeaponAttribute(s, IWA_ClipSize, i), SetWeaponAttribute(s, IWA_DefaultClip, i)
	if((i = h.GetNum("Tier", -1)) >= 0) SetWeaponAttribute(s, IWA_Tier, i)
	if((i = h.GetNum("Bullets", -1)) >= 0) SetWeaponAttribute(s, IWA_Bullets, i)
	if((i = h.GetNum("AmmoIndex")) > 0) SetWeaponAttribute(s, IWA_AmmoIndex, i)
	if((i = h.GetNum("Loading", -1)) >= 0) SetWeaponAttribute(s, IWEA_Loading, i)
	if((i = h.GetNum("SpawnCount", -1)) >= 0) SetWeaponAttribute(s, IWEA_SpawnCount, i)
	if((i = h.GetNum("MaxAmmo", -1)) >= 0) SetWeaponAttribute(s, IWEA_MaxAmmo, i)
	if((i = h.GetNum("SkinCount", -1)) >= 0) SetWeaponAttribute(s, IWEA_SkinCount, i)
	if((i = h.GetNum("ExplodeDamage", -1)) >= 0) SetWeaponAttribute(s, IWEA_ExplodeDamage, i)
	if((i = h.GetNum("PenetrationNumLayers", -1)) >= 0) SetWeaponAttribute(s, IWA_PenetrationNumLayers, i)
	h.GetString("DamageFlags", t, sizeof(t))
	if(t[0]) SetWeaponAttribute(s, IWEA_DamageFlags, StringToBit(t))

	if((f = h.GetFloat("CycleTime", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_CycleTime , f)
	if((f = h.GetFloat("VerticalPunch", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_VerticalPunch, f)
	if((f = h.GetFloat("HorizontalPunch", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_HorizontalPunch, f)
	if((f = h.GetFloat("SpreadPerShot", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_SpreadPerShot, f)
	if((f = h.GetFloat("MaxSpread", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_MaxSpread, f)
	if((f = h.GetFloat("SpreadDecay", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_SpreadDecay, f)
	if((f = h.GetFloat("MinDuckingSpread", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_MinDuckingSpread, f)
	if((f = h.GetFloat("MinStandingSpread", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_MinStandingSpread, f)
	if((f = h.GetFloat("MinInAirSpread", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_MinInAirSpread, f)
	if((f = h.GetFloat("MaxMovementSpread", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_MaxMovementSpread, f)
	if((f = h.GetFloat("Range", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_Range, f)
	if((f = h.GetFloat("GainRange", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_GainRange, f)
	if((f = h.GetFloat("RangeModifier", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_RangeModifier, f)
	if((f = h.GetFloat("PenetrationPower", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_PenetrationPower, f)
	if((f = h.GetFloat("PelletScatterPitch", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_PelletScatterPitch, f)
	if((f = h.GetFloat("PelletScatterYaw", -1.0)) >= 0.0) SetWeaponAttribute(s, FWA_PelletScatterYaw, f)

	if((f = h.GetFloat("ReloadDuration", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_ReloadDuration, f)
	if((f = h.GetFloat("EmptyReloadDuration", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_EmptyReloadDuration, f)
	if((f = h.GetFloat("RealReloadDuration", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_RealReloadDuration, f)
	if((f = h.GetFloat("DualRealReloadDuration", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_DualRealReloadDuration, f)
	if((f = h.GetFloat("EmptyRealReloadDuration", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_EmptyRealReloadDuration, f)
	if((f = h.GetFloat("DualEmptyRealReloadDuration", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_DualEmptyRealReloadDuration, f)
	if((f = h.GetFloat("ReloadSpeed", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_ReloadSpeed, f)
	if((f = h.GetFloat("DeployDuration", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_DeployDuration, f)
	if((f = h.GetFloat("DualDeployDuration", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_DualDeployDuration, f)
	if((f = h.GetFloat("RealReloadEndTime", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_RealReloadEndTime, f)
	if((f = h.GetFloat("DeploySpeed", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_DeploySpeed, f)
	if((f = h.GetFloat("FireSpeed", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_FireSpeed, f)
	if((f = h.GetFloat("SwingDuration", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_SwingDuration, f)
	if((f = h.GetFloat("Weight", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_Weight, f)
	if((f = h.GetFloat("AmmoWeight", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_AmmoWeight, f)
	if((f = h.GetFloat("ExplodeRadius", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_ExplodeRadius, f)
	if((f = h.GetFloat("DamageForce", -1.0)) >= 0.0) SetWeaponAttribute(s, FWEA_DamageForce, f)
}
