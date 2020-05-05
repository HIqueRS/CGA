#include "Output.h"

void Output::execute()
{
	OutputImage();
}

void Output::OutputImage()
{
	int nx = 200;
	int ny = 100;
	int ns = 100;
	outFile.open("test.ppm");
	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	outFile << "P3\n" << nx << " " << ny << "\n255\n";	

	Hitable* list[2];

	Lambertian a = Lambertian(Vec3(0.8, 0.3, 0.3));
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.8, 0.3, 0.3)));

	//Lambertian b = new Lambertian(Vec3(0.8, 0.8, 0.0));
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertian(Vec3(0.8, 0.8, 0.0)));


	Hitable_List* world = new Hitable_List(list, 2);
	Camera cam;

	//Hitable_List a;

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				
				float u = float(i+ rndt.Randinho() ) / float(nx);
				float v = float(j + rndt.Randinho()) / float(ny);
				Ray r = cam.Get_ray(u,v);
				Vec3 p = r.Point_At_Parameter(2.0);
				col += Color(r,world,0);

			}
			col /= float(ns);
			col = Vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			//std::cout << Randinho() <<std::endl;
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

Vec3 Output::Color(const Ray& r,Hitable *world, int depth)
{
	Hit_Record rec;
	if (world->Hit(r, 0.001, FLT_MAX, rec))
	{
		Ray scattered;
		Vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->Scatter(r, rec, attenuation, scattered))
		{
			return attenuation * Color(scattered, world, depth + 1);
		}
		else
		{
			return Vec3(0.0, 0.0, 0.0);
		}
		
	}
	else
	{
		Vec3 unit_direction = unit_vector(r.Direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return(1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0);
	}

	
}