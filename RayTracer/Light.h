#pragma once

#include "Vector3.h"

class Light
{
public:
	Light(Vector3 pos, double lp);
	virtual ~Light();

	//Only point light (Linear decay in ray tracer) ONLY now.
	Vector3 position;
	double lightPower;
};

