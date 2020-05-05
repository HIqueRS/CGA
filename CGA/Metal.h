#pragma once
#include "Material.h"
class Metal : public Material
{
public:
	Metal(const Vec3& a) : albedo(a){}
	virtual bool Scatter(const Ray& r_in, const Hit_Record& rec, Vec3& attenuation, Ray& scattered) const
	{
		Vec3 reflected = Reflect(unit_vector(r_in.Direction()), rec.normal);
		scattered = Ray(rec.p, reflected);
		attenuation = albedo;
		return (dot(scattered.Direction(), rec.normal) > 0);
	}

	Vec3 albedo;
};

