stock int GetArrayMinArray(any:a[], l, ignore=0, s=0)
{
	new min, ar = -1
	for(int i = s;i < l;i++)
	{
		if(ignore &(1<<i)) continue;
		if(ar == -1 || a[i] < min) ar = i, min = a[i]
	}
	return ar;
}

stock int GetArrayMaxArray(any:a[], l, ignore=0, s=0)
{
	new max, ar = -1
	for(int i = s;i < l;i++)
	{
		if(ignore &(1<<i)) continue;
		if(ar == -1 || a[i] > max) ar = i, max = a[i]
	}
	return ar;
}
/*stock int GetArrayMinArray(any:a[], l, ignore=0, s=0)
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
}*/

/*
* @param	b	true for single only
*/
/*stock int GetArrayMaxArray(any:a[], l, bool b=false, ignore=0, s=0)
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
}*/

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

stock bool IsArrayAllSame(any []a, l)
{
	while(l--)
	{
		if(a[l] != a[0]) return false
	}
	return true
}

stock bool IsArrayZero(any []a, l)
{
	while(l--)
	{
		if(a[l] != 0) return false
	}
	return true
}