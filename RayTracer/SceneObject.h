#pragma once

#include "Ray.h"
#include "Material.h"

class SceneObject
{
public:
	SceneObject();
	virtual ~SceneObject();

	virtual bool RayCast(const Ray &ray, RayCastResult &result) = 0;

	Material material;
};

