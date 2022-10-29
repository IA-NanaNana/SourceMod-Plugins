// Fade Flag
#define FFADE_IN            0x0001        // Just here so we don't pass 0 into the function
#define FFADE_OUT           0x0002        // Fade out (not in)
#define FFADE_MODULATE      0x0004        // Modulate (don't blend)
#define FFADE_STAYOUT       0x0008        // ignores the duration, stays faded out until new ScreenFade message received
#define FFADE_PURGE         0x0010        // Purges all other fades, replacing them with this one

#define FV_Switch	1
#define FV_Select	2
#define FV_Int		3
#define FV_Float	4
#define FV_String	5

#define FCMD_ADMIN		FCVAR_ARCHIVE
#define FCMD_SERVER		FCVAR_SERVER_CAN_EXECUTE
#define FCMD_HOST		FCVAR_USERINFO

#define CLAMP_Min	-1
#define CLAMP_Max	1

#define FL_Team1		(1<<1)
#define FL_Team2		(1<<2)
#define FL_Team3		(1<<3)
#define FL_TeamAll		FL_Team1|FL_Team2|FL_Team3
#define FL_Admin		(1<<5)

#define DMG_HEADSHOT                (1 << 30)   /**< Damage from a headshot. */
#define DMG_BIGSHOT                 (1 << 31)   /**< Damage from a large bullet, it can dismember zombies. */

#define DEBUG	PrintToChatAll("?"), PrintToServer("?")

enum ObjectType
{
	OT_STATIC,OT_DYNAMIC,OT_PHYSICS,OT_PHYSICS_PROP
}
enum DoorType
{
	DT_STATIC,DT_CHECKPOINT
}
enum BlockType
{
	BT_NONE,BT_SURVIVORS,BT_PLSI,BT_ALLSI,BT_ALL
}

#define Upgrade_FireBullect			(1<<0)
#define Upgrade_ExplosiveBullect	(1<<1)
#define Upgrade_LaserSight			(1<<2)

#include <sourcemod>
#include <sdktools>
#include <sdkhooks>

/*	------------- MenuItem -------------	*/
// stock void AddMenuTranslatedItem(Menu menu, const char[] opt, const char[] phrase, int client)
// {
	// char buffer[128];
	// Format(buffer, sizeof(buffer), "%T", phrase, client);
	// menu.AddItem(opt, buffer);
// }
// stock void AddMenuTranslatedItemInt(Menu menu, int i, const char[] phrase, int client)
// {
	// char buffer[128], b[12]
	// Format(buffer, sizeof(buffer), "%T", phrase, client);
	// IntToString(i, b, 12)
	// menu.AddItem(i, buffer);
// }
stock AddMenuInt(Handle:m, a, b, bool c=true)
{
	char s[10]
	if(c)
	{
		for(new i=a;i<=b;i++)
		{
			IntToString(i, s, 10)
			AddMenuItem(m, s, s)
		}
	}
	else for(new i=a;i>=b;i--)
	{
		IntToString(i, s, 10)
		AddMenuItem(m, s, s)
	}
}

stock AddMenuItemAll(Handle:menu, t)
{
	if(t == 0 || t == 2)
	{
		AddMenuItem(menu, "-2", IsL4D2()?"{t:All Survivor}":"{t:All T}");
	}
	if(t == 0 || t == 3)
	{
		AddMenuItem(menu, "-3", IsL4D2()?"{t:All Infected}":"{t:All CT}");
	}
}

stock AddMenuItemEx(Handle:menu, style=ITEMDRAW_DEFAULT, const String:b[], const String:f[], any:...)
{
	char s[256]
	VFormat(s, 256, f, 5)
	AddMenuItem(menu, b, s, style)
}

stock AddMenuItemFormat(Handle:menu, const String:b[], const String:format[], type, any:x=0, const String:value[]="", style=ITEMDRAW_DEFAULT)
{
	char s[256]
	if(type == FV_Select) style = x?ITEMDRAW_DISABLED:ITEMDRAW_DEFAULT
	FormatValue(s, 256, type, format[0]?format:b, x, value)
	AddMenuItem(menu, b, s, style)
}

stock AddMenuItemInt(Handle:menu, i, const String:s[], style=ITEMDRAW_DEFAULT, p=-1)
{
	char b[10];
	IntToString(i, b, 10)
	if(p >= 0) InsertMenuItem(menu, p, b, s, style);
	else AddMenuItem(menu, b, s, style)
}

stock AddMenuItemIntEx(Handle:menu, style=ITEMDRAW_DEFAULT, i, const String:f[], any:...)
{
	char s[256], b[10]
	IntToString(i, b, 10)
	VFormat(s, 256, f, 5)
	AddMenuItem(menu, b, s, style)
}

stock AddMenuItemIntFormat(Handle:menu, i, const String:format[], type, any:x=0, const String:value[]="", style=ITEMDRAW_DEFAULT)
{
	char s[256], b[10]
	IntToString(i, b, 10)
	if(type == FV_Select) style = x?ITEMDRAW_DISABLED:ITEMDRAW_DEFAULT
	FormatValue(s, 256, type, format, x, value)
	AddMenuItem(menu, b, s, style)
}
stock AM_CommandFlag(const String:cmd[], f, bool b)
{
	new i = GetCommandFlags(cmd)
	if(b) i |=f
	else i &=~f
	SetCommandFlags(cmd, i);
}

stock ArrayToString(any[]z, c, char[]s, l)
{
	s[0] = 0
	while(c--) Format(s, l, "%i %s", z[c], s)
	TrimString(s)
}

stock ArrayAdd(any[] a, const any[] b, c)
{
	while(c--) a[c] += b[c]
}

stock any ArraySum(const any[] a, b)
{
	int i
	while(b--) i += a[b]
	return i
}

stock BitToString(a, String:s[], l)
{
	s[0] = 0
	for(new i = 1;i<32;i++)
	{
		if(a & 1<<i) Format(s, l, "%s%i|", s, i)
	}
	if(s[0]) s[strlen(s)-1] = 0
}

stock CalTime(float f, &h, &m, &s)
{
	h = RoundToFloor(f/3600.0)
	f -= 3600.0*float(h)
	m = RoundToFloor(f/60.0)
	f -= 60.0*float(m)
	s = RoundToFloor(f)
}

#define CLTime_S 1
#define CLTime_M 2
#define CLTime_H 3
#define CLTime_D 4

stock CalTimeEx(float f, any[]z, l)
{
	if(l==4)
	{
		l--
		z[l] = RoundToFloor(f/86400.0)
		f -= 86400.0*float(z[l])
	}
	if(l==3)
	{
		l--
		z[l] = RoundToFloor(f/3600.0)
		f -= 3600.0*float(z[l])
	}
	if(l==2)
	{
		l--
		z[l] = RoundToFloor(f/60.0)
		f -= 60.0*float(z[l])
	}
	if(l==1)
	{
		l--
		z[l] = RoundToFloor(f)
	}
}

stock CheatCommand(a, const String:cmd[], const String:format[]="", any:...)
{
	new i = GetCommandFlags(cmd), String:s[128]
	VFormat(s, 128, format, 4)
	SetCommandFlags(cmd, i &~FCVAR_CHEAT&~FCVAR_ARCHIVE);
	if(a || (a = GetRandomClient())) FakeClientCommand(a, "%s %s", cmd, s);
	else
	{
		a = CreateFakeClient("")
		FakeClientCommand(a, "%s %s", cmd, s);
		KickClientEx(a)
	}
	SetCommandFlags(cmd, i)
}
// cm warp_all_survivors_to_checkpoint

/*stock CheatCommand(a, const String:cmd[], const String:format[]="", any:...)
{
	new i = GetCommandFlags(cmd), String:s[128]
	VFormat(s, 128, format, 4)
	SetCommandFlags(cmd, i &~FCVAR_CHEAT&~FCVAR_ARCHIVE);
	if(a)
	{
		FakeClientCommand(a, "%s %s", cmd, s);
		SetCommandFlags(cmd, i)
	}
	else
	{
		ServerCommand("%s %s", cmd, s);
		if(i &FCVAR_CHEAT || i &FCVAR_ARCHIVE)
		{
			Handle p = CreateDataPack();
			WritePackString(p, cmd)
			WritePackCell(p, i)
			CreateTimer(0.1, ResetCommandCheatFlags, p, TIMER_DATA_HNDL_CLOSE)
		}
	}
}*/

stock any Clamp(any a, any b, any c)
{
	if(a < b) return b
	if(a > c) return c
	return a
}

stock CopyFile(const String:file[], bool b, const String:newFile[], bool cover=true)
{
	if(FileExists(newFile) && !cover) return
	File hFile = OpenFile(file, "rb", b)
	if(!hFile) return
	File hNewFile = OpenFile(newFile, "wb")
	if(hNewFile)
	{
		int s[256]; // 256Bytes each time
		int i;
		while (!hFile.EndOfFile())
		{
			i = hFile.Read(s, 256, 1);
			hNewFile.Write(s, i, 1);
		}
		FlushFile(hNewFile);
		hNewFile.Close();
	}
	hFile.Close();
	/*new l = FileSize(file), buffer[l]
	l = ReadFile(hFile, buffer, l, 1);
	WriteFile(hNewFile, buffer, l, 1);
	hFile.Close()
	hNewFile.Close()*/
}
stock CopyVector(Float:x[3], const Float:y[3])
{
	x[0] = y[0]
	x[1] = y[1]
	x[2] = y[2]
}
stock Handle:CreateConVarEx(const String:name[], const String:defaultValue[], ConVarChanged:callback, const String:description[]="", flags=0, bool hasMin=false, Float:min=0.0, bool hasMax=false, Float:max=0.0)
{
	ConVar cvar = CreateConVar(name, defaultValue, description, flags, hasMin, min, hasMax, max)
	HookConVarChange(cvar, callback);
	return cvar
}

stock int CreateBlocker(BlockType:t, const Float:Min[3], const Float:Max[3], const Float:x[3]=NULL_VECTOR, const Float:y[3]=NULL_VECTOR)
{
	new e = CreateEntityByName("env_physics_blocker"), String:s[32]
	if(BT_NONE <= t <= BT_ALL) Format(s, 32, "%i", t)
	else return 0
	TeleportEntity(e, x, y, NULL_VECTOR)
	SetEntPropVector(e, Prop_Send, "m_vMins", Min);
	SetEntPropVector(e, Prop_Send, "m_vMaxs", Max);
	SetEntProp(e, Prop_Send, "m_nSolidType", 6);
	DispatchKeyValue(e, "InitialState", "1")
	DispatchKeyValue(e, "BlockType", s)
	DispatchSpawn(e)
	return e
}

