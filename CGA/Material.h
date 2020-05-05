#pragma once
#include "Ray.h"
#include "Hitable.h"
class Material
{
public:
	virtual bool Scatter(const Ray& r_in, const Hit_Record& rec, Vec3& attenuation, Ray& scattered) const = 0;
};

