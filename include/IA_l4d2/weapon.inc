enum
{
	PISTOL = 1,       // 1
	SMG,              // 2
	PUMPSHOTGUN,      // 3
	AUTOSHOTGUN,      // 4
	RIFLE,            // 5
	HUNTING_RIFLE,    // 6
	SMG_SILENCED,     // 7
	SHOTGUN_CHROME,   // 8
	RIFLE_DESERT,     // 9
	SNIPER_MILITARY,  // 10
	SHOTGUN_SPAS,     // 11
	FIRST_AID_KIT,    // 12
	MOLOTOV,          // 13
	PIPE_BOMB,        // 14
	PAIN_PILLS,       // 15
	GASCAN,           // 16
	PROPANE_TANK,     // 17
	OXYGEN_TANK,      // 18
	MELEE,            // 19
	CHAINSAW,         // 20
	GRENADE_LAUNCHER, // 21
	AMMO_PACK2,       // 22
	ADRENALINE,       // 23
	DEFIBRILLATOR,    // 24
	VOMITJAR,         // 25
	RIFLE_AK47,       // 26
	GNOME_CHOMPSKI,   // 27
	COLA_BOTTLES,     // 28
	FIREWORKS_BOX,    // 29
	INCENDIARY_AMMO,  // 30
	FRAG_AMMO,        // 31
	PISTOL_MAGNUM,    // 32
	SMG_MP5,          // 33
	RIFLE_SG552,      // 34
	SNIPER_AWP,       // 35
	SNIPER_SCOUT,     // 36
	M60,			  // 37
	TANK_CLAW,        // 38
	HUNTER_CLAW,      // 39
	CHARGER_CLAW,     // 40
	BOOMER_CLAW,      // 41
	SMOKER_CLAW,      // 42
	SPITTER_CLAW,     // 43
	JOCKEY_CLAW,      // 44
	MACHINEGUN,       // 45
	VOMIT,            // 46
	SPLAT,            // 47
	POUNCE,           // 48
	LOUNGE,           // 49
	PULL,             // 50
	CHOKE,            // 51
	ROCK,             // 52
	PHYSICS,          // 53
	AMMO_PACK,		  // 54
	UPGRADE_ITEM      // 55
};



// weaponclass
// #define WEAPON_MELEE			"weapon_melee"
// #define WEAPON_PISTOL			"weapon_pistol"
// #define WEAPON_PISTOL_MAGNUM	"weapon_pistol_magnum"      
// #define WEAPON_SMG				"weapon_smg"
// #define WEAPON_SMG_SILENCED		"weapon_smg_silenced"
// #define WEAPON_HUNTING_RIFLE	"weapon_hunting_rifle"
// #define WEAPON_SNIPER_MILITARY	"weapon_sniper_military"
// #define WEAPON_PUMPSHOTGUN		"weapon_pumpshotgun"
// #define WEAPON_SHOTGUN_CHROME	"weapon_shotgun_chrome"
// #define WEAPON_AUTOSHOTGUN		"weapon_autoshotgun"
// #define WEAPON_SHOTGUN_SPAS		"weapon_shotgun_spas"
// #define WEAPON_RIFLE			"weapon_rifle"
// #define WEAPON_RIFLE_DESERT		"weapon_rifle_desert"
// #define WEAPON_RIFLE_AK47		"weapon_rifle_ak47"
// #define WEAPON_MOLOTOV			"weapon_molotov"
// #define WEAPON_PIPE_BOMB		"weapon_pipe_bomb"
// #define WEAPON_VOMITJAR			"weapon_vomitjar"
// #define WEAPON_GRENADE_LAUNCHER	"weapon_grenade_launcher"
// #define WEAPON_RIFLE_M60		"weapon_rifle_m60"
// #define WEAPON_SMG_MP5			"weapon_smg_mp5"
// #define WEAPON_RIFLE_SG552		"weapon_rifle_sg552"
// #define WEAPON_SNIPER_AWP		"weapon_sniper_awp"
// #define WEAPON_SNIPER_SCOUT		"weapon_sniper_scout"
// #define WEAPON_FIRST_AID_KIT	"weapon_first_aid_kit"
// #define WEAPON_PAIN_PILLS		"weapon_pain_pills"
// #define WEAPON_ADRENALINE		"weapon_adrenaline"
// #define WEAPON_MACHINEGUN		"weapon_machinegun"