stock int CreateDoor(const String:m[], DoorType:t, const Float:x[3]=NULL_VECTOR, const Float:y[3]=NULL_VECTOR)
{
	new e, Float:f[3]
	if(!IsModelPrecached(m) && !PrecacheModel(m)) return 0
	if(t == DT_STATIC) e = CreateEntityByName("prop_door_rotating")
	else if(t == DT_CHECKPOINT) e = CreateEntityByName("prop_door_rotating_checkpoint")
	else return 0
	AcceptEntityInput(e, "DisableShadow")
	SetEntityModel(e, m)
	DispatchSpawn(e)
	TeleportEntity(e, x, y, NULL_VECTOR)
	GetEntityOrigin(e, f)
	f[2] += 50.0
	TeleportEntity(e, f, NULL_VECTOR, NULL_VECTOR)
	SetEntPropFloat(e, Prop_Data, "m_flAutoReturnDelay", -1.0)
	f = y
	f[1]+=90.0
	SetEntPropVector(e, Prop_Data, "m_angRotationOpenForward", f)
	f = y
	f[1]-=90.0
	SetEntPropVector(e, Prop_Data, "m_angRotationOpenBack", f)
	SetEntPropVector(e, Prop_Data, "m_angRotationClosed", y)
	SetEntPropVector(e, Prop_Data, "m_angGoal", y)
	AcceptEntityInput(e, "Unlock")
	SetVariantFloat(200.0);
	AcceptEntityInput(e, "SetSpeed")
	return e
}

stock int CreateObject(const String:m[], ObjectType:t, const Float:x[3]=NULL_VECTOR, const Float:y[3]=NULL_VECTOR)
{
	new e;
	if(t == OT_PHYSICS) e = CreateEntityByName("prop_physics_override");
	else if(t == OT_PHYSICS_PROP) e = CreateEntityByName("physics_prop");
	else if(t == OT_STATIC || t == OT_DYNAMIC) e = CreateEntityByName("prop_dynamic_override");
	else return 0
	SetEntityModelEx(e, m)
	DispatchKeyValue(e, "targetname", "IA_object");
	if(t == OT_STATIC) SetEntProp(e, Prop_Send, "m_nSolidType", 6);
	/*if(t == OT_PHYSICS_PROP)
	{
		SetEntProp(e, Prop_Send, "m_nSolidType", 6);
	}*/
	DispatchSpawn(e);
	TeleportEntity(e, x, y, NULL_VECTOR)
	return e
}

stock int CreateWind()
{
	new i = CreateEntityByName("env_wind");
	DispatchKeyValue(i, "targetname", "silverwind");
	DispatchKeyValue(i, "windradius", "-1");
	DispatchKeyValue(i, "minwind", "75");
	DispatchKeyValue(i, "mingustdelay", "15");
	DispatchKeyValue(i, "mingust", "100");
	DispatchKeyValue(i, "maxwind", "150");
	DispatchKeyValue(i, "maxgustdelay", "30");
	DispatchKeyValue(i, "maxgust", "200");
	DispatchKeyValue(i, "gustduration", "5");
	DispatchKeyValue(i, "gustdirchange", "20");
	DispatchSpawn(i);
	ActivateEntity(i);
	return i
}

stock DestroyEntity(&e, bool b=true)
{
	if(e && IsValidEntity(e)) RemoveEntity(e)
	if(b) e = 0
}

stock FloatToStringEx(float f, String:s[], l)
{
	FloatToString(f, s, l)
	new j = strlen(s)-1
	while(s[j] == '0' && s[j-1] != '.')
	{
		s[j--] = 0
	}
	/*FloatToString(f, s, l)
	new j = strlen(s)
	while(j)
	{
		j--
		if(s[j] == '0') s[j] = 0
		else break
	}
	if(s[j] == '.') s[j] = 0*/
}

stock FormatValue(String:s[], l, type, const String:format[], any:i=0, const String:value[]="")
{
	switch(type)
	{
		case FV_Switch: FormatEx(s, l, "%s {t:%s}", i?"[✔]":"[　]", format)
		case FV_Select: FormatEx(s, l, "%s {t:%s}", i?"[√]":"　", format)
		case FV_Int: FormatEx(s, l, "{t:%s} [%i]", format, i)
		case FV_Float:
		{
			FloatToStringEx(i, s, l)
			Format(s, l, "{t:%s} [%s]", format, s)
		}
		case FV_String: FormatEx(s, l, "{t:%s} [%s]", format, value)
	}
}

stock int GetClientCountEx(g=-1, t=FL_TeamAll, l=-1, h=-1, c=0)
{
	int b;
	for (int a = 1; a <= MaxClients; a++)
	{
		if(a != c && IsClientAvailable(a, g, 0, l, h) && t&1<<GetClientTeam(a)) b++;
	}
	return b;
}

stock bool GetClientEyeEndPosition(a, float f[3])
{
	float x[3], y[3]
	GetClientEyePosition(a, x);
	GetClientEyeAngles(a, y);
	TR_TraceRayFilter(x, y, MASK_OPAQUE, RayType_Infinite, TR_DontHitTarget, -1);
	if(!TR_DidHit()) return false
	TR_GetEndPosition(f);
	return true
}

/*stock int GetClientCounts(g=-1, t=0, l=-1, h=-1, b=0)
{
	int a;
	for (int i = 1; i <= MaxClients; i++)
	{
		if(i != b && IsClientAvailable(i, g, t, l, h) && !IsCreateBot(i)) a++;
	}
	return a;
}*/

stock Float:GetClientHealthBuffer(a)
{
	float f = GetEntPropFloat(a, Prop_Send, "m_healthBuffer")-((GetGameTime()-GetEntPropFloat(a, Prop_Send, "m_healthBufferTime"))*GS_CvarFloat("pain_pills_decay_rate"))
	if(f < 0.0) f = 0.0
	return f
}

stock int GetEdictsCount()
{
	new l;
	for(new i = 1;i < 2049;i++){if(IsValidEdict(i)) l++;}
	return l
}

stock int GetEntityOfAddress(Address i)
{
	for(int a=1;a<=2048;a++)
	{
		if(IsValidEntity(a) && GetEntityAddress(a) == i) return a
	}
	return -1
}

stock GetEntityModel(a, String:s[], b)
{
	GetEntPropString(a, PropType:1, "m_ModelName", s, b);
}

stock GetEntityOrigin(a, Float:f[3])
{
	if(FindDataMapInfo(a, "m_vecAbsOrigin") != -1) GetEntPropVector(a, Prop_Data, "m_vecAbsOrigin", f)
}

stock GetEntityOriginWithOffset(a, float f[3], float x, float y, float z)
{
	new Float:F[3], Float:v[3]
	GetEntPropVector(a, Prop_Data, "m_vecAbsOrigin", f)
	GetEntPropVector(a, Prop_Data, "m_angRotation", F)
	GetAngleVectors(F, NULL_VECTOR, v, NULL_VECTOR);
	f[0] += v[0]*x;
	f[1] += v[1]*x;
	GetAngleVectors(F, v, NULL_VECTOR, NULL_VECTOR);
	f[0] += v[0]*y;
	f[1] += v[1]*y;
	f[2] += z
}

stock GetEntityRotation(a, Float:f[3])
{
	if(FindDataMapInfo(a, "m_angRotation") != -1) GetEntPropVector(a, Prop_Data, "m_angRotation", f)
}

stock float GetEntitySpeed(a)
{
	new Float:f[3]
	GetEntityVelocity(a, f)
	return GetVectorLength(f)
}

stock GetEntityVector3(a, float f[3], float F[3], float v[3])
{
	GetEntPropVector(a, Prop_Data, "m_vecAbsOrigin", f)
	GetEntPropVector(a, Prop_Data, "m_angRotation", F)
	GetEntPropVector(a, Prop_Data, "m_vecVelocity", v)
}

stock GetEntityVelocity(a, Float:f[3])
{
	if(FindDataMapInfo(a, "m_vecVelocity") != -1) GetEntPropVector(a, Prop_Data, "m_vecVelocity", f)
}

stock float GetGroundZ(Float:f[3], a=0)
{
	new Float:x[3]
	TR_TraceRayFilter(f, Float:{90.0, 0.0, 0.0}, MASK_SOLID, RayType_Infinite, TR_DontHitTarget, a);
	if(TR_DidHit()) TR_GetEndPosition(x);
	else x[2] = f[2]
	return x[2]
}

stock int GetPlayerWeapon(a)
{
	return GetEntPropEnt(a, Prop_Send, "m_hActiveWeapon")
}

stock GetPluginInfoEx(Handle:h, String:s[], l)
{
	new String:n[128]
	GetPluginInfo(h, PlInfo_Name, n, 128);
	Format(s, l, "\"%s\"", n)
	GetPluginInfo(h, PlInfo_Version, n, 128);
	Format(s, l, "%s(%s)", s, n)
	GetPluginFilename(h, n, 128);
	Format(s, l, "%s [%s]", s, n)
	GetPluginInfo(h, PlInfo_Author, n, 128);
	Format(s, l, "%s by %s", s, n)
	GetPluginInfo(h, PlInfo_Description, n, 128);
	Format(s, l, "%s\n- %s", s, n)
}

stock int GetStringArg(const String:s[], k)
{
	bool b
	int j
	while(s[j])
	{
		if(s[j] == ' ') b = false
		else if(!b)
		{
			k--
			if(!k) return j
			b = true
		}
		j++
	}
	return -1
}

/*stock bool GetStringLineFromeString(const String:f[], i, String:s[], l)
{
	if(i < 1) return false
	new j, k
	
	while(true)
	{
		if((j = StrContains(f[k], "\n")) != -1)
		{
			if(i) k+=j+1, i++
		}
		else break
		
		if((j = StrContains(f[k], "\n")) != -1 && i)
		
		i--
		if((j = StrContains(f[k], "\n")) != -1 && i) 
		else break
	}
	
	while(i)
	{
		i--
		if((j = StrContains(f[k], "\n")) != -1 && i) k+=j+1
		else break
	}
	
	
	do
	{
		i--
		k+=j+1
	}
	while(i && (j = StrContains(f[k], "\n")) != -1)
	if(i) return false
	strcopy(s, l, f[k])
	if(j != -1) s[j] = 0
	return true
}*/

