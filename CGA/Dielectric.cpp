#include "Dielectric.h"

bool Dielectric::Scatter(const Ray& r_in, const Hit_Record& rec, Vec3& attenuation, Ray& scattered) const
{
	Vec3 outward_normal;
	Vec3 reflected = Reflect(r_in.Direction(), rec.normal);
	float ni_over_nt;
	attenuation = Vec3(1.0, 1.0, 1.0);
	Vec3 refracted;
	float reflect_prob;
	float cosine;
	RandomTest rngt;

	if (dot(r_in.Direction(), rec.normal) > 0)
	{
		outward_normal = -rec.normal;
		ni_over_nt = ref_idx;
		cosine = ref_idx * dot(r_in.Direction(), rec.normal) / r_in.Direction().length();
	}
	else
	{
		outward_normal = rec.normal;
		ni_over_nt = 1.0 / ref_idx;
		cosine = -dot(r_in.Direction(), rec.normal) / r_in.Direction().length();
	}
	if (Refract(r_in.Direction(), outward_normal, ni_over_nt, refracted))
	{
		reflect_prob = schlick(cosine, ref_idx);
		//scattered = Ray(rec.p, refracted);
	}
	else
	{
		scattered = Ray(rec.p, refracted);
		reflect_prob = 1.0;
	}
	if (rngt.Randinho() < reflect_prob)
	{
		scattered = Ray(rec.p, reflected);
	}
	else
	{
		scattered = Ray(rec.p, refracted);
	}

	return true;
}
