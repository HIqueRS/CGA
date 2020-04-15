#pragma once
#include <iostream>
#include <fstream>
class Output
{
public:
	void execute();
	
protected:
	void OutputImage();

	std::ofstream outFile;

};