stock int GetTeamClients(t, l=-1, h=-1, b=0)
{
	int a;
	for (int i = 1; i <= MaxClients; i++)
	{
		if(i != b && IsClientAvailable(i, 1, t, l, h) && !IsCreateBot(i)) a++;
	}
	return a;
}

stock int GetTickrate()
{
	return RoundFloat(1.0/GetTickInterval())
}

stock int GetWeaponAmmoType(e)
{
	return GetEntProp(e, Prop_Send, "m_iPrimaryAmmoType");
}

stock int GS_WeaponClip(a, b=-1)
{
	if(b > -1) SetEntProp(a, Prop_Send, "m_iClip1", b);
	int c = GetEntProp(a, Prop_Send, "m_iClip1")
	return c >= 254?0:c;
}

stock int GS_WeaponAmmo(e, s=-1)
{
	new a;
	if((a = GetEntPropEnt(e, Prop_Send, "m_hOwner")) > 0)
	{
		new f = GetEntProp(e, Prop_Send, "m_iPrimaryAmmoType");
		if(f > 0)
		{
			if(s > -1) SetEntProp(a, Prop_Send, "m_iAmmo", s, _, f);
			s = GetEntProp(a, Prop_Send, "m_iAmmo", _, f);
		}
	}
	else
	{
		if(s > -1) SetEntProp(e, Prop_Send, "m_iExtraPrimaryAmmo", s)
		s = GetEntProp(e, Prop_Send, "m_iExtraPrimaryAmmo")
	}
	return s
}

stock InitialArray(any[]z, l)
{
	for(int i=0;i<l;i++) z[i] = 0
}

stock InsertMenuItemInt(Handle:menu, a, i, const String:s[])
{
	static char incBuffer[10];
	IntToString(i, incBuffer, 10)
	InsertMenuItem(menu, a, incBuffer, s)
}

stock bool IsAllClientInGame(i=0)
{
	for(new a=1;a<33;a++)
	{
		if(a != i && IsClientConnected(a) && !IsClientInGame(a)) return false
	}
	return true
}

stock bool IsBoxIntersectingBox(float a1[3], float a2[3], float a3[3], float a4[3])
{
	return a1[0] <= a4[0] && a3[0] <= a2[0] && a1[1] <= a4[1] && a3[1] <= a2[1] && a1[2] <= a4[2] && a2[2] >= a3[2]
}
stock bool IsBoxIntersectingSphere(float a1[3], float a2[3], float a3[3], float a4)
{
	float v5; // xmm0_4@2

	if ( a1[0] <= a3[0] )
	{
		if ( a3[0] <= a2[0] )
			v5 = 0.0;
		else
			v5 = (a2[0] - a3[0]) * (a2[0] - a3[0]);
	}
	else
	{
		v5 = (a3[0] - a1[0]) * (a3[0] - a1[0]);
	}
	if ( a1[1] <= a3[1] )
	{
		if ( a3[1] > a2[1] )
		{
			v5 = v5 + ((a2[1] - a3[1]) * (a2[1] - a3[1]));
			if ( a1[2] <= a3[2] )
			{
			  if ( a3[2] > a2[2] ) v5 = v5 + ((a2[2] - a3[2]) * (a2[2] - a3[2]));
			  return (a4 * a4) > v5;
			}
			return (a4 * a4) > (v5 + ((a3[2] - a1[2]) * (a3[2] - a1[2])));
		}
	}
	else
	{
		v5 = v5 + ((a3[1] - a1[1]) * (a3[1] - a1[1]));
	}
	if ( a1[2] > a3[2] ) return (a4 * a4) > (v5 + ((a3[2] - a1[2]) * (a3[2] - a1[2])));
	if ( a3[2] > a2[2] ) v5 = v5 + ((a2[2] - a3[2]) * (a2[2] - a3[2]));
	return (a4 * a4) > v5;
}

stock bool IsClientAvailable(a, g=1,t=0, l=-1, h=-1)
{
	return 0 < a <= MaxClients && IsClientConnected(a) && (g == -1 || (!g && !IsClientInGame(a)) || (g == 1 && IsClientInGame(a))) && (!t || GetClientTeam(a) == t) && (l == -1 || (!l && (!IsPlayerAlive(a) || IsPlayerGhost(a))) || (l == 1 && IsPlayerAlive(a) && !IsPlayerGhost(a))) && (h == -1 || (!h && IsFakeClient(a)) || (h == 1 && !IsFakeClient(a)))
}

stock bool IsFirstMap()
{
	new i, e
	while((e = FindEntityByClassname(e, "info_landmark")) > 0) i++
	return i < 2 && FindEntityByClassname(0, "trigger_finale") == -1
}

stock bool IsIntro()
{
	new e = FindEntityByClassname(0, "terror_gamerules")
	return e != -1 && GetEntProp(e, Prop_Send, "m_bInIntro")
}

stock bool IsMissionFinal()
{
	new i, e
	while((e = FindEntityByClassname(e, "info_landmark")) > 0) i++
	return i < 2 && FindEntityByClassname(0, "trigger_finale") > 0
}

stock bool IsStringNumeric(const char[]s)
{
	int i
	while(s[i])
	{
		if(!IsCharNumeric(s[i++])) return false
	}
	return true
}

stock bool IsValidEnt(a)
{
	return (a > 32 && IsValidEdict(a));
}

stock bool IsVectorZero(float f[3])
{
	return f[0] == 0.0 && f[1] == 0.0 && f[2] == 0.0
}

stock KillTimerEx(&Handle:h)
{
	if(h && IsValidHandle(h)) KillTimer(h);
	h = INVALID_HANDLE
}

stock KillPlayer(a, b=-1, t=0)
{
	SDKHooks_TakeDamage(a, 0, b, 99999.0, t);
	if(IsPlayerAlive(a)) ForcePlayerSuicide(a);
}

stock KvAdd(KeyValues k, const String:t[], const y[], l)
{
	char s[256]
	new z[l]
	k.GetString(t, s, 256)
	/*StringToStats(s, z, sizeof(z))
	for(i = 0;i<sizeof(z);i++) z[i] += y[i]
	IntToString(z[0], s, 200)
	for(i = 1;i<l;i++) Format(s, 200, "%s %i", s, z[i])*/ 
	StringToArray(s, z, l)
	ArrayAdd(z, y, l)
	ArrayToString(z, l, s, 256)
	k.SetString(t, s)
}
stock KvRemoveKey(KeyValues k, const char[]key)
{
	if(k.JumpToKey(key) && k.DeleteThis() == 1) k.GoBack()
}
/*stock Notify(a, const String:f[], any:...)
{
	new i = GS_CvarInt("IA_message")
	if(!i) return
	new String:s[255], String:t[255]
	VFormat(t, 255, f, 3)
	Format(s, 255, "\x03IA\x01 :  %s", t)
	if(a > 0)
	{
		if(i == 2 || IsAdmin(a)) SendMessage(a, false, s)
		Format(s, 512, "\x03IA\x01 :  ({admin:%i}%N\x01) %s", a, a, t)
		if(GS_CvarInt("IA_notify_admin"))
		{
			for(i = 1;i<33;i++)
			{
				if(a != i && IsClientAvailable(i) && IsAdmin(i)) SendMessage(i, false, s)
			}
		}
	}
	else if(i == 2 && a < 0) SendMessage(0, true, s)
	else if(i == 1 && a < 0) PrintToChatAdmin(true, s)
	StrColor(s)
	PrintToConsole(0, s)
}*/


stock int LoadStringFromAddress(Address p, char[]s, l)
{
	s[0] = 0
	int i
	while(i<l)
	{
		s[i] = view_as<int>(LoadFromAddress(p+view_as<Address>(i), NumberType_Int8))
		if(!s[i]) break
		i++
	}
	return i
}

stock PerformFade(client, bool type, duration, const color[4])
{
	new Handle:h=StartMessageOne("Fade",client), i
	if(type) i = FFADE_PURGE|FFADE_OUT|FFADE_STAYOUT
	else i = FFADE_PURGE|FFADE_IN
	BfWriteShort(h,duration)	// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, milliseconds duration
	BfWriteShort(h,0)		// FIXED 16 bit, with SCREENFADE_FRACBITS fractional, milliseconds duration until reset (fade & hold)
	BfWriteShort(h,i) // fade type (in / out)
	BfWriteByte(h,color[0])	// fade red
	BfWriteByte(h,color[1])	// fade green
	BfWriteByte(h,color[2])	// fade blue
	BfWriteByte(h,color[3])	// fade alpha
	EndMessage()
}

stock bool PlayGameSound(int a, const char[] gameSound, int e = -2, int flags = 0, int speakerentity = -1, const float origin[3] = NULL_VECTOR, const float dir[3] = NULL_VECTOR, bool updatePos = true, float soundtime = 0.0)
{
	new channel, level, Float:volume, pitch
	static char sample[128]
	if(!GetGameSoundParams(gameSound, channel, level, volume, pitch, sample, 128, e)) return false
	int z[33], l
	if(a > 0) z[l++] = a, e = (e == -2)?a:e
	else for(a = 1;a<33;a++)
	{
		if(IsClientInGame(a)) z[l++] = a
	}
	PrecacheSound(sample);
	EmitSound(z, l, sample, e, channel, level, flags, volume, pitch, speakerentity, origin, dir, updatePos, soundtime);
	return true;
}

stock PrecacheMelee(const char[] sMeleeName)
{
	new i = FindStringTable("MeleeWeapons");
	if(FindStringIndex(i, sMeleeName) == INVALID_STRING_INDEX)
	{
		bool b = LockStringTables(false);
		AddToStringTable(i, sMeleeName);
		LockStringTables(b);
	}
}

stock PrecacheParticle(const char[] sEffectName)
{
	new i = FindStringTable("ParticleEffectNames");
	if(FindStringIndex(i, sEffectName) == INVALID_STRING_INDEX)
	{
		bool b = LockStringTables(false);
		AddToStringTable(i, sEffectName);
		LockStringTables(b);
	}
}

