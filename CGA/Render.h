#pragma once
#include "RayCastRender.h"
#include "RayTracingRender.h"
class Render
{
public:
	void execute();
protected:
	RayCastRender cast;
	RayTracingRender trace;
};

