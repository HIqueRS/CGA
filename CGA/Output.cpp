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
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			Vec3 col(float(i) / float(nx), float(j) / float(ny), 0.2);
			
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			std::cout << ir << " " << ig << " " << ib << "\n";
			outFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outFile.close();
}