// AMMO_TYPE
#define AMMO_PISTOL			1
#define AMMO_PISTOL_MAGNUM	2
#define AMMO_ASSAULTRIFLE	3
#define AMMO_SMG			5
#define AMMO_M60			6
#define AMMO_SHOTGUN		7
#define AMMO_AUTOSHOTGUN	8
#define AMMO_HUNTINGRIFLE	9
#define AMMO_SNIPERRIFLE	10
#define AMMO_PIPEBOMB		12
#define AMMO_MOLOTOV		13
#define AMMO_VOMITJAR		14
#define AMMO_PAIN_PILLS		15
#define AMMO_FIRST_AID		16
#define AMMO_GRENADELAUNCHER	17
#define AMMO_ADRENALINE		18
#define AMMO_CHAINSAW		19
#define AMMO_OTHER			20

stock bool WeaponID_IsGun(id)
{
	if(1 <= id <= 11 || 32 <= id <= 37 || id == GRENADE_LAUNCHER || id == RIFLE_AK47) return true
	return false
}
// models
//#define SMG_MP5_M			"models/w_models/weapons/w_smg_mp5.mdl"
//#define RIFLE_SG552_M		"models/w_models/weapons/w_rifle_sg552.mdl"
//#define SNIPER_AWP_M		"models/w_models/weapons/w_sniper_awp.mdl"
//#define SNIPER_SCOUT_M		"models/w_models/weapons/w_sniper_scout.mdl"
//#define SNIPER_AWP_V		"models/v_models/v_snip_awp.mdl"

stock int CreateWeaponSpawn(id, count, const Float:x[3]=NULL_VECTOR, const Float:y[3]=NULL_VECTOR)
{
	new e = CreateEntityByName("weapon_spawn");
	SetEntityWeapon(e, id)
	DispatchKeyValue(e, "targetname", "IA_weapon_spawn");
	TeleportEntity(e, x, y, NULL_VECTOR)
	DispatchKeyValueInt(e, "count", count);
	DispatchSpawn(e);
	return e
}

stock int GetMeleeWeaponID(int a)
{
	static m_hMeleeWeaponInfo = -1
	if(m_hMeleeWeaponInfo == -1) m_hMeleeWeaponInfo = FindSendPropInfo("CTerrorMeleeWeapon", "m_hMeleeWeaponInfo")
	return GetEntData(a, m_hMeleeWeaponInfo)
}

stock GetMeleeWeaponName(int a, char[]s, l)
{
	GetEntPropString(a, Prop_Data, "m_strMapSetScriptName", s, l)
}

stock bool IsAmmoSpawn(a)
{
	int i = FindDataMapInfo(a, "m_weaponID")
	return i != -1 && GetEntData(a, i) == 54
}

stock bool IsFullyAutomatic(a)
{
	switch(GetEntProp(a, Prop_Data, "m_iPrimaryAmmoType"))
	{
		case AMMO_ASSAULTRIFLE,AMMO_SMG,AMMO_M60,AMMO_AUTOSHOTGUN: return true
	}
	return false
}

stock bool IsTool(a)
{
	int i = FindDataMapInfo(a, "m_iPrimaryAmmoType")
	return i != -1 && GetEntData(a, i) == AMMO_OTHER
}

stock bool IsUpgradeSpawn(a)
{
	int i = FindDataMapInfo(a, "m_weaponID")
	return i != -1 && GetEntData(a, i) == 55
}

stock bool IsWeapon(a)
{
	int i = FindDataMapInfo(a, "m_iPrimaryAmmoType")
	return i != -1 && (0 < GetEntData(a, i) || FindDataMapInfo(a, "m_strMapSetScriptName") != -1)
}

