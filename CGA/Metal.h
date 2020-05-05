#pragma once
#include "Material.h"
#include "RandomTest.h"
class Metal : public Material
{
public:
	Metal(const Vec3& a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }
	virtual bool Scatter(const Ray& r_in, const Hit_Record& rec, Vec3& attenuation, Ray& scattered) const
	{
		RandomTest RNGT;
		Vec3 reflected = Reflect(unit_vector(r_in.Direction()), rec.normal);
		scattered = Ray(rec.p, reflected + fuzz*RNGT.Random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.Direction(), rec.normal) > 0);
	}

	Vec3 albedo;
	float fuzz;
};