stock PrintMemory(Address pAddress, int offset, int bytes)
{
	// Loop memory
	PrintToServer("");
	PrintToServer("Displaying %d bytes from 0x%X + 0x%X offset.\n", bytes, pAddress, offset);
	char buff[128];
	int loop;
	for( int i = 0; i < bytes; i++ )
	{
		loop++;

		// Padded line offset numbers
		if( loop == 1 )
		{
			buff[0] = '\x0';
			
			Format(buff, sizeof(buff), "%8X ", view_as<int>(pAddress) + offset + i);
			Format(buff, sizeof(buff), "%s[%3X]  ", buff, i + offset);
		}

		// Load bytes into print buffer
		Format(buff, sizeof(buff), "%s%02X ", buff, LoadFromAddress(pAddress + view_as<Address>(offset) + view_as<Address>(i), NumberType_Int8));

		// Double space in middle
		if( loop == 16 / 2 ) StrCat(buff, sizeof(buff), " ");

		// Print line to console and reset buffer
		if( loop == 16 )
		{
			PrintToServer(buff);

			buff[0] = '\x0';
			loop = 0;
		}
	}
	// if unprinted bytes left
	if( buff[0] != '\x0' )
	{
		PrintToServer(buff);
	}
}

stock PrintToChatAllEx(b=FL_TeamAll, bool sound, const String:f[], any:...)
{
	char s[254]
	for (int i = 1; i <= MaxClients; i++)
	{
		if(IsClientInGame(i) && !IsFakeClient(i) && b&(1<<GetClientTeam(i)))
		{
			SetGlobalTransTarget(i);
			VFormat(s, sizeof(s), f, 4);
			PrintToChatEx(i, sound, s);
		}
	}
}

stock PrintToChatEx(a, bool sound, const String:f[], any:...)
{
	Handle h
	if(a) h = StartMessageOne("SayText2", a), SetGlobalTransTarget(a)
	else h = StartMessageAll("SayText2")
	char s[254]
	VFormat(s, sizeof(s), f, 4)
	int i = StrColor(s)
	Format(s, sizeof(s), "\x01%s", s)
	if(GetUserMessageType() == UM_BitBuf)
	{
		BfWriteByte(h, i)
		BfWriteByte(h, sound)
		BfWriteString(h, s); //Message
	}
	else
	{
		PbSetInt(h, "ent_idx", i)
		PbSetBool(h, "chat", sound)
		PbSetString(h, "msg_name", s)
		PbAddString(h, "params", "")
		PbAddString(h, "params", "")
		PbAddString(h, "params", "")
		PbAddString(h, "params", "")
	}
	EndMessage();
	
}
/*stock PrintToChatTeam(a, bool sound, const String:f[], any:...)
{
	char s[255]
	VFormat(s, 255, f, 4)
	for(new i=1;i<33;i++)
	{
		if(IsClientInTeam(i, GetClientTeam(a))) SendMessage(i, sound, s)
	}
}*/

stock PutEntityInFrontOfEntity(e, a, float dis)
{
	new Float:f[3], Float:F[3], Float:v[3]
	GetEntityOrigin(a, f);
	GetEntityRotation(a, F);
	GetAngleVectors(F, v, NULL_VECTOR, NULL_VECTOR);
	f[0] += v[0] * dis;
	f[1] += v[1] * dis;
	f[2] = GetGroundZ(f)
	F[0] = F[2] = 0.0
	TeleportEntity(e, f, F, NULL_VECTOR);
}

stock void ReadMemoryString(int addr, char[] temp, int size)
{
	bool read = true;
	char byte[1];
	int pos;
	temp[0] = 0;

	while( read )
	{
		byte[0] = LoadFromAddress(view_as<Address>(addr + pos), NumberType_Int8);
		pos++;

		if( pos < size/* && (IsCharAlpha(byte[0]) || IsCharNumeric(byte[0])) */)
		{
			StrCat(temp, size, byte);
		} else {
			return;
		}
	}
}

stock RemoveEntityByClassname(const String:n[])
{
	new String:t[64], String:s[64]
	for(new a = 33;a<2049;a++)
	{
		if(IsValidEdict(a))
		{
			GetEdictClassname(a, s, 64)
			GetEntityNetClass(a, t, 64)
			if(StrEqual(n, s, false) || StrEqual(n, t, false)) AcceptEntityInput(a, "Kill");
		}
	}
}
stock RemovePlayerAllWeapon(a)
{
	new e;
	for(new l=0;l<5;l++)
	{
		if((e = GetPlayerWeaponSlot(a, l)) > 0) RemovePlayerItemEx(a, e)
	}
}
stock RemovePlayerItemEx(a, e)
{
	RemovePlayerItem(a, e)
	RemoveEntity(e)
}

stock ResetConVarEx(const String:s[], any:...)
{
	ConVar cvar = FindConVar(s)
	if(cvar) ResetConVar(cvar)
}

stock InitHandle(Handle &h)
{
	if(h) CloseHandle(h)
	h = null
}

/**
 * @brief Run VScript Code
 *
 * @param		code		Code String to run
 */
stock RunScriptCode(const String:code[], any:...)
{
	if(!IsValidEdict(0)) return
	new String:s[256], e = FindEntityByClassname(0, "logic_script")
	VFormat(s, 256, code, 2)
	if(e < 1)
	{
		e = CreateEntityByName("logic_script")
		DispatchSpawn(e);
	}
	SetVariantString(s);
	AcceptEntityInput(e, "RunScriptCode");
}

stock RunScriptFile(const String:code[], any:...)
{
	if(!IsValidEdict(0)) return
	new String:s[256], e = FindEntityByClassname(0, "logic_script")
	VFormat(s, 256, code, 2)
	if(e < 1)
	{
		e = CreateEntityByName("logic_script")
		DispatchSpawn(e);
	}
	SetVariantString(s);
	AcceptEntityInput(e, "RunScriptCode");
}

// stock SendMessage(a, bool sound, const String:f[])
// {
	// new Handle:h, i, String:s[255]
	// strcopy(s, 255, f)
	// i = StrColor(s)
	// if(a) h = StartMessageOne("SayText2", a)
	// else h = StartMessageAll("SayText2")
	// Format(s, 255, "\x01%s", s)
	// if(GetUserMessageType() == UM_BitBuf)
	// {
		// BfWriteByte(h, i)
		// BfWriteByte(h, sound)
		// BfWriteString(h, s); //Message
	// }
	// else
	// {
		// PbSetInt(h, "ent_idx", i)
		// PbSetBool(h, "chat", sound)
		// PbSetString(h, "msg_name", s)
		// PbAddString(h, "params", "")
		// PbAddString(h, "params", "")
		// PbAddString(h, "params", "")
		// PbAddString(h, "params", "")
	// }
	// EndMessage();
	// /*else
	// {
		// if(a)
		// {
			// PrintToChat(a, s)
			// if(sound) EmitGameSoundToClient(a, "HudChat.Message")
		// }
		// else
		// {
			// PrintToChatAll(s)
			// if(sound) EmitGameSoundToAll("HudChat.Message")
		// }
	// }*/
// }

stock SetClientHealthBuffer(a, float f)
{
	SetEntPropFloat(a, Prop_Send, "m_healthBuffer", f)
	SetEntPropFloat(a, Prop_Send, "m_healthBufferTime", GetGameTime())
}

stock SetClientLookAt(a, float F[3])
{
	float f[3], v[3]
	GetClientEyePosition(a, f)
	MakeVectorFromPoints(f, F, v)
	GetVectorAngles(v, v);
	TeleportEntity(a, NULL_VECTOR, v, NULL_VECTOR)
}

stock SetEntityLifeTime(e, float f)
{
	new String:s[32]
	Format(s, 32, "OnUser1 !self:Kill::%f:1", f);
	SetVariantString(s);
	AcceptEntityInput(e, "AddOutput");
	AcceptEntityInput(e, "FireUser1");
}

stock bool SetEntityModelEx(e, const String:s[])
{
	if(!IsValidModel(s)) return false
	SetEntityModel(e, s)
	return true
}

stock SetGlow(a, t, R, r, c, f)
{
	SetEntProp(a, Prop_Send, "m_Glow", t);
	SetEntProp(a, Prop_Send, "m_Glow", R, 4, 1);
	SetEntProp(a, Prop_Send, "m_Glow", r, 4, 2);
	SetEntProp(a, Prop_Send, "m_Glow", c, 4, 3);
	SetEntProp(a, Prop_Send, "m_Glow", f, 4, 4);
}

stock SetScriptValueInt(const String:t[], int i)
{
	RunScriptCode("DirectorScript.MapScript.LocalScript.DirectorOptions.%s <- %i", t, i)
}

stock SortArray(int[]ar, size, int[]z)
{
	Handle hndl = CreateDataPack()
	WritePackCell(hndl, size)
	for(int i=0;i<size;i++)
	{
		ar[i]=i
		WritePackCell(hndl, z[i])
	}
	SortCustom1D(ar, size, SortArrayFunc, hndl);
	CloseHandle(hndl)
	/*new y[size], l, bool filter[size]
	for(new i=0;i<size;i++) y[i] = z[i]
	SortIntegers(y, size, order);
	for(new i=0;i<size;i++)
	{
		for(new j=0;j<size;j++)
		{
			if(!filter[j] && z[j]==y[i])
			{
				ar[l++] = j
				filter[j] = true
				break
			}
		}
	}*/
}

stock StoreStringToAddress(Address p, const char[]s)
{
	int i
	do
	{
		StoreToAddress(p+view_as<Address>(i++), s[i], NumberType_Int8)
	} while(s[i])
}

stock StrAdd(char[] buffer, int maxlength, const char[] source)
{
	return strcopy(buffer[strlen(buffer)], maxlength, source);
}

