#include <sourcemod>
#include <sourcescramble>

enum PatchType
{
	PatchType_PlainData,
	PatchType_Pointer
}

enum VariantType
{
	VariantType_Int,
	VariantType_Float
}

#define ListOrder_MemPatch		0
#define ListOrder_PatchType		1
#define ListOrder_VariantType	2
#define ListOrder_MemBlock		3

ArrayList hMemoryPatchList
StringMap hConVarMemPatchList//, hConVarMemPatch, hConVarMemBlock, hConVarMemType, hConVarVariantType
GameData hGameData

public Plugin:myinfo =
{
	name = "More ConVar",
	author = "IA/NanaNana",
	description = "Give more and more ConVar",
	version = "1.0",
	url = "https://steamcommunity.com/profiles/76561198291983872"
}

public OnPluginStart()
{
	hMemoryPatchList = new ArrayList()
	/*hConVarMemPatch = new StringMap()
	hConVarMemBlock = new StringMap()
	hConVarMemType = new StringMap()
	hConVarVariantType = new StringMap()*/
	hConVarMemPatchList = new StringMap()
	
	hGameData = new GameData("IA_more_convar")
	
	// Add new convar in here.
	CreateConVarPatch(VariantType_Float, "ItemGiveDistance", "IA_item_give_distance", "256.0", "How far a survivor can give item to other")
	CreateConVarPatch(VariantType_Float, "SlammedSurvivorDamageNormal", "z_charger_slammed_dmg_normal", "10.0", "A damage amount of charger slammed a survivor in normal")
	CreateConVarPatch(VariantType_Float, "SlammedSurvivorDamageHard", "z_charger_slammed_dmg_hard", "15.0", "A damage amount of charger slammed a survivor in hard")
	CreateConVarPatch(VariantType_Float, "SlammedSurvivorDamageExpert", "z_charger_slammed_dmg_expert", "20.0", "A damage amount of charger slammed a survivor in expert")
	CreateConVarPatch(VariantType_Float, "FriendlyFireScaleBase", "survivor_friendly_fire_factor_base", "0.35", "FF damage of easy-hard scale by this")
	CreateConVarPatch(VariantType_Float, "SpecialsSpawnDelay", "director_special_spawn_delay", "20.0", "director special spawn delay")
	CreateConVarPatch(VariantType_Float, "SpecialsSpawnDelay2", "director_special_spawn_delay")
	CreateConVarPatch(VariantType_Float, "SpecialsSpawnDelay3", "director_special_spawn_delay")
	
	CreateConVarPatch(VariantType_Float, "SpecialsSpawnDelayFail", "director_special_spawn_delay_fail", "5.0", "Reset spawn delay when fail to spawn special")
	CreateConVarPatch(VariantType_Float, "SpecialsSpawnDelayFail2", "director_special_spawn_delay_fail")
	CreateConVarPatch(VariantType_Float, "SpecialsSpawnDelayFail3", "director_special_spawn_delay_fail")
	
	CreateConVarPatch(VariantType_Float, "ChargerTakeDamage", "z_charger_takedamage_scale_charging", "0.333", "Charger take damage scale by this when charging")
	
	// AutoExecConfig(true, "IA_more_convar")
	
	hGameData.Close()
}

public OnPluginEnd()
{
	for(int i=hMemoryPatchList.Length-1;i>=0;i--)
	{
		view_as<MemoryPatch>(hMemoryPatchList.Get(i)).Disable()
	}
}

/*CreateMemoryPatch(GameData h, const char[]s)
{
	MemoryPatch p = MemoryPatch.CreateFromConf(h, s)
	if(p)
	{
		hMemoryPatchList.Push(p)
		
	}
	else LogError("MemPatches ItemGiveDistance invalid.");
}*/

CreateConVarPatch(VariantType vt,
	const char[] section,
	const char[] name,
	const char[] defaultValue="",
	const char[] description="",
	int flags=0,
	bool hasMin=false, float min=0.0,
	bool hasMax=false, float max=0.0)
{
	MemoryPatch p = MemoryPatch.CreateFromConf(hGameData, section)
	if(!p)
	{
		LogError("MemPatches %s not found.", section);
		return
	}
	if(p.Enable())
	{
		hMemoryPatchList.Push(p)
		// Get patch type
		PatchType type
		Address addr = p.Address
		
		ArrayList list
		if(!hConVarMemPatchList.GetValue(name, list))
		{
			list = new ArrayList(4)
			hConVarMemPatchList.SetValue(name, list)
		}
		int l = list.Length
		list.Resize(l+1)
		
		int i = LoadFromAddress(addr, NumberType_Int16)
		
		//if(i == 0x44C7 && LoadFromAddress(addr+view_as<Address>(2), NumberType_Int8) == 0x24) type = PatchType_PlainData
		//else type = PatchType_Pointer
		
		if(i == 0x0FF3 || i == 0x2F0F)
		{
			type = PatchType_Pointer
			MemoryBlock mb = new MemoryBlock(4)
			list.Set(l, mb, ListOrder_MemBlock)
			StoreToAddress(addr+view_as<Address>(i == 0x0FF3 ? 4 : 3), mb.Address, NumberType_Int32)
		}
		else
		{
			type = PatchType_PlainData
			switch(i)
			{
				case 0x44C7: i = 4
				case 0x84C7: i = 7
				case 0x43C7: i = 3
			}
			list.Set(l, i, ListOrder_MemBlock)
		}
		list.Set(l, p, ListOrder_MemPatch)
		list.Set(l, type, ListOrder_PatchType)
		list.Set(l, vt, ListOrder_VariantType)
		
		//hConVarMemPatch.SetValue(name, p)
		//hConVarMemType.SetValue(name, type)
		//hConVarVariantType.SetValue(name, vt)
		 
		// PrintToServer("PatchType is %i", type)
		
		ConVar convar = FindConVar(name)
		if(!convar) convar = CreateConVar(name, defaultValue, description, flags, hasMin, min, hasMax, max)
		char s[128]
		convar.GetString(s, sizeof s)
		Hook_ConVar(convar, "", s)
		convar.AddChangeHook(Hook_ConVar);
	}
	else
	{
		LogError("MemPatches %s invalidate.", section);
		p.Close()
	}
}
Hook_ConVar(ConVar convar, const char[] oldValue, const char[] newValue)
{
	char name[80]
	convar.GetName(name, sizeof name)
	PatchType type
	VariantType vt
	Address p
	
	
	//hConVarMemType.GetValue(name, type)
	//hConVarMemPatch.GetValue(name, patch)
	//hConVarVariantType.GetValue(name, vt)
	
	ArrayList list
	hConVarMemPatchList.GetValue(name, list)
	
	for(int l=list.Length-1;l>=0;l--)
	{
		type = list.Get(l, ListOrder_PatchType)
		vt = list.Get(l, ListOrder_VariantType)
		
		if(type == PatchType_PlainData)
		{
			p = view_as<MemoryPatch>(list.Get(l, ListOrder_MemPatch)).Address+list.Get(l, ListOrder_MemBlock)
		}
		else
		{
			p = view_as<MemoryBlock>(list.Get(l, ListOrder_MemBlock)).Address
		}
		
		if(vt == VariantType_Int) StoreToAddress(p, StringToInt(newValue), NumberType_Int32)
		else StoreToAddress(p, StringToFloat(newValue), NumberType_Int32)
	}
}

