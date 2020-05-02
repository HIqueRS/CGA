#pragma once
#include "Ray.h"

struct  Hit_Record
{
	float t;
	Vec3 p;
	Vec3 normal;
};

class Hitable
{
public:
	virtual bool Hit(const Ray& r, float t_min, float t_max, Hit_Record& rec) const = 0;
};
