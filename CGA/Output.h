#pragma once
#include <iostream>
#include <fstream>
#include "Vec3.h"
#include "Ray.h"
class Output
{
public:
	void execute();
	
protected:
	void OutputImage();
	Vec3 Color(const Ray& r);
	bool Hit_Sphere(const Vec3& center, float radius, const Ray& r);

	std::ofstream outFile;

};

