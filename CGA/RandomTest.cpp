#include "RandomTest.h"

float RandomTest::Randinho()
{
	rand_s(&rng);

	return (double)rng /((double)UINT_MAX + 1) * 1 ;
}

Vec3 RandomTest::Random_in_unit_sphere()
{
	Vec3 p;
	do {
		p = 2.0 * Vec3(Randinho(), Randinho(), Randinho()) - Vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}
