#pragma once

#include "Vector3.h"

typedef struct _rayCastResult
{
	double distance;
	Vector3 normal, position;
}RayCastResult;

class Ray
{
public:
	Ray(Vector3 o, Vector3 d) : origin(o), dirc(d) {}
	~Ray();

	Vector3 origin, dirc;
};

