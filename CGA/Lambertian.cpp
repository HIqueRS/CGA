#include "Lambertian.h"

bool Lambertian::Scatter(const Ray& r_in, const Hit_Record& rec, Vec3& attenuation, Ray& scattered) const
{
	RandomTest rngt;
	Vec3 target = rec.p + rec.normal + rngt.Random_in_unit_sphere();
	scattered = Ray(rec.p, target - rec.p);
	attenuation = albedo;
	return true;
}
