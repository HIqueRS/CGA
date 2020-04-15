#pragma once
#include <iostream>
#include <fstream>
#include "Vec3.h"
class Output
{
public:
	void execute();
	
protected:
	void OutputImage();

	std::ofstream outFile;

};