stock int StrColor(String:s[])
{
	new String:c[10], String:t[24], i, l = strlen(s)+4, a, j
	bool k
	if((j = StrContains(s, "{team:")) >= 0 && StrContains(s, "}") > j+1)
	{
		i = StringToInt(s[j+6])
		strcopy(t, 24, s[j])
		t[StrContains(t, "}")+1] = 0
		if(!IsClientAvailable(i)) i = 0
		ReplaceString(s, l, t, i?"\x03":"\x01")
		k = true
	}
	else if((j = StrContains(s, "{clr:")) >= 0 && StrContains(s, "}") > j+1)
	{
		strcopy(t, 24, s[j])
		strcopy(c, 10, s[j+5])
		t[StrContains(t, "}")+1] = c[StrContains(c, "}")] = 0
		if(StrEqual(c, "red", false)) i = GetAnyClientByTeam(3)
		else if(StrEqual(c, "blue", false)) i = GetAnyClientByTeam(2)
		else if(StrEqual(c, "white", false)) i = GetAnyClientByTeam(1)
	}
	ReplaceString(s, l, "{clr:red}", !k && i?"\x03":"\x04")
	ReplaceString(s, l, "{clr:blue}", !k && i?"\x03":"\x05")
	ReplaceString(s, l, "{clr:white}", !k && i?"\x03":"\x01")
	
	ReplaceString(s, l, "{clr:1}", "\x01")
	ReplaceString(s, l, "{clr:3}", "\x03")
	ReplaceString(s, l, "{clr:4}", "\x04")
	ReplaceString(s, l, "{clr:5}", "\x05")
	/*for(j=1;j<=5;j++)
	{
		FormatEx(t, 24, "{clr:%i}", j)
		FormatEx(c, 10, "\\x0%i", j==3 && i?1:j)
		ReplaceString(s, l, t, c)
	}*/
	while((j = StrContains(s, "{admin:")) >= 0 && StrContains(s, "}") > j+1)
	{
		a = StringToInt(s[j+7])
		strcopy(t, 24, s[j])
		t[StrContains(t, "}")+1] = 0
		ReplaceString(s, l, t, IsClientAvailable(a) && IsAdmin(a)?"\x03":"\x04")
	}
	return i
}

/*stock int StrColor(String:s[])
{
	new String:c[10], String:t[24], i, l = strlen(s), a, j
	if((j = StrContains(s, "{clr:")) >= 0 && StrContains(s, "}") > j+1)
	{
		strcopy(t, 24, s[j])
		strcopy(c, 10, s[j+5])
		t[StrContains(t, "}")+1] = c[StrContains(c, "}")] = 0
	}
	else if((j = StrContains(s, "{team:")) >= 0 && StrContains(s, "}") > j+1)
	{
		i = StringToInt(s[j+6])
		strcopy(t, 24, s[j])
		t[StrContains(t, "}")+1] = 0
		if(!IsClientAvailable(i)) i = 0
	}
	if(StrEqual(c, "red", false)) i = GetAnyClientByTeam(3)
	else if(StrEqual(c, "blue", false)) i = GetAnyClientByTeam(2)
	else if(StrEqual(c, "white", false)) i = GetAnyClientByTeam(1)
	if(t[0]) ReplaceString(s, l, t, i?"\x03":"\x01")
	while((j = StrContains(s, "{admin:")) >= 0 && StrContains(s, "}") > j+1)
	{
		a = StringToInt(s[j+7])
		strcopy(t, 24, s[j])
		t[StrContains(t, "}")+1] = 0
		ReplaceString(s, l, t, IsClientAvailable(a) && IsAdmin(a)?"\x03":"\x04")
	}
	return i
}*/

stock StringIntOperate(const char[]a, const char[]b, char[]s, l, int c)
{
	/*int i = strlen(a), j, k
	if(strlen(b) > i), i = strlen(b)
	i += 12*/
	int d = 1, i, j
	s[0] = 0
	while(d)
	{
		i = GetStringArg(a, d), j = GetStringArg(b, d)
		if(i != -1 && j != -1)
		{
			i = StringToInt(a[i]), j = StringToInt(b[j])
			switch(c)
			{
				case '+': i += j
				case '-': i -= j
				case '*': i *= j
				case '/': i /= j
			}
			Format(s, l, "%s %i", s, i)
		}
		else
		{
			if(i == -1 && j != -1) Format(s, l, "%s %s", s, b[j])
			else if(i != -1 && j == -1) Format(s, l, "%s %s", s, a[i])
			break
		}
		d++
	}
	TrimString(s)
}

stock StringToArray(const String:s[], any:z[], l)
{
	int j, c
	z[0] = StringToInt(s)
	for(int i=1;i<l;i++)
	{
		if((j = StrContains(s[c], " ")+1)) c+=j, z[i] = StringToInt(s[c])
		else z[i] = 0
	}
}

/*stock TakeDamage(a, b, c, float d, t=0, const Float:p[3]=NULL_VECTOR)
{
	new e = FindEntityByClassname(0, "point_hurt"), String:s[12]
	if(e < 1)
	{
		e = CreateEntityByName("point_hurt")
		DispatchSpawn(e);
	}
	Format(s, 12, "bhurt%i", a);
	DispatchKeyValue(a, "targetname", s);
	DispatchKeyValue(e, "DamageTarget", s);
	SetEntProp(e, Prop_Data, "m_bitsDamageType", t)
	FloatToString(d, s, 12)
	DispatchKeyValue(e, "Damage", s);
	TeleportEntity(e, p, NULL_VECTOR,NULL_VECTOR)
	AcceptEntityInput(e, "Hurt", b);
}

stock TakeDamage2(a, b, c, float d, t=0)
{
	new e = FindEntityByClassname(0, "trigger_hurt"), String:s[12]
	if(e < 1)
	{
		e = CreateEntityByName("trigger_hurt")
		DispatchSpawn(e);
	}
	SetEntPropFloat(e, Prop_Data, "m_flDamage", d)
	SetEntProp(e, Prop_Data, "m_bitsDamageInflict", t)
	SetEntProp(e, Prop_Data, "m_hurtEntities", a)
	Format(s, 12, "thurt%i", b);
	DispatchKeyValue(b, "targetname", s);
	SetEntPropString(e, Prop_Data, "m_sMaster", s)
	
	AcceptEntityInput(e, "Enable");
}*/
stock TE_SendBox(float vMins[3], float vMaxs[3])
{
	float vPos1[3], vPos2[3], vPos3[3], vPos4[3], vPos5[3], vPos6[3];
	vPos1 = vMaxs;
	vPos1[0] = vMins[0];
	vPos2 = vMaxs;
	vPos2[1] = vMins[1];
	vPos3 = vMaxs;
	vPos3[2] = vMins[2];
	vPos4 = vMins;
	vPos4[0] = vMaxs[0];
	vPos5 = vMins;
	vPos5[1] = vMaxs[1];
	vPos6 = vMins;
	vPos6[2] = vMaxs[2];
	TE_SendBeam(vMaxs, vPos1);
	TE_SendBeam(vMaxs, vPos2);
	TE_SendBeam(vMaxs, vPos3);
	TE_SendBeam(vPos6, vPos1);
	TE_SendBeam(vPos6, vPos2);
	TE_SendBeam(vPos6, vMins);
	TE_SendBeam(vPos4, vMins);
	TE_SendBeam(vPos5, vMins);
	TE_SendBeam(vPos5, vPos1);
	TE_SendBeam(vPos5, vPos3);
	TE_SendBeam(vPos4, vPos3);
	TE_SendBeam(vPos4, vPos2);
}

stock TE_SendBeam(const float vMins[3], const float vMaxs[3])
{
	TE_SetupBeamPoints(vMins, vMaxs, PrecacheModel("materials/sprites/laserbeam.vmt"), 0, 0, 0, 60.0, 5.0, 5.0, 1, 0.0, { 255, 255, 255, 255 }, 0);
	TE_SendToAll();
}

stock TeleportDeadPlayers(const Float:x[3]=NULL_VECTOR, const Float:y[3]=NULL_VECTOR, const Float:z[3]=NULL_VECTOR)
{
	new a;
	while((a = FindEntityByClassname(a, "survivor_death_model")) != -1)
	{
		if(IsValidEnt(a)) TeleportEntity(a, x, y, z);
	}
}

/*stock TeleportEntityEx(e, a=0, bool b=false) // "b" is use for player whither on cursor
{
	new Float:X[3], Float:Y[3], Float:Z[3]
	GetEntityOrigin(a, X);
	GetEntityRotation(a, Y);
	GetEntityVelocity(a, Z);
	if(b)
	{
		GetClientEyePosition(a, X);
		GetClientEyeAngles(a, Y);
		TR_TraceRayFilter(X, Y, MASK_OPAQUE, RayType_Infinite, TR_DontHitTarget, -1);
		if(TR_DidHit()) TR_GetEndPosition(X);
		Y = NULL_VECTOR
		Z = NULL_VECTOR
	}
	TeleportEntity(e, X, Y, Z);
}*/

stock TeleportEntityToEntity(e, a)
{
	float x[3], y[3], z[3]
	GetEntPropVector(a, Prop_Data, "m_vecAbsOrigin", x)
	GetEntPropVector(a, Prop_Data, "m_angRotation", y)
	GetEntPropVector(a, Prop_Data, "m_vecVelocity", z)
	TeleportEntity(e, x, y, z);
}

stock TeleportEntityToClientPoint(e, a)
{
	float x[3], y[3]
	GetClientEyePosition(a, x);
	GetClientEyeAngles(a, y);
	TR_TraceRayFilter(x, y, MASK_OPAQUE, RayType_Infinite, TR_DontHitTarget, -1);
	if(!TR_DidHit()) return
	TR_GetEndPosition(x);
	TeleportEntity(e, x, NULL_VECTOR, NULL_VECTOR);
}

stock TrimComments(String:f[])
{
	new String:s[512], j
	while((j = StrContains(f, "//")) >= 0)
	{
		strcopy(s, 512, f[j])
		if((j = StrContains(s, "\n")) >= 0) s[j] = 0
		ReplaceString(f, strlen(f), s, "")
	}
	TrimString(f)
}

/*stock TrimComments(const String:f[], String:s[], l)
{
	new i, j, b, bool m
	while(f[i] != 0 && j<l-1)
	{
		if(b == 1 && !m)
		{
			if(f[i] == '*' && f[i+1] == '/')
			{
				i++
				if(f[i+1] == '\n') i++
				b = 0
			}
		}
		else if(b == 2 && !m)
		{
			if(f[i] == '\n')
			{
				i--
				b = 0
			}
		}
		else
		{
			if(f[i] == '"')
			{
				if(m) m = false
				else m = true
			}
			if(f[i] == '/' && f[i+1] == '*' && !m) b = 1
			else if(f[i] == '/' && f[i+1] == '/' && !m) b = 2
			else
			{
				s[j] = f[i]
				j++
			}
		}
		i++
	}
	s[j] = 0
}*/

