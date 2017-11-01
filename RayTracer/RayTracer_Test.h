#pragma once
#include "RayTracer.h"

#include <iostream>

class RayTracer_Test :
	public RayTracer
{
public:
	RayTracer_Test(RenderTarget &target);
	virtual ~RayTracer_Test();

	virtual void SetupScene();
	virtual void Render();
};

