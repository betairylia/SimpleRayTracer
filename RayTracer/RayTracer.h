#pragma once

#include "SceneObject.h"
#include "Sphere.h"

#include "Light.h"

#include <vector>

using namespace std;

const int screenWidth = 1280, screenHeight = 720;

typedef struct _screen
{
	double screenPixels[screenWidth][screenHeight][3];
}RenderTarget;

class RayTracer
{
public:
	RenderTarget &m_target;

	vector<SceneObject*> scene;
	vector<Light*> sceneLight;

	RayTracer(RenderTarget &target);
	virtual ~RayTracer();
	virtual void SetupScene() = 0;
	virtual void Render() = 0;

	void SetTarget(int x, int y, double value)
	{
		m_target.screenPixels[x][y][0] = value;
		m_target.screenPixels[x][y][1] = value;
		m_target.screenPixels[x][y][2] = value;
	}

	void SetTarget(int x, int y, double r, double g, double b)
	{
		m_target.screenPixels[x][y][0] = r;
		m_target.screenPixels[x][y][1] = g;
		m_target.screenPixels[x][y][2] = b;
	}
};

