#pragma once

#include "RayTracer.h"
#include <cmath>
#include <iostream>

class RayTracer_CPU :
	public RayTracer
{
public:
	RayTracer_CPU(RenderTarget &target);
	virtual ~RayTracer_CPU();

	virtual void SetupScene();
	virtual void Render();

private:
	//Single color now.
	double RayCast(Vector3 &position, Vector3 &normal, SceneObject *obj, int depth);
	double max(double a, double b);

	double linearDecay = 0;
	int rayPerPixel = 200, bounceCount = 2;
};

