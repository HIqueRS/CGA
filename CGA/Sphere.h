#pragma once
#include "Hitable.h"
#include "Lambertian.h"
class Sphere: public Hitable
{
public:
	Sphere() {};
	Sphere(Vec3 cen, float r, Material* m) : center(cen), radius(r), mat(m) {};
    bool Hit(const Ray& r, float t_min, float t_max, Hit_Record& rec) const;

	Vec3 center;
	float radius;
	Material* mat;
};



