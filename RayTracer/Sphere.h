#pragma once
#include "SceneObject.h"
class Sphere :
	public SceneObject
{
public:
	Sphere();
	Sphere(Vector3 c, double r) : centerPos(c), radius(r) {}
	virtual ~Sphere();

	Vector3 centerPos;
	double radius;

	virtual bool RayCast(const Ray &ray, RayCastResult &result);
};

