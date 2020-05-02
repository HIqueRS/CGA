#pragma once
#include "Hitable.h"
class Sphere: public Hitable
{
public:
	Sphere(){}
	Sphere(Vec3 cen, float r) : center(cen), radius(r) {};
    bool Hit(const Ray& r, float t_min, float t_max, Hit_Record& rec) const;

	Vec3 center;
	float radius;
};


