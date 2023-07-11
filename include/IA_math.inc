stock GetVectorForward(const float vecAng[3], float result[3])
{
	float flPitch = DegToRad(vecAng[0]);
	float flYaw = DegToRad(vecAng[1]);
	result[0] = Cosine(flPitch) * Cosine(flYaw)
	result[1] = Cosine(flPitch) * Sine(flYaw)
	result[2] = Sine(-flPitch)
}

stock GetVectorCross(const float p1[3], const float p2[3], const float p3[3], float result[3])
{
	float dx = p1[0] - p2[0], dy = p1[1] - p2[1], u = (p3[0] - p1[0]) * dx + (p3[1] - p1[1]) * dy;
	u /= dx * dx + dy * dy;
	result[0] = p1[0] + u * dx
	result[1] = p1[1] + u * dy
	result[2] = 0.0
}

stock GetVectorReflect(const float angle[3], const float normal[3], float result[3], bool:bRejectMethod=true, float fFactor = 2.0)
{
	float flPitch = DegToRad(angle[0]);
	float flYaw = DegToRad(angle[1]);
	result[0] = Cosine(flPitch) * Cosine(flYaw)
	result[1] = Cosine(flPitch) * Sine(flYaw)
	result[2] = Sine(-flPitch)
	//GetVectorForward(vec1, result)
	if(bRejectMethod)
	{
		float f[3]
		GetVectorReject(result, normal, f)
		ScaleVector(f, fFactor)
		SubtractVectors(f, result, result);
	}
	/*else
	{
		local vecProj = VMath.Project(vector_a, vector_b);
		return vector_a - (vecProj * fFactor);
	}*/
	GetVectorAngles(result, result);
}

stock GetVectorReflectEx(const float angle[3], const float vecStart[3], float result[3], bool:bRejectMethod=true, float fFactor = 2.0, int flags=MASK_SOLID, TraceEntityFilter filter=INVALID_FUNCTION, any:data)
{
	float ang[3], vecNormal[3], vecPointA[3], vecPointB[3], vecDropPoint[3]
	CopyVector(ang, angle)
	TR_TraceRayFilter(vecStart, ang, flags, RayType_Infinite, filter, data);
	TR_GetEndPosition(vecDropPoint); // vecDropPoint = 目标点，法线和反射起点
	ang[1]-=0.01
	TR_TraceRayFilter(vecStart, ang, flags, RayType_Infinite, filter, data);
	TR_GetEndPosition(vecPointA);
	ang[0]-=0.01
	ang[1]+=0.01
	TR_TraceRayFilter(vecStart, ang, flags, RayType_Infinite, filter, data);
	TR_GetEndPosition(vecPointB);
	ang[0]+=0.01
	SubtractVectors(vecPointA, vecDropPoint, vecPointA);
	SubtractVectors(vecPointB, vecDropPoint, vecPointB);
	GetVectorCrossProduct(vecPointA, vecPointB, vecNormal);
	GetVectorReflect(ang, vecNormal, result, bRejectMethod, fFactor)
}

stock GetVectorReject(const float vec1[3], const float vec2[3], float result[3], bool:bMethod2D=false)
{
	float f[3]
	NormalizeVector(vec2, f);
	float l = GetVectorDotProduct(vec1, f);
	f[0] *= l
	f[1] *= l
	f[2] *= bMethod2D?0.0:l
	SubtractVectors(vec1, f, result);
}

stock GetVectorsCenter(ArrayList p, float result[3], bool b=true)
{
	result = Float:{0.0,0.0,0.0}
	int l = p.Length
	float f[3]
	for(int i=0;i<l;i++)
	{
		p.GetArray(i, f, 3)
		AddVectors(result, f, result)
	}
	ScaleVector(result, 1.0/float(l))
	if(b) p.Close()
}