stock bool IsWeaponGun(a)
{
	int i = FindDataMapInfo(a, "m_iPrimaryAmmoType")
	if(i == -1) return false
	switch(GetEntData(a, i))
	{
		case AMMO_PISTOL,AMMO_PISTOL_MAGNUM,AMMO_ASSAULTRIFLE,AMMO_SMG,AMMO_M60,AMMO_SHOTGUN,AMMO_AUTOSHOTGUN,AMMO_HUNTINGRIFLE,AMMO_SNIPERRIFLE,AMMO_GRENADELAUNCHER: return true
	}
	return false
}

stock bool IsWeaponGunReload(a)
{
	static m_bInReload = -1
	if(m_bInReload == -1) m_bInReload = FindSendPropInfo("CBaseCombatWeapon", "m_bInReload")
	return GetEntData(a, m_bInReload, 1) != 0
}

stock bool IsWeaponMelee(a)
{
	return FindDataMapInfo(a, "m_strMapSetScriptName") != -1
}

stock bool IsWeaponSpawn(a)
{
	int i = FindDataMapInfo(a, "m_weaponID")
	if(i == -1) return false
	switch((i = GetEntData(a, i, 1)))
	{
		case GASCAN,PROPANE_TANK,OXYGEN_TANK,AMMO_PACK2,GNOME_CHOMPSKI,COLA_BOTTLES,FIREWORKS_BOX: return false
	}
	return i < 38
}

stock bool IsWeaponMeleeSpawn(a)
{
	return FindDataMapInfo(a, "m_iszMeleeWeapon") != -1
}

stock int GetWeaponSpawnID(a)
{
	static m_weaponID = -1
	if(m_weaponID == -1) m_weaponID = FindDataMapInfo(a, "m_weaponID")
	return GetEntData(a, m_weaponID, 1);
}
stock SetWeaponSpawnID(a, i)
{
	static m_weaponID = -1
	if(m_weaponID == -1) m_weaponID = FindDataMapInfo(a, "m_weaponID")
	SetEntData(a, m_weaponID, i, 1);
}

stock GetWeaponClassFromID(i, String:s[], l)
{
	strcopy(s, l, "_")
	switch(i)
	{
		case MELEE: strcopy(s, l, "weapon_melee")
		case PISTOL_MAGNUM: strcopy(s, l, "weapon_pistol_magnum")
		case PISTOL: strcopy(s, l, "weapon_pistol")
		case CHAINSAW: strcopy(s, l, "weapon_chainsaw")
		case SNIPER_AWP: strcopy(s, l, "weapon_sniper_awp")
		case SNIPER_SCOUT: strcopy(s, l, "weapon_sniper_scout")
		case RIFLE_SG552: strcopy(s, l, "weapon_rifle_sg552")
		case SMG_MP5: strcopy(s, l, "weapon_smg_mp5")
		case AUTOSHOTGUN: strcopy(s, l, "weapon_autoshotgun")
		case SHOTGUN_SPAS: strcopy(s, l, "weapon_shotgun_spas")
		case PUMPSHOTGUN: strcopy(s, l, "weapon_pumpshotgun")
		case SHOTGUN_CHROME: strcopy(s, l, "weapon_shotgun_chrome")
		case SMG_SILENCED: strcopy(s, l, "weapon_smg_silenced")
		case SMG: strcopy(s, l, "weapon_smg")
		case HUNTING_RIFLE: strcopy(s, l, "weapon_hunting_rifle")
		case SNIPER_MILITARY: strcopy(s, l, "weapon_sniper_military")
		case RIFLE_AK47: strcopy(s, l, "weapon_rifle_ak47")
		case RIFLE_DESERT: strcopy(s, l, "weapon_rifle_desert")
		case M60: strcopy(s, l, "weapon_rifle_m60")
		case RIFLE: strcopy(s, l, "weapon_rifle")
		case GRENADE_LAUNCHER: strcopy(s, l, "weapon_grenade_launcher")
		case PIPE_BOMB: strcopy(s, l, "weapon_pipe_bomb")
		case MOLOTOV: strcopy(s, l, "weapon_molotov")
		case VOMITJAR: strcopy(s, l, "weapon_vomitjar")
		case FIRST_AID_KIT: strcopy(s, l, "weapon_first_aid_kit")
		case DEFIBRILLATOR: strcopy(s, l, "weapon_defibrillator")
		case INCENDIARY_AMMO: strcopy(s, l, "weapon_upgradepack_incendiary")
		case FRAG_AMMO: strcopy(s, l, "weapon_upgradepack_explosive")
		case PAIN_PILLS: strcopy(s, l, "weapon_pain_pills")
		case ADRENALINE: strcopy(s, l, "weapon_adrenaline")
	}
}