stock int FindClientByName(const String:s[], bool b=false)
{
	char t[32];
	for(new i = 1; i < 33;i++)
	{
		if(!IsClientConnected(i)) continue;
		GetClientName(i, t, 32);
		if(StrEqual(t, s, false) || (b && StrContains(t, s, false) >= 0)) return i;
	}
	return 0;
}

stock int FindClientBySteamID(AuthIdType a, const String:s[])
{
	char t[32];
	int i
	for(i = 1; i <=MaxClients;i++)
	{
		if(!IsClientAuthorized(i) || IsFakeClient(i)) continue;
		GetClientAuthId(i, a, t, 32);
		if(!strcmp(t, s)) return i;
	}
	return 0;
}

stock int FindClientBySteamIDAll(const String:s[])
{
	char t[32];
	int a, i
	for(i = 1; i <=MaxClients;i++)
	{
		if(!IsClientAuthorized(i) || IsFakeClient(i)) continue;
		for(a = 1; a < 4; a++)
		{
			GetClientAuthId(i, AuthIdType:a, t, 32);
			if(!strcmp(t, s)) return i;
		}
	}
	return 0;
}

/*stock int FindClientBySteamID2(const String:s[])
{
	char t[32];
	for(new i = 1; i <=MaxClients;i++)
	{
		if(!IsClientAuthorized(i) || IsFakeClient(i)) continue;
		GetClientAuthId(i, AuthId_Steam2, t, 32);
		if(!strcmp(t, s)) return i;
	}
	return 0;
}*/

stock int SearchTarget(const String:s[])
{
	if(s[0] == '#') return GetClientOfUserId(StringToInt(s[1]))
	if(s[0] == '@') return FindClientByName(s[1])
	new a = StringToInt(s);
	if(a > 0 && IsValidEdict(a)) return a
	return 0
}
stock int GetAnyClientByTeam(i)
{
	for(new a=1;a<33;a++)
	{
		if(IsClientInTeam(a, i)) return a
	}
	return 0
}
stock int GetArrayMaxOrMinValue(any:a[], l, bool b)
{
	new max = a[0], min = a[0]
	for(new i = 0;i < l;i++)
	{
		if(a[i] > max) max = a[i]
		if(a[i] < min) min = a[i]
	}
	return (b) ? max:min
}

/*
* @param	b	true for single only
*/
stock int GetArrayMaxArray(any:a[], l, bool b=false, ignore=0, s=0)
{
	int i, max, ar = -1
	for(i = s;i < l;i++)
	{
		if(ignore & 1<<i) continue;
		if(a[i] > max) max = a[i], ar = i
	}
	if(b && ar != -1)
	{
		for(i = s;i < l;i++)
		{
			if(!(ignore & 1<<i) && a[i] == max && ar != i) return -1
		}
	}
	return ar;
}

/*stock int GetArrayMaxArray(any:a[], l, &ar, ignore=0, s=0, &arb=0)
{
	new max, b, i
	for(i = s;i < l;i++)
	{
		if(ignore & 1<<i) continue;
		max = a[i]
		ar = i
		for(i = ar;i < l;i++)
		{
			if(ignore & 1<<i) continue;
			if(a[i] > max)
			{
				max = a[i]
				ar = i
				arb = 0
				b = 0
			}
			if(a[i] == max)
			{
				b++
				arb |= 1<<i
			}
		}
		break
	}
	return b;
}*/

stock int GetArrayMinArray(any:a[], l, ignore=0, s=0)
{
	new min, i, ar = -1
	for(i = s;i < l;i++)
	{
		if(ignore & 1<<i) continue;
		min = a[i]
		ar = i
		for(i = ar;i < l;i++)
		{
			if(ignore & 1<<i) continue;
			if(a[i] < min) min = a[i], ar = i
		}
		break
	}
	return ar;
}

stock int GetArrayValueBits(any:a[], l, any:z, ignore=0, s=0)
{
	new b
	for(new i = s;i < l;i++)
	{
		if(!(ignore & 1<<i) && a[i] == z) b |= 1<<i
	}
	return b
}

stock int GetArrayValueNums(any:a[], l, any:z, ignore=0, s=0)
{
	new b
	for(new i = s;i < l;i++)
	{
		if(!(ignore & 1<<i) && a[i] == z) b++
	}
	return b
}

/*stock int GetMaxOrMinArray(any:a[], l, bool t, n=-1, o=false)
{
	bool b;
	for(new i = 0;i < l;i++)
	{
		if(i == n) continue;
		if(o && !i) continue
		for(new m=0;m<l;m++)
		{
			if(m == n) continue;
			if((a[i] >= a[m] && t) || (a[i] <= a[m] && !t)) b=true;
			else
			{
				b=false
				break;
			}
		}
		if(b) return i
	}
	return -1;
}*/

stock int GetBarString(float f, float F, j, String:s[], l, c='|')
{
	s[0] = 0
	new i, m = RoundToCeil((f/F) * float(j)), z;
	while(i < j && strlen(s)-2<l)
	{
		if(i < m) s[i] = c, z++;
		else s[i] = ' '
		i++;
	}
	Format(s, l, "[%s]", s)
	return z
}

stock int GetClientNums(bool human)
{
	new a;
	for(new i = 1;i<=MaxClients;i++)
	{
		if(IsClientAvailable(i))
		{
			if(human && !IsFakeClient(i)) a++
			else if(!human && IsFakeClient(i)) a++
		}
	}
	return a
}

stock int GetRandomClient(team=0, alive=-1, human=-1, filter=0)
{
	new l[32], L
	for(new i = 1;i<=MaxClients;i++)
	{
		if(i != filter && IsClientAvailable(i, 1, team, alive, human)) l[L++]=i
	}
	if(!L) return 0
	return l[GetRandomInt(0, L-1)]
}

stock int GetWeaponInPlayerSlot(w, a)
{
	if(!IsValidEnt(w)) return -1;
	for(new i = 0;i<6;i++)
	{
		if(GetPlayerWeaponSlot(a, i) == w) return i
	}
	return -1;
}

stock Float:GS_ClientNextAttackTime(a, float b=-1.0)
{
	if(b >= 0.0) SetEntPropFloat(a, Prop_Send, "m_flNextAttack", b)
	return GetEntPropFloat(a, Prop_Send, "m_flNextAttack")
}

stock int GS_CvarBit(const String:t[], b=-1)
{
	ConVar cvar = FindConVar(t)
	if(!cvar) return 0
	new String:s[40]
	if(b != -1)
	{
		BitToString(b ,s ,40)
		SetConVarString(cvar, s)
	}
	GetConVarString(cvar, s, 40)
	return StringToBit(s)
}

stock int GS_CvarInt(const String:s[], b=-65535)
{
	ConVar cvar = FindConVar(s)
	if(!cvar) return 0
	if(b != -65535) SetConVarInt(cvar, b)
	return GetConVarInt(cvar)
}

stock float GS_CvarFloat(const String:s[], float b=-65535.0)
{
	ConVar cvar = FindConVar(s)
	if(!cvar) return 0.0
	if(b != -65535.0) SetConVarFloat(cvar, b)
	return GetConVarFloat(cvar)
}
stock GS_CvarString(const String:s[], const String:t[]="/null", String:n[]="", l=0)
{
	ConVar cvar = FindConVar(s)
	if(!cvar) return
	if(!StrEqual(t, "/null")) SetConVarString(cvar, t)
	GetConVarString(cvar, n, l)
}

stock int GS_EntityHealth(a, b=-1)
{
	if(b > -1) SetEntProp(a, Prop_Data, "m_iHealth", b);
	new i = GetEntProp(a, Prop_Data, "m_iHealth");
	if(i < 0 || GetEntProp(a, Prop_Data, "m_lifeState")) i = 0
	return i
}

stock int GS_EntityMaxHealth(a, b=-1)
{
	if(b > -1) SetEntProp(a, Prop_Data, "m_iMaxHealth", b);
	return GetEntProp(a, Prop_Data, "m_iMaxHealth");
}

stock int GS_TempoState(b=-1)
{
	new a = FindEntityByClassname(0, "terror_player_manager")
	if(a < 1) return 0
	if(b > -1) SetEntProp(a, Prop_Send, "m_tempoState", b);
	return GetEntProp(a, Prop_Send, "m_tempoState");
}
/**
 * 0 = Midnight
 * 1 = Dawn
 * 2 = Morning
 * 3 = Afternoon
 * 4 = Dusk
 * 5 = Evening
 */
stock int GS_TimeOfDay(b=-1)
{
	if(!IsValidEdict(0)) return -1
	if(b > -1) SetEntProp(0, Prop_Send, "m_iTimeOfDay", b);
	return GetEntProp(0, Prop_Send, "m_iTimeOfDay");
}

/*stock int GS_WeaponID(a, b=-1)
{
	if(IsValidWeaponSpawner(a))
	{
		if(b > -1) SetEntProp(a, Prop_Data, "m_weaponID", b);
		return GetEntProp(a, Prop_Data, "m_weaponID");
	}
	else if(IsValidWeapon(a))
	{
		char s[40]
		GetEdictClassname(a, s, 40)
		return GetWeaponIDFromClass(s)
	}
	return 0
}*/

/*stock int GS_WeaponID(a, b=-1)
{
	if(IsValidWeaponSpawner(a))
	{
		if(b > -1) SetEntProp(a, Prop_Data, "m_weaponID", b);
		return GetEntProp(a, Prop_Data, "m_weaponID");
	}
	else if(IsValidWeapon(a))
	{
		char s[40]
		GetEdictClassname(a, s, 40)
		return GetWeaponIDFromClass(s)
	}
	return 0
}*/

stock Float:GS_WeaponNextAttackTime(a, float b=-1.0)
{
	/*for(int i=6132;i<=6140;i+=4)
	{
		if(GetEntDataFloat(a, i))
		{
			if(b >= 0.0) SetEntDataFloat(a, i, b), ChangeEdictState(a, i);
			return GetEntDataFloat(a, i)
		}
	}*/
	if(b >= 0.0) SetEntPropFloat(a, Prop_Send, "m_flNextPrimaryAttack", b)
	return GetEntPropFloat(a, Prop_Send, "m_flNextPrimaryAttack")
}

