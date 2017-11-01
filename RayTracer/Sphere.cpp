#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

bool Sphere::RayCast(const Ray &ray, RayCastResult &result)
{
	Vector3 origin_center = centerPos - ray.origin;
	double proj_origin_center = origin_center.DotProduct(ray.dirc);

	//no intersection
	if (proj_origin_center < 0)
	{
		return false;
	}

	double origin_center_square = origin_center.DotProduct(origin_center);
	
	//distance from ray to sphere (squared)
	double dist_square = origin_center_square - proj_origin_center * proj_origin_center;

	//no intersection
	if (dist_square >= (radius * radius))
	{
		return false;
	}

	//distance between intersection points (half).
	//squared now.
	double dist_point = radius * radius - dist_square;
	if (dist_point < 1e-05)
	{
		result.distance = proj_origin_center;
	}
	else
	{
		dist_point = sqrt(dist_point);

		//only the nearest one was needed.
		result.distance = proj_origin_center - dist_point;
	}

	//calculate normal
	result.position = ray.dirc.Normalized() * result.distance + ray.origin;
	result.normal = (result.position - centerPos).Normalized();

	return true;
}
	