stock int GetWeaponIDFromClass(const String:s[])
{
	if(StrContains(s, "weapon_")) return 0
	if(!strcmp(s[7], "melee")) return MELEE
	if(!strcmp(s[7], "pistol_magnum")) return PISTOL_MAGNUM
	if(!strcmp(s[7], "pistol")) return PISTOL
	if(!strcmp(s[7], "chainsaw")) return CHAINSAW
	if(!strcmp(s[7], "sniper_awp")) return SNIPER_AWP
	if(!strcmp(s[7], "sniper_scout")) return SNIPER_SCOUT
	if(!strcmp(s[7], "rifle_sg552")) return RIFLE_SG552
	if(!strcmp(s[7], "smg_mp5")) return SMG_MP5
	if(!strcmp(s[7], "autoshotgun")) return AUTOSHOTGUN
	if(!strcmp(s[7], "shotgun_spas")) return SHOTGUN_SPAS
	if(!strcmp(s[7], "pumpshotgun")) return PUMPSHOTGUN
	if(!strcmp(s[7], "shotgun_chrome")) return SHOTGUN_CHROME
	if(!strcmp(s[7], "smg_silenced")) return SMG_SILENCED
	if(!strcmp(s[7], "smg")) return SMG
	if(!strcmp(s[7], "hunting_rifle")) return HUNTING_RIFLE
	if(!strcmp(s[7], "sniper_military")) return SNIPER_MILITARY
	if(!strcmp(s[7], "rifle_ak47")) return RIFLE_AK47
	if(!strcmp(s[7], "rifle_desert")) return RIFLE_DESERT
	if(!strcmp(s[7], "rifle_m60")) return M60
	if(!strcmp(s[7], "rifle")) return RIFLE
	if(!strcmp(s[7], "grenade_launcher")) return GRENADE_LAUNCHER
	if(!strcmp(s[7], "pipe_bomb")) return PIPE_BOMB
	if(!strcmp(s[7], "molotov")) return MOLOTOV
	if(!strcmp(s[7], "vomitjar")) return VOMITJAR
	if(!strcmp(s[7], "first_aid_kit")) return FIRST_AID_KIT
	if(!strcmp(s[7], "defibrillator")) return DEFIBRILLATOR
	if(!strcmp(s[7], "upgradepack_incendiary")) return INCENDIARY_AMMO
	if(!strcmp(s[7], "upgradepack_explosive")) return FRAG_AMMO
	if(!strcmp(s[7], "pain_pills")) return PAIN_PILLS
	if(!strcmp(s[7], "adrenaline")) return ADRENALINE
	return 0
}

/*stock int GetWeaponType(a)
{
	switch(GetEntProp(a, Prop_Data, "m_iPrimaryAmmoType"))
	{
		case AMMO_PISTOL,AMMO_PISTOL_MAGNUM: return WT_Pistol
		case AMMO_SMG, AMMO_ASSAULTRIFLE: return WT_FullAuto
		case AMMO_SHOTGUN, AMMO_AUTOSHOTGUN: return WT_Shotgun
		case AMMO_HUNTINGRIFLE, AMMO_SNIPERRIFLE: return WT_Sniper
		// AMMO_M60,AMMO_GRENADELAUNCHER: return true
	}
}*/