stock bool HasLeftStartArea()
{
	new a = FindEntityByClassname(-1, "terror_player_manager")
	if(a > 0 && GetEntProp(a, Prop_Send, "m_hasAnySurvivorLeftSafeArea")) return true
	return false
}

stock bool KvReadString(const String:f[], const String:sec[], const String:key[], String:s[], l)
{
	KeyValues h = CreateKeyValues("IA")
	new String:t[l], bool:k
	h.ImportFromFile(f)
	if(h.JumpToKey(sec))
	{
		h.GetString(key, t, l, "null")
		if(!StrEqual(t, "null"))
		{
			strcopy(s, l, t)
			k = true
		}
	}
	CloseHandle(h)
	return k
}

stock KvWriteString(const String:f[], const String:sec[], const String:key[], const String:format[], any:...)
{
	new String:s[255]
	KeyValues h = CreateKeyValues("IA")
	h.ImportFromFile(f)
	VFormat(s, 255, format, 5)
	h.JumpToKey(sec, true)
	h.SetString(key, s)
	h.Rewind();
	KeyValuesToFile(h, f)
	CloseHandle(h)
}

stock int SpawnRagdoll(int a, const String:s[])
{
	new b = CreateEntityByName("prop_ragdoll")
	if(b > 0)
	{
		SetEntityModelEx(b, s);
		DispatchSpawn(b)
		ActivateEntity(b)
		SetEntProp(b, Prop_Data, "m_CollisionGroup", 2);
		SetEntProp(b, Prop_Data, "m_nSequence", GetEntProp(a, Prop_Send, "m_nSequence"));
		TeleportEntityToEntity(b, a)
		return b
	}
	return 0
}

stock bool SpawnSI(const String:s[], a=0, bool b=true,const Float:x[3]=NULL_VECTOR)
{
	//if(!StrContains(s, "witch", false)) CheatCommand(a, "z_spawn_old", "%s%s", s, a?"":" auto")
	if(!StrContains(s, "witch", false))
	{
		new e = CreateEntityByName("witch")
		DispatchSpawn(e)
		if(b) TeleportEntityToClientPoint(e, a)
		else if(a) TeleportEntityToEntity(e, a)
		else TeleportEntity(e, x, NULL_VECTOR, NULL_VECTOR)
	}
	else
	{
		new e = CreateFakeClient(" ")
		if(e < 1) return false
		ChangeClientTeam(e, 3)
		if(a)
		{
			CheatCommand(a, "z_spawn_old", "%s", s)
			if(!b) TeleportEntityToEntity(e, a)
		}
		else
		{
			CheatCommand(e, "z_spawn_old", "%s auto", s)
			TeleportEntity(e, x, NULL_VECTOR, NULL_VECTOR)
		}
		KickClient(e)
	}
	return true
}

stock int StringToBit(const String:s[])
{
	new i, j;
	if(47 < s[0] < 58) i |= 1<<StringToInt(s)
	while(s[j] != '\0')
	{
		if(s[j] == '|') i |= 1<<StringToInt(s[j+1])
		j++;
	}
	return i
}

stock StringToVector(const String:s[], float f[3])
{
	f[0] = StringToFloat(s[GetStringArg(s, 1)])
	f[0] = StringToFloat(s[GetStringArg(s, 2)])
	f[0] = StringToFloat(s[GetStringArg(s, 3)])
}

/* bool */
stock bool AryEqual(any:a[], l, ignore=0, s=0)
{
	new j = a[s]
	for(new i = s;i < l;i++)
	{
		if(ignore & 1<<i) continue;
		if(a[i] != j) return false
	}
	return true
}

stock bool IsClientInTeam(int a, int b)
{
	return IsClientInGame(a) && GetClientTeam(a) == b
}

stock bool IsClientInTeamAlive(int a, int b)
{
	return IsClientInGame(a) && IsPlayerAlive(a) && GetClientTeam(a) == b
}

stock bool IsCreateBot(a)
{
	if(IsFakeClient(a))
	{
		new String:n[14]
		GetEntityNetClass(a, n, 14)
		return StrEqual(n, "CTerrorPlayer")
	}
	return false
}

stock bool IsCSGO()
{
	char s[32]
	GetGameFolderName(s, 32)
	return StrEqual(s, "csgo")
}

stock bool IsEntVisibleTo(a, b)
{
	new Float:f[3], Float:p[3]
	if(a < 33) GetClientEyePosition(a, f)
	else GetEntityOrigin(a, f)
	if(b < 33) GetClientEyePosition(b, p)
	else GetEntityOrigin(b, p)
	DataPack c = new DataPack()
	c.WriteCell(a)
	c.WriteCell(b)
	TR_TraceRayFilter(f, p, MASK_SOLID, RayType_EndPoint, TR_DontHitBloodly, c);
	CloseHandle(c)
	if(TR_DidHit() && TR_GetEntityIndex() == b) return true
	return false
}

stock bool IsFakePlayer(a)
{
	new String:s[40]
	GetEntityNetClass(a, s, 40)
	return (IsFakeClient(a) && StrEqual(s, "CTerrorPlayer"))
}

stock bool IsFakeClientEx(a)
{
	return (IsFakeClient(a) && !(GetEntProp(a, Prop_Send, "m_fFlags") &1<<8))
}

/*stock bool IsFinale()
{
	return (FindEntityByClassname(0, "trigger_finale") != -1)
}*/

stock bool IsL4D2()
{
	char s[32]
	GetGameFolderName(s, 32)
	return StrEqual(s, "left4dead2")
}

stock bool IsPlayerCanMove(a)
{
	return !(GetEntityFlags(a)&FL_FROZEN)
}

stock bool IsPlayerCanReachPoint(a, const Float:f[3])
{
	new Float:p[3]
	GetClientEyePosition(a, p)
	TR_TraceRayFilter(p, f, MASK_SOLID, RayType_EndPoint, TR_DontHitTarget, a);
	return !TR_DidHit()
}

stock bool IsPlayerGhost(a)
{
	return (GetEntProp(a, Prop_Send, "m_isGhost") != 0)
}

stock bool IsValidVector(const Float:f[3])
{
	return (f[0] != 0.0 || f[1] != 0.0 || f[2] != 0.0)
}
stock bool IsValidInfected(a)
{
	if(!IsValidEnt(a)) return false
	new String:s[64]
	GetEdictClassname(a, s, 64)
	return (StrEqual(s, "infected"))
}
stock bool IsValidModel(const String:s[])
{
	return (IsValidString(s) && (IsModelPrecached(s) || PrecacheModel(s) > 0))
}

stock bool IsValidWeaponSpawner(a)
{
	return (IsValidEnt(a) && FindDataMapInfo(a, "m_weaponID") != -1 && GetEntProp(a, Prop_Data, "m_weaponID") != 54)
}

stock bool ReadFileStringLine(const String:f[], const String:t[], String:s[]="", l=0)
{
	File h = OpenFile(f, "rt")
	if(h == null) return false;
	bool k = false;
	char c[255];
	new i;
	while(ReadFileLine(h, c, 255))
	{
		if(StrContains(c, t, false) >= 0)
		{
			if((i = StrContains(c, "//")) >= 0) c[i] = '\0'
			TrimString(c)
			if(c[0] == '\0') continue;
			strcopy(s, l, c)
			k = true;
			break;
		}
	}
	CloseHandle(h)
	return k;
}

/*stock bool WriteFileStringLine(const String:f[], const String:t[], const String:b[], any:...)
{
	File h = OpenFile(f, "rt")
	if(h == null)
	{
		h = OpenFile(f, "wt");
		CloseHandle(h);
		h = OpenFile(f, "rt");
	}
	new i = FileSize(f)+255;
	bool k;
	new String:a[i], String:a1[i], String:s[i]
	VFormat(s, i, b, 4)
	ReadFileString(h, a, i)
	new j = StrContains(a, t, false)
	if(j >= 0 && t[0] != '\0')
	{
		Format(a1, i, a[j])
		while(a[j] != '\n' && j >= 0) j--;
		a[j] = 0, j = 0
		while(a1[j] != '\n' && a1[j] != 0) j++;
		Format(a1, i, a1[j])
		TrimString(a)
		TrimString(a1)
		TrimString(s)
		if(s[0] == 0) Format(a, i, "%s\n%s\n", a, a1)
		else Format(a, i, "%s\n%s\n%s\n", a, s, a1)
	}
	else Format(a, i, "%s\n%s", a, s)
	CloseHandle(h)
	h = OpenFile(f, "wt")
	WriteFileString(h, a, false)
	k = true;
	CloseHandle(h);
	return k;
}*/

/*stock bool INI_ClearSection(const String:file[], const String:sec[], bool m=false)
{
	if(sec[0] == 0) return false;
	char f[256]
	strcopy(f, 256, file)
	if(strlen(f)-StrContains(f, ".ini") != 4) Format(f, 256, "%s.ini", f)
	File h = OpenFile(f, "rt");
	if(h == null) return false;
	new j;
	bool k;
	new String:section[64]
	ReadFileString(h, sFS1, iSL)
	TrimComments(sFS1, sFS, iSL)
	sFS1 = ""
	Format(section, 64, "[%s]", sec)
	if((j = StrContains(sFS, section, false)) >= 0)
	{
		if(!m)
		{
			while(sFS[j] != ']') j++;
			j++
		}
		Format(sFS1, iSL, sFS[j])
		sFS[j] = 0
		j = StrContains(sFS1[1], "[")
		if(j > 0) Format(sFS1, iSL, sFS1[j])
		else sFS1[0] = 0
		TrimString(sFS)
		TrimString(sFS1)
		Format(sFS, iSL, "%s\n\n%s\n", sFS, sFS1)
		CloseHandle(h)
		h = OpenFile(f, "wt")
		WriteFileString(h, sFS, false)
		k = true;
	}
	sFS = ""
	sFS1 = ""
	CloseHandle(h);
	return k;
}*/

