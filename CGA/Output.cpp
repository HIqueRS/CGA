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

	Hitable* list[4];
	//float r = cos(M_PI / 4);
	//list[0] = new Sphere(Vec3(-r, 0, -1), r, new Lambertian(Vec3(0, 0, 1)));
	//list[1] = new Sphere(Vec3(r, 0, -1), r, new Lambertian(Vec3(1, 0, 0)));


	//Lambertian a = Lambertian(Vec3(0.8, 0.3, 0.3));
	list[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.8, 0.3, 0.3)));

	////Lambertian b = new Lambertian(Vec3(0.8, 0.8, 0.0));
	list[1] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertian(Vec3(0.8, 0.8, 0.0)));

	list[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2),0.3));

	list[3] = new Sphere(Vec3(-1, 0, -1), -0.45, new Dielectric(1.5));




	Vec3 lookfrom(3, 3, 2);
	Vec3 lookat(0, 0, -1);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 2.0;

	//Camera cam(lookfrom, lookat, Vec3(0, 1, 0), 20, float(nx) / float(ny), aperture, dist_to_focus);
	//Camera cam(90,float(nx)/float(ny));
	Camera cam(Vec3(-2,2,1),Vec3(0,0,-1),Vec3(0,1,0),20,float(nx)/float(ny));

	Hitable_List* world = new Hitable_List(list, 4);
	//Hitable_List* world = Random_scene();
	//Hitable* blep = Random_scene();
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

Hitable_List* Output::Random_scene()
{
	int n = 500;//500;
	Hitable** list = new Hitable*[n+1];
	list[0] = new Sphere(Vec3(0, -1000, 0), 1000, new Lambertian(Vec3(0.5, 0.5, 0.5)));
	RandomTest rngt2;
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float chose_mat = rngt2.Randinho();
			Vec3 center(a + 0.9 * rngt2.Randinho(), 0.2, b + 0.9 * rngt2.Randinho());
			if ((center - Vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (chose_mat < 0.8)
				{
					list[i++] = new Sphere(center, 0.2, new Lambertian(Vec3(rngt2.Randinho() * rngt2.Randinho(), rngt2.Randinho() * rngt2.Randinho(), rngt2.Randinho() * rngt2.Randinho())));
				}
				else if (chose_mat < 0.95)
				{
					list[i++] = new Sphere(center, 0.2,
						new Metal(Vec3(0.5 * (1 + rngt2.Randinho()), 0.5 * (1 + rngt2.Randinho()), 0.5 * (1 + rngt2.Randinho())), 0.5 * rngt2.Randinho()));
				}
				else
				{
					list[i++] = new Sphere(center, 0.2, new Dielectric(1.5));
				}
			}
		}
	}

	list[i++] = new Sphere(Vec3(0, 1, 0), 1.0, new Dielectric(1.5));
	list[i++] = new Sphere(Vec3(-4, 1, 0), 1.0, new Lambertian(Vec3(0.4, 0.2, 0.1)));
	list[i++] = new Sphere(Vec3(4, 1, 0), 1.0, new Metal(Vec3(0.7, 0.6, 0.5),0.0));
	

	return new Hitable_List(list,i);
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