stock SetEntityWeapon(a, i)
{
	switch(i)
	{
		case SNIPER_SCOUT: SetEntityModelEx(a, "models/w_models/weapons/w_sniper_scout.mdl");
		case SNIPER_AWP: SetEntityModelEx(a, "models/w_models/weapons/w_sniper_awp.mdl");
		case RIFLE_SG552: SetEntityModelEx(a, "models/w_models/weapons/w_rifle_sg552.mdl");
		case SMG_MP5: SetEntityModelEx(a, "models/w_models/weapons/w_smg_mp5.mdl");
		case PISTOL_MAGNUM: SetEntityModel(a, "models/w_models/weapons/w_desert_eagle.mdl");
		case RIFLE_AK47: SetEntityModel(a, "models/w_models/weapons/w_rifle_ak47.mdl");
		case VOMITJAR: SetEntityModel(a, "models/w_models/weapons/w_eq_bile_flask.mdl");
		case PIPE_BOMB: SetEntityModel(a, "models/w_models/weapons/w_eq_pipebomb.mdl");
		case MOLOTOV: SetEntityModel(a, "models/w_models/weapons/w_eq_molotov.mdl");
		case SHOTGUN_SPAS: SetEntityModel(a, "models/w_models/weapons/w_shotgun_spas.mdl");
		case SNIPER_MILITARY: SetEntityModel(a, "models/w_models/weapons/w_sniper_military.mdl");
		case RIFLE_DESERT: SetEntityModel(a, "models/w_models/weapons/w_desert_rifle.mdl");
		case SHOTGUN_CHROME: SetEntityModel(a, "models/w_models/weapons/w_pumpshotgun_a.mdl");
		case SMG_SILENCED: SetEntityModel(a, "models/w_models/weapons/w_smg_a.mdl");
		case HUNTING_RIFLE: SetEntityModel(a, "models/w_models/weapons/w_sniper_mini14.mdl");
		case RIFLE: SetEntityModel(a, "models/w_models/weapons/w_rifle_m16a2.mdl");
		case AUTOSHOTGUN: SetEntityModel(a, "models/w_models/weapons/w_autoshot_m4super.mdl");
		case PUMPSHOTGUN: SetEntityModel(a, "models/w_models/weapons/w_shotgun.mdl");
		case SMG: SetEntityModel(a, "models/w_models/weapons/w_smg_uzi.mdl");
		case PISTOL: SetEntityModel(a, "models/w_models/weapons/w_pistol_a.mdl");
		case FIRST_AID_KIT: SetEntityModel(a, "models/w_models/weapons/w_eq_Medkit.mdl");
		case DEFIBRILLATOR: SetEntityModel(a, "models/w_models/weapons/w_eq_defibrillator.mdl");
		case PAIN_PILLS: SetEntityModel(a, "models/w_models/weapons/w_eq_painpills.mdl");
		case ADRENALINE: SetEntityModel(a, "models/w_models/weapons/w_eq_adrenaline.mdl");
		case GRENADE_LAUNCHER: SetEntityModel(a, "models/w_models/weapons/w_grenade_launcher.mdl");
		case M60: SetEntityModel(a, "models/w_models/weapons/w_m60.mdl");
		case INCENDIARY_AMMO: SetEntityModel(a, "models/w_models/weapons/w_eq_incendiary_ammopack.mdl");
		case FRAG_AMMO: SetEntityModel(a, "models/w_models/weapons/w_eq_explosive_ammopack.mdl");
		case CHAINSAW: SetEntityModel(a, "models/weapons/melee/w_chainsaw.mdl");
		case AMMO_PACK: SetEntityModel(a, "models/props/terror/ammo_stack.mdl");
	}
	int id = FindDataMapInfo(a, "m_weaponID")
	if(id != -1) SetEntData(a, id, i, 1);
}

stock int GetWeaponAmmoType(a)
{
	static m_iPrimaryAmmoType = -1
	if(m_iPrimaryAmmoType == -1) m_iPrimaryAmmoType = FindSendPropInfo("CTerrorWeapon", "m_iPrimaryAmmoType")
	return GetEntData(a, m_iPrimaryAmmoType)
}
stock SetWeaponAmmoType(a, int i)
{
	static m_iPrimaryAmmoType = -1
	if(m_iPrimaryAmmoType == -1) m_iPrimaryAmmoType = FindSendPropInfo("CTerrorWeapon", "m_iPrimaryAmmoType")
	SetEntData(a, m_iPrimaryAmmoType, i)
}

