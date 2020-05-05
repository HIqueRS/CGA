#include "Sphere.h"
bool Sphere::Hit(const Ray& r, float t_min, float t_max, Hit_Record& rec)const
{
	Vec3 oc = r.Origin() - center;
	float a = dot(r.Direction(), r.Direction());
	float b = dot(oc, r.Direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - a * c;
	Material* x = mat;
	if (discriminant > 0)
	{
		float temp = (-b - sqrt(b * b - a * c)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.Point_At_Parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = x;
			return true;
		}
		temp = (-b + sqrt(b * b - a * c)) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.Point_At_Parameter(rec.t);
			rec.normal = (rec.p - center) / radius;
			rec.mat_ptr = x;
			return true;
		}
	}
	return false;
}
