#pragma once
#define _CRT_RAND_S 
#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
#include "Hitable_List.h"
#include <float.h>
#include <cfloat>
#include "Sphere.h"
#include "Camera.h"
#include <random>
#include <stdlib.h>
#include <stdio.h>  
#include <limits.h>
#include "RandomTest.h"
#include "Material.h"
#include "Metal.h"
#include "Dielectric.h"
class Output
{
public:
	void execute();

protected:
	void OutputImage();
	Vec3 Color(const Ray& r, Hitable* world, int depth);
	float Hit_Sphere(const Vec3& center, float radius, const Ray& r);
	Hitable_List* Random_scene();
	//float Randinho();
	//Vec3 Random_in_unit_sphere();

	std::ofstream outFile;
	unsigned int rng;
	RandomTest rndt;
};