/*stock bool INI_ReadSection(const String:file[], const String:sec[], String:s[]="", l=0)
{
	if(sec[0] == 0) return false
	char f[256]
	strcopy(f, 256, file)
	if(strlen(file)-StrContains(file, ".ini") != 4) Format(f, 256, "%s.ini", file)
	File h = OpenFile(f, "rt");
	if(h == null) return false;
	new String:section[64], j, bool k
	sFS = ""
	ReadFileString(h, sFS, iSL);
	TrimComments(sFS, sFS1, iSL)
	sFS = ""
	Format(section, 64, "[%s]", sec);
	if((j = StrContains(sFS1, section, false)) >= 0)
	{
		while(sFS1[j] != ']') j++;
		j++
		strcopy(s, l, sFS1[j])
		j = 1
		while(s[j] != '[' && s[j] != 0) j++
		s[j] = 0
		TrimString(s)
		k = true
	}
	sFS1 = ""
	CloseHandle(h);
	return k
}

stock bool INI_ReadString(const String:file[], const String:sec[], const String:ke[], String:s[]="", l=0)
{
	char f[256]
	strcopy(f, 256, file)
	if(strlen(file)-4 != StrContains(file, ".ini")) Format(f, 256, "%s.ini", file)
	if(!FileExists(f) || ke[0] == 0) return false
	new String:key[255], j, bool k
	if(INI_ReadSection(f, sec, sFS, iSL))
	{
		Format(key, 255, "%s=", ke);
		if((j = StrContains(sFS, key, false)) >= 0)
		{
			Format(sFS, iSL, sFS[j])
			Format(s, l, sFS[StrContains(sFS, "=")+1])
			j = 0
			while(s[j] != '\n' && s[j] != 0) j++;
			s[j] = 0
			TrimString(s)
			k = true
		}
	}
	sFS = ""
	return k;
}

stock bool INI_ReadStringLine(const String:file[], const String:sec[], m, String:s[], l)
{
	if(sec[0] == 0 || m < 1) return false;
	char f[256]
	strcopy(f, 256, file)
	if(strlen(file)-StrContains(file, ".ini") != 4) Format(f, 256, "%s.ini", file)
	if(!FileExists(f)) return false
	new j
	if(!INI_ReadSection(f, sec, sFS, iSL)) return false
	Format(sFS, iSL, sFS[StrContains(sFS, "]")+1]);
	TrimString(sFS);
	while(m > 1)
	{
		j = StrContains(sFS, "\n");
		if(j < 1)
		{
			sFS = ""
			return false
		}
		Format(sFS, iSL, "%s", sFS[j]);
		TrimString(sFS);
		m--;
	}
	j = 0
	while(sFS[j] != '\n' && sFS[j] != 0) j++;
	sFS[j] = 0
	strcopy(s, l, sFS)
	TrimString(s)
	sFS = ""
	return true
}*/

/*stock bool INI_WriteString(const String:file[], const String:sec[], const String:key[] , const String:format[], any:...)
{
	if(sec[0] == 0 || key[0] == 0) ThrowError("Section or key is invaild. (section=\"%s\", key=\"%s\")", sec, key)
	char f[256]
	strcopy(f, 256, file)
	if(strlen(f)-StrContains(f, ".ini") != 4) Format(f, 256, "%s.ini", f)
	File h = OpenFile(f, "rt");
	if(h == null)
	{
		h = OpenFile(f, "wt");
		CloseHandle(h);
		h = OpenFile(f, "rt");
	}
	new j, bool k;
	new String:t[500], String:s[500], String:section[64]
	VFormat(s, 500, format, 5)
	ReadFileString(h, sFS, iSL)
	CloseHandle(h)
	Format(section, 64, "[%s]", sec)
	if(StrContains(s, "/no_sign", false) == 0) Format(s, 500, key)
	else if(StrContains(s, "/del", false) == 0) s = ""
	else Format(s, 500, "%s=%s", key, s)
	ReplaceString(s, 500, "[", "")
	ReplaceString(s, 500, "]", "")
	TrimString(s)
	if((j = StrContains(sFS, section, false)) >= 0)
	{
		Format(sFS1, iSL, sFS[j])
		sFS[j] = 0
		j = StrContains(sFS1[2], "[")
		if(j > 0)
		{
			Format(sFS2, iSL, sFS1[j])
			sFS1[j] = 0
		}
		TrimString(sFS1)
		if((j =StrContains(sFS1, key, false)) > 0)
		{
			Format(t, 500, sFS1[j])
			j = 0;
			while(t[j] != '\n' && t[j] != 0) j++
			t[j] = 0
			TrimString(t)
			ReplaceString(sFS1, iSL, t, s)
			ReplaceString(sFS1, iSL, "\n\n", "\n")
		}
		else Format(sFS1, iSL, "%s\n%s", sFS1, s)
		TrimString(sFS)
		TrimString(sFS1)
		TrimString(sFS2)
		if(IsValidString(sFS)) Format(sFS, iSL, "%s\n\n", sFS)
		if(IsValidString(sFS1)) Format(sFS1, iSL, "%s\n\n", sFS1)
		Format(sFS, iSL, "%s%s%s", sFS, sFS1, sFS2)
		k = true;
	}
	else
	{
		TrimString(sFS)
		Format(sFS, iSL, "%s\n\n%s\n%s\n", sFS, section, s)
		k = true;
	}
	if(k)
	{
		h = OpenFile(f, "wt")
		WriteFileString(h, sFS, false)
		CloseHandle(h);
	}
	sFS = ""
	sFS1 = ""
	sFS2 = ""
	return k;
}*/

stock bool IsAdmin(a)
{
	return (GetUserFlagBits(a) > 0)
}

stock bool IsGasCan(e, bool b=true)
{
	static char m[40], s[64]
	GetEdictClassname(e, m, 40)
	GetEntityModel(e, s, 64)
	return (StrEqual(m[5], "physics") || StrEqual(m[7], "gascan")) && StrEqual(s, "models/props_junk/gascan001a.mdl") && (!GetEntProp(e, Prop_Data, "m_nSkin") || b)
}

stock bool IsExplosive(e)
{
	static char m[40], s[64]
	GetEdictClassname(e, m, 40)
	GetEntityModel(e, s, 64)
	return StrEqual(m[5], "physics") && (StrContains(s, "propanecanister") > 0 || StrContains(s, "oxygentank") > 0 || StrContains(s, "explosive_box") > 0)
}

stock bool IsIncap(a)
{
	return GetEntProp(a, Prop_Send, "m_isIncapacitated") != 0
}

stock bool IsValidString(const String:s[])
{
	return (!StrEqual(s, "_") && s[0] != 0)
}

stock bool StringToBool(const String:s[])
{
	return (StringToInt(s) != 0)
}
stock Float:GetEntityDistance(a, b)
{
	new Float:f[3], Float:F[3];
	GetEntPropVector(a, Prop_Data, "m_vecAbsOrigin", f);
	GetEntPropVector(b, Prop_Data, "m_vecAbsOrigin", F);
	return GetVectorDistance(f, F)
}
stock Float:GetFriendlyFireFactor()
{
	char s[64]
	GetConVarString(FindConVar("z_difficulty"), s, 64)
	if(StrEqual(s, "Impossible", false)) s = "expert"
	Format(s, 64, "survivor_friendly_fire_factor_%s", s)
	return GetConVarFloat(FindConVar(s))
}
// Extra Functag
stock Action:EmitBurstSound(Handle:h, e)
{
	EmitGameSoundToAll("c2m5.fireworks_burst", e)
}

stock Action:ResetCommandCheatFlags(Handle:h, Handle:p)
{
	ResetPack(p)
	new String:cmd[256]
	ReadPackString(p, cmd, 256)
	SetCommandFlags(cmd, ReadPackCell(p));
}

stock bool TR_DontHitTarget(entity, mask, a)
{
	if(entity > 0 && (entity == a || a == -1)) // Check if the TraceRay hit the client.
	{
		return false; // Don't let the entity be hit
	}
	return true; // It didn't hit client
}

stock bool TR_DontHitBloodly(e, mask, DataPack p)
{
	if(e > 0)
	{
		p.Reset()
		int a = p.ReadCell()
		if(e == a) return false
		int b = p.ReadCell()
		if(e == b) return true
		if(FindDataMapInfo(e, "m_bloodColor") != -1 && (a > 32 || GetClientTeam(a) != b)) return false
	}
	return true
}

stock bool TR_DontHitPlayer(entity, mask, a)
{
	if(entity > 0 && (entity == a || a == -1)) // Check if the TraceRay hit the client.
	{
		return false; // Don't let the entity be hit
	}
	return true; // It didn't hit client
}

stock SortArrayFunc(elem1, elem2, array[], Handle:hndl)
{
	ResetPack(hndl)
	new i = ReadPackCell(hndl), z[i]
	for(new j=0;j<i;j++) z[j] = ReadPackCell(hndl)
	if(z[elem2] < z[elem1] || elem1 > elem2) return -1;
	if(z[elem1] < z[elem2] || elem2 > elem1) return 1;
	return 0;
}

// Countdown Timer
enum CountdownTimer
{
	CountdownTimer_Null
}
stock CountdownTimer GetRawCountdownTimer(Address a, i)
{
	return view_as<CountdownTimer>(a+Address:i)
}

stock CountdownTimer GetEntityCountdownTimer(a, i)
{
	return view_as<CountdownTimer>(GetEntityAddress(a)+Address:i)
}

stock bool IsCountdownTimerActive(CountdownTimer i)
{
	float f = LoadFromAddress(view_as<Address>(i)+Address:8, NumberType_Int32)
	return f > 0.0 && GetGameTime() < f
}

stock SetCountdownTimer(CountdownTimer i, float d, bool b=true)
{
	if(b) StoreToAddress(view_as<Address>(i)+Address:4, d, NumberType_Int32)
	StoreToAddress(view_as<Address>(i)+Address:8, GetGameTime()+d, NumberType_Int32)
}

stock float GetCountdownTimer(CountdownTimer i, bool timestamp)
{
	return LoadFromAddress(view_as<Address>(i)+Address:(timestamp?8:4), NumberType_Int32)
}

stock float GetCountdownTimerRemain(CountdownTimer i)
{
	float f = LoadFromAddress(view_as<Address>(i)+Address:8, NumberType_Int32)
	if(f > 0.0 && (f = view_as<float>(LoadFromAddress(view_as<Address>(i)+Address:8, NumberType_Int32))-GetGameTime()) < 0.0) f = 0.0
	return f
}
