#pragma once
#include "Material.h"
#include "RandomTest.h"
class Dielectric : public Material
{
public:
	Dielectric(float ri): ref_idx(ri){}
	virtual bool Scatter(const Ray& r_in, const Hit_Record& rec, Vec3& attenuation, Ray& scattered) const;

	float ref_idx;
};

