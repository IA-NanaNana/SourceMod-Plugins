/*
* @param	force	Use the weapon throw force if vel is NULL_VECTOR
*/
stock DropWeapon2(a, b, bool force=true, const float vel[3]=NULL_VECTOR)
{
	static Handle hCSWeaponDrop
	if(!hCSWeaponDrop)
	{
		StartPrepSDKCall(SDKCall_Player) 
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN9CCSPlayer12CSWeaponDropEP17CBaseCombatWeaponbbP6Vector", 0);
		PrepSDKCall_AddParameter(SDKType_CBaseEntity, SDKPass_Pointer)
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_AddParameter(SDKType_Bool, SDKPass_Plain)
		PrepSDKCall_AddParameter(SDKType_Vector, SDKPass_Pointer, VDECODE_FLAG_ALLOWNULL);
		hCSWeaponDrop = EndPrepSDKCall()
	}
	SDKCall(hCSWeaponDrop, a, b, 0, force, vel)
}

stock int GetSequenceFromActivity(a, i)
{
	static Handle hSelectWeightedSequence
	if(!hSelectWeightedSequence)
	{
		StartPrepSDKCall(SDKCall_Entity)
		PrepSDKCall_SetVirtual(208)
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain);
		hSelectWeightedSequence = EndPrepSDKCall()
	}
	return SDKCall(hSelectWeightedSequence, a, i)
}

stock float GetSequenceDuration(a, b=-1)
{
	static Handle hGetSequenceDuration
	if(!hGetSequenceDuration)
	{
		StartPrepSDKCall(SDKCall_Entity) 
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN14CBaseAnimating25ScriptGetSequenceDurationEi", 0);
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_SetReturnInfo(SDKType_Float, SDKPass_Plain)
		hGetSequenceDuration = EndPrepSDKCall()
	}
	return SDKCall(hGetSequenceDuration, a, b==-1?GetSequence(a):b)
}

stock bool GrenadeLauncherPrimaryAttack(w)
{
	static Handle hGLPrimaryAttack
	if(!hGLPrimaryAttack)
	{
		StartPrepSDKCall(SDKCall_Entity);
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN16CGrenadeLauncher13PrimaryAttackEv", 0)
		PrepSDKCall_SetReturnInfo(SDKType_Bool, SDKPass_Plain);
		hGLPrimaryAttack = EndPrepSDKCall()
	}
	return SDKCall(hGLPrimaryAttack, w)
}

stock OnAmmoPickedUp(a)
{
	static Handle hOnAmmoPickedUp
	if(!hOnAmmoPickedUp)
	{
		StartPrepSDKCall(SDKCall_Player);
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN13CTerrorPlayer14OnAmmoPickedUpEv", 0)
		hOnAmmoPickedUp = EndPrepSDKCall()
	}
	SDKCall(hOnAmmoPickedUp, a)
}

stock bool WeaponGunPrimaryAttack(w)
{
	static Handle hGunPrimaryAttack
	if(!hGunPrimaryAttack)
	{
		StartPrepSDKCall(SDKCall_Entity);
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN10CTerrorGun13PrimaryAttackEv", 0)
		PrepSDKCall_SetReturnInfo(SDKType_Bool, SDKPass_Plain);
		hGunPrimaryAttack = EndPrepSDKCall()
	}
	return SDKCall(hGunPrimaryAttack, w)
}

stock bool SendWeaponAnim(w, i)
{
	static Handle hSendWeaponAnim
	if(!hSendWeaponAnim)
	{
		StartPrepSDKCall(SDKCall_Entity)
		PrepSDKCall_SetVirtual(252)
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain)
		hSendWeaponAnim = EndPrepSDKCall()
	}
	return SDKCall(hSendWeaponAnim, w, i)
}

/*methodmap KvPointer
{
	public void GetString(const char[]key, char[]buffer, int len, const char[]def="")
	{
		static Handle hKvGetString
		if(!hKvGetString)
		{
			StartPrepSDKCall(SDKCall_Raw)
			PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN9KeyValues9GetStringEPKcS1_", 0);
			PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer)
			PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer)
			PrepSDKCall_SetReturnInfo(SDKType_String, SDKPass_Pointer)
			hKvGetString = EndPrepSDKCall()
		}
		SDKCall(hKvGetString, this, buffer, len, key, def);
	}
	public bool JumpToKey(const char[]key, bool build=false)
	{
		static Handle hKvFindKey
		if(!hKvFindKey)
		{
			StartPrepSDKCall(SDKCall_Raw)
			PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN9KeyValues7FindKeyEPKcb", 0);
			PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer)
			PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
			PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain)
			hKvFindKey = EndPrepSDKCall()
		}
		static int i
		i = SDKCall(hKvFindKey, this, key, build);
		if(i) this = view_as<KvPointer>(i)
		return i != 0
	}
}*/

stock KvPointer_GetString(int p, const char[]key, char[]buffer, int len, const char[]def="")
{
	static Handle hKvGetString
	if(!hKvGetString)
	{
		StartPrepSDKCall(SDKCall_Raw)
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN9KeyValues9GetStringEPKcS1_", 0);
		PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer)
		PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer)
		PrepSDKCall_SetReturnInfo(SDKType_String, SDKPass_Pointer)
		hKvGetString = EndPrepSDKCall()
	}
	SDKCall(hKvGetString, p, buffer, len, key, def);
}

