#pragma once
#include "Material.h"
#include "Vec3.h"
#include "Ray.h"
#include "RandomTest.h"

class Lambertian : public Material
{
public:
	Lambertian() {};
		Lambertian(const Vec3& a) : albedo(a){}
		virtual bool Scatter(const Ray& r_in, const Hit_Record& rec, Vec3& attenuation, Ray& scattered)const;

		Vec3 albedo;		

};
