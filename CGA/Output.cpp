#include "Output.h"

void Output::execute()
{
	OutputImage();
}

void Output::OutputImage()
{
	int nx = 200;
	int ny = 100;
	outFile.open("test.ppm");
	std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	outFile << "P3\n" << nx << " " << ny << "\n255\n";
	Vec3 lower_left_corner(-2.0, -1.0, -1.0);
	Vec3 horizontal(4.0, 0.0, 0.0);
	Vec3 vertical(0.0, 2.0, 0.0);
	Vec3 origin(0.0, 0.0, 0.0);

	Hitable* list[2];
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5);
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100);
	Hitable_List* world = new Hitable_List(list, 2);

	//Hitable_List a;

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			Ray r(origin, lower_left_corner + u * horizontal + v * vertical);
			Vec3 col = Color(r,world);
			
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
			outFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outFile.close();
}




float Output::Hit_Sphere(const Vec3& center, float radius, const Ray& r)
{
	Vec3 oc = r.Origin() - center;
	float a = dot(r.Direction(), r.Direction());
	float b = 2.0 * dot(oc, r.Direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	
	if (discriminant < 0) 
	{
		return -1.0;
	}
	else
	{
		float test = sqrt(discriminant);
		return (-b - test) / (2.0 * a);
	}	
}

Vec3 Output::Color(const Ray& r,Hitable *world)
{
	Hit_Record rec;
	if (world->Hit(r, 0.0, FLT_MAX, rec))
	{
		return 0.5 * Vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else
	{
		Vec3 unit_direction = unit_vector(r.Direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return(1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}

	
}