/*bool KvPointer_JumpToKey(int &p, const char[]key, bool build=false)
{
	static Handle hKvFindKey
	if(!hKvFindKey)
	{
		StartPrepSDKCall(SDKCall_Raw)
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN9KeyValues7FindKeyEPKcb", 0);
		PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer)
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain)
		hKvFindKey = EndPrepSDKCall()
	}
	int i = SDKCall(hKvFindKey, this, key, build);
	if(i) p = i
	return i != 0
}*/

stock int KvPointer_GetInt(int p, const char[]key, int def=0)
{
	static Handle hKvGetInt
	if(!hKvGetInt)
	{
		StartPrepSDKCall(SDKCall_Raw)
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN9KeyValues6GetIntEPKci", 0);
		PrepSDKCall_AddParameter(SDKType_String, SDKPass_Pointer)
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain)
		hKvGetInt = EndPrepSDKCall()
	}
	return SDKCall(hKvGetInt, p, key, def);
}

stock int GetMissionCurrentMap()
{
	static Handle hGetMissionCurrentMap
	if(!hGetMissionCurrentMap)
	{
		StartPrepSDKCall(SDKCall_Static)
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN16CTerrorGameRules20GetMissionCurrentMapEPP9KeyValues", 0);
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain)
		hGetMissionCurrentMap = EndPrepSDKCall()
	}
	return SDKCall(hGetMissionCurrentMap, 0)
}

stock int GetBodyGroup(e, i)
{
	static Handle hGetBodyGroup
	if(!hGetBodyGroup)
	{
		StartPrepSDKCall(SDKCall_Entity)
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN14CBaseAnimating12GetBodygroupEi", 0);
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain)
		hGetBodyGroup = EndPrepSDKCall()
	}
	return SDKCall(hGetBodyGroup, e, i)
}
stock SetBodyGroup(e, i, part)
{
	static Handle hSetBodyGroup
	if(!hSetBodyGroup)
	{
		StartPrepSDKCall(SDKCall_Entity)
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN14CBaseAnimating12SetBodygroupEii", 0);
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		hSetBodyGroup = EndPrepSDKCall()
	}
	SDKCall(hSetBodyGroup, e, i, part)
}

stock int GetBodyGroupCount(e, i)
{
	static Handle hGetBodyGroupCount
	if(!hGetBodyGroupCount)
	{
		StartPrepSDKCall(SDKCall_Entity)
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN14CBaseAnimating17GetBodygroupCountEi", 0);
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain)
		hGetBodyGroupCount = EndPrepSDKCall()
	}
	return SDKCall(hGetBodyGroupCount, e, i)
}

stock GetBodyGroupName(e, i, char[]s, l)
{
	static Handle hGetBodygroupName
	if(!hGetBodygroupName)
	{
		StartPrepSDKCall(SDKCall_Entity)
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN14CBaseAnimating16GetBodygroupNameEi", 0);
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_SetReturnInfo(SDKType_String, SDKPass_Pointer)
		hGetBodygroupName = EndPrepSDKCall()
	}
	SDKCall(hGetBodygroupName, e, s, l, i);
}

stock GetBodygroupPartName(e, i, part, char[]s, l)
{
	static Handle hGetBodygroupPartName
	if(!hGetBodygroupPartName)
	{
		StartPrepSDKCall(SDKCall_Entity)
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN14CBaseAnimating20GetBodygroupPartNameEii", 0);
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_AddParameter(SDKType_PlainOldData, SDKPass_Plain)
		PrepSDKCall_SetReturnInfo(SDKType_String, SDKPass_Pointer)
		hGetBodygroupPartName = EndPrepSDKCall()
	}
	SDKCall(hGetBodygroupPartName, e, s, l, i, part);
	// int i = FindCharInString(s, '.', true)
	// if(i != -1) s[i] = 0
	/*if((i = FindCharInString(s, '/', true)) != -1) strcopy(s, l, s[i+1])*/
}

stock int GetNumBodyGroups(e)
{
	static Handle hGetNumBodyGroups
	if(!hGetNumBodyGroups)
	{
		StartPrepSDKCall(SDKCall_Entity)
		PrepSDKCall_SetSignature(SDKLibrary_Server, "@_ZN14CBaseAnimating16GetNumBodyGroupsEv", 0);
		PrepSDKCall_SetReturnInfo(SDKType_PlainOldData, SDKPass_Plain)
		hGetNumBodyGroups = EndPrepSDKCall()
	}
	return SDKCall(hGetNumBodyGroups, e)
}

stock ResetMainActivity(e)
{
	static Handle hResetMainActivity
	if(!hResetMainActivity)
	{
		StartPrepSDKCall(SDKCall_Raw)
		PrepSDKCall_SetVirtual(5);
		hResetMainActivity = EndPrepSDKCall()
	}
	int i = GetEntData(e, 10512)
	StoreToAddress(view_as<Address>(i) + view_as<Address>(344) + view_as<Address>(0), 0, NumberType_Int8);
	StoreToAddress(view_as<Address>(i) + view_as<Address>(344) + view_as<Address>(2), 0, NumberType_Int8);
	StoreToAddress(view_as<Address>(i) + view_as<Address>(344) + view_as<Address>(3), 0, NumberType_Int8);
	StoreToAddress(view_as<Address>(i) + view_as<Address>(344) + view_as<Address>(5), 0, NumberType_Int8);
	StoreToAddress(view_as<Address>(i) + view_as<Address>(344) + view_as<Address>(7), 0, NumberType_Int8);
	StoreToAddress(view_as<Address>(i) + view_as<Address>(344) + view_as<Address>(9), 0, NumberType_Int8);
	return SDKCall(hResetMainActivity, i)
}