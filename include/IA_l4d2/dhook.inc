/*stock Hook_GetClass(a, )
{
	static DynamicHook hHook_GetClass
	if(!hHook_GetClass) hHook_GetClass = DHookCreate(337, HookType_Entity, ReturnType_Int, ThisPointer_CBaseEntity)
	hHook_GetClass.HookEntity(Hook_Pre, e, DH_OnRocketKilled)
}*/