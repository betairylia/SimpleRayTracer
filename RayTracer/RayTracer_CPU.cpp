#include "RayTracer_CPU.h"

RayTracer_CPU::RayTracer_CPU(RenderTarget &target) : RayTracer(target)
{
}

RayTracer_CPU::~RayTracer_CPU()
{
}

void RayTracer_CPU::SetupScene()
{
	for (int i = 0; i < 100; i++)
	{
		scene.push_back(new Sphere(Vector3(
			-6 + 12 * (double)(rand() % 10000) / 10000.0,
			-4 + 8 * (double)(rand() % 10000) / 10000.0,
			8 + 8 * (double)(rand() % 10000) / 10000.0
			), 0.7));
	}

	sceneLight.push_back(new Light(Vector3(0, 0, 12), 1));
	//sceneLight.push_back(new Light(Vector3(-3, 1, 13), 0.4));
}

void RayTracer_CPU::Render()
{
	//TODO: camera moveable
	vector<SceneObject*>::iterator iter;

	for (int i = 0; i < screenWidth; i++)
	{
		for (int j = 0; j < screenHeight; j++)
		{
			double targetValue = 0;
			for (int count = 0; count < rayPerPixel; count++)
			{
				//get the ray corresponding the screen position (i, j)
				Ray pixelRay(Vector3(0, 0, 0), Vector3(
					((double)i / (double)screenWidth)  * 1.0f - 0.5f,
					((double)j / (double)screenHeight) * 0.5625f - 0.28125f,
					sqrt(3.0f) / 2.0f).Normalized());

				//SetTarget(i, j, RayCast(pixelRay, 0));

				RayCastResult result;
				result.distance = 9999999;
				SceneObject *intersectObject;

				for (iter = scene.begin(); iter != scene.end(); iter++)
				{
					RayCastResult tmp;
					if ((*iter)->RayCast(pixelRay, tmp))
					{
						if (tmp.distance < result.distance)
						{
							result = tmp;
							intersectObject = (*iter);
						}
					}
				}

				//No intersections
				if (result.distance == 9999999)
				{
					targetValue = rayPerPixel * 0.1f;
					break;
				}
				//Has intersections
				else
				{
					targetValue += RayCast(result.position, result.normal, intersectObject, 0);
				}
			}
			SetTarget(i, j, targetValue / (double)rayPerPixel);
		}
	}

	cout << "Render finished." << endl;
}

double RayTracer_CPU::RayCast(Vector3 &position, Vector3 &normal, SceneObject *obj, int depth)
{
	//Bounce limit
	if (depth >= bounceCount)
	{
		return 0;
	}

	position = position + (normal * 0.01);

	double resultLight = 0;

	vector<SceneObject*>::iterator iter;
	vector<Light*>::iterator iter_light;

	//TODO: fixed Material now.
	//find lights
	for (iter_light = sceneLight.begin(); iter_light != sceneLight.end(); iter_light++)
	{
		RayCastResult result;
		result.distance = 9999999;
		SceneObject *intersectObject;

		Ray lightRay(position, ((*iter_light)->position - position).Normalized());

		//intersection
		for (iter = scene.begin(); iter != scene.end(); iter++)
		{
			RayCastResult tmp;
			if ((*iter)->RayCast(lightRay, tmp))
			{
				if (tmp.distance < result.distance)
				{
					result = tmp;
					intersectObject = (*iter);
				}
			}
		}

		//Face to light without other things.
		double distToLight = ((*iter_light)->position - position).Magnitude();
		if (result.distance >= distToLight)
		{
			double illumination = max(0, (*iter_light)->lightPower);
			resultLight += max(0, 
				0.75f * //FIXED MATERIAL PARAMETER
				illumination * normal.DotProduct(((*iter_light)->position - position).Normalized()) + 0.25f);
		}
		//Need further computation.
		//else
		//{
		//	if ((result.position - position).Magnitude() <= 1e-05)
		//	{
		//		//It is yourself.
		//		resultLight += 0;
		//	}
		//	else
		//	{
		//		double illumination = max(0, RayCast(result.position, result.normal, intersectObject, depth + 1));
		//		resultLight += max(0,
		//			0.9f * //FIXED MATERIAL PARAMETER
		//			illumination * normal.DotProduct((result.position - position).Normalized()));
		//	}
		//}
	}

	//Diffuse, Monte-Carlo Ray Tracing
	Ray diffuseRay(position, Vector3::random());
	
	//intersection
	RayCastResult result;
	result.distance = 9999999;
	SceneObject *intersectObject;
	for (iter = scene.begin(); iter != scene.end(); iter++)
	{
		RayCastResult tmp;
		if ((*iter)->RayCast(diffuseRay, tmp))
		{
			if (tmp.distance < result.distance)
			{
				result = tmp;
				intersectObject = (*iter);
			}
		}
	}

	if (result.distance < 9999999)
	{
		double illuminationIndirect = max(0, RayCast(result.position, result.normal, intersectObject, depth+1));
		resultLight += max(0,
			0.75f * //FIXED MATERIAL PARAMETER
			illuminationIndirect * normal.DotProduct((result.position - position).Normalized()) + 0.25f);
	}

	return resultLight;
}

double RayTracer_CPU::max(double a, double b)
{
	return a > b ? a : b;
}
