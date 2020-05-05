#pragma once
#define _CRT_RAND_S  

#include <stdlib.h>  
#include <stdio.h>  
#include <limits.h>
#include "Vec3.h"
class RandomTest
{
public:
	unsigned int rng;
	float Randinho();
	Vec3 Random_in_unit_sphere();

};

//inline float Randinho()
//{
//	unsigned int rng;
//	rand_s(&rng);
//
//	return (double)rng / ((double)UINT_MAX + 1) * 1;
//}
//
//inline Vec3 Randon_in_unit_sphere()
//{
//	Vec3 p;
//	do {
//		p = 2.0 * Vec3(Randinho(), Randinho(), Randinho()) - Vec3(1, 1, 1);
//	} while (p.squared_length() >= 1.0);
//	return p;
//}