/*stock int GetWeaponGroup(a)
{
	int i = FindDataMapInfo(a, "m_weaponID") == -1?GetWeaponID(a):GetEntProp(a, Prop_Data, "m_weaponID")
	switch(i)
	{
		case 26, 21: return 0
		case 1, 32, 19, 20: return 1
		case 13, 14, 25: return 2
		case 12, 24, 30, 31: return 3
		case 15, 23: return 4
	}
	if((i > 1 && i < 12) || (i > 32 && i < 38)) return 0;
	return -1;
}*/

/*stock int GetWeaponIDGroup(i)
{
	switch(i)
	{
		case 26, 21: return 0
		case 1, 32, 19, 20: return 1
		case 13, 14, 25: return 2
		case 12, 24, 30, 31: return 3
		case 15, 23: return 4
	}
	if((i > 1 && i < 12) || (i > 32 && i < 38)) return 0;
	return -1;
}*/

stock bool HasDualGun(a)
{
	static m_hasDualWeapons = -1
	if(m_hasDualWeapons == -1) m_hasDualWeapons = FindSendPropInfo("CTerrorGun", "m_hasDualWeapons")
	return GetEntData(a, m_hasDualWeapons, 1) != 0
}

stock bool HasDualWeapons(a)
{
	return GetWeaponAmmoType(a) == AMMO_PISTOL && HasDualGun(a)
}

stock int MeleeNameToID(const char[]n)
{
	new table = FindStringTable("MeleeWeapons"), l = GetStringTableNumStrings(table)
	char s[40]
	while(l--)
	{
		ReadStringTable(table, l, s, 40);
		if(!strcmp(s, n)) return l
	}
	return -1
}

stock int ReplaceWeapon(a, i, c=-1)
{
	float e[3], f[3]
	GetEntPropVector(a, Prop_Data, "m_vecAbsOrigin", e)
	GetEntPropVector(a, Prop_Data, "m_angRotation", f)
	if(c < 0) c = GetEntProp(a, Prop_Data, "m_itemCount")
	RemoveEntity(a)
	a = CreateEntityByName("weapon_spawn")
	if(a < 1) return 0;
	SetEntityWeapon(a, i)
	SetEntProp(a, Prop_Data, "m_itemCount", c)
	DispatchKeyValue(a, "targetname", "IA_replaced");
	TeleportEntity(a, e, f, NULL_VECTOR)
	DispatchSpawn(a)
	return a
}

// Get and Set
stock int GetWeaponClip(int weapon)
{
	static m_iClip1 = -1
	if(m_iClip1 == -1) m_iClip1 = FindDataMapInfo(weapon, "m_iClip1")
	int i = GetEntData(weapon, m_iClip1)
	return i == 254 ? 0 : i
}
stock SetWeaponClip(int weapon, int nums)
{
	static m_iClip1 = -1
	if(m_iClip1 == -1) m_iClip1 = FindDataMapInfo(weapon, "m_iClip1")
	SetEntData(weapon, m_iClip1, nums)
}

stock int GetWeaponAmmo(e, a=0)
{
	if(a > 0)
	{
		int b = GetWeaponAmmoType(e);
		if(b != -1) return GetEntProp(a, Prop_Send, "m_iAmmo", _, b);
	}
	else return GetEntProp(e, Prop_Send, "m_iExtraPrimaryAmmo")
	return 0
}
stock SetWeaponAmmo(e, i, a=0)
{
	if(i < 0) ThrowError("Can't set weapon ammo to lower than 0 (%i)", i)
	if(a > 0)
	{
		int b = GetWeaponAmmoType(e);
		if(b != -1) SetEntProp(a, Prop_Send, "m_iAmmo", i, _, b);
	}
	else SetEntProp(e, Prop_Send, "m_iExtraPrimaryAmmo", i)
}
