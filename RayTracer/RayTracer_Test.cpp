#include "RayTracer_Test.h"

RayTracer_Test::RayTracer_Test(RenderTarget &target) : RayTracer(target)
{
}

RayTracer_Test::~RayTracer_Test()
{
}

void RayTracer_Test::SetupScene()
{
}

void RayTracer_Test::Render()
{
	int i = 0, j = 0, c = 0;
	while (true)
	{
		c++;
		std::cout << c << std::endl;
		for (i = 0; i < screenWidth; i++)
		{
			for (j = 0; j < screenHeight; j++)
			{
				m_target.screenPixels[i][j][0] = 0.5f + 0.5f * sin(0.163 + 0.00177f * (double)(i + j * 1 + 100 * c));
				m_target.screenPixels[i][j][1] = 0.5f + 0.5f * sin(0.372 + 0.00677f * (double)(i + j * 2 + 100 * c));
				m_target.screenPixels[i][j][2] = 0.5f + 0.5f * sin(0.875 + 0.01877f * (double)(i + j * 3 + 100 * c));
			}
		}
	}
}
