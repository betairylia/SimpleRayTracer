#include <GL\freeglut.h>
#include <cstdio>
#include <thread>

#include "RayTracer.h"
#include "RayTracer_CPU.h"
#include "RayTracer_Test.h"

RenderTarget target;

const int refreshGap = 500;//(ms)

void Reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	/* the curve */
	glPushMatrix();

	glBegin(GL_POINTS);
	for (int i = 0; i < screenWidth; i++)
	{
		for (int j = 0; j < screenHeight; j++)
		{
			glColor3f(target.screenPixels[i][j][0], target.screenPixels[i][j][1], target.screenPixels[i][j][2]);
			glVertex2i(i, j);
		}
	}
	glEnd();

	glPopMatrix();
	
	glFlush();
}

void Idle(int t)
{
	glutPostRedisplay();
	glutTimerFunc(refreshGap, Idle, 0);
}

void InitTracer()
{
	RayTracer *tracer;
	tracer = new RayTracer_CPU(target);
	
	tracer -> SetupScene();
	tracer -> Render();
}

int main(int argc, char *argv[])
{
	srand(time(0));

	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(400, 200);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInit(&argc, argv);

	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	std::thread tracerThread(InitTracer);

	glutCreateWindow("rayTracer");

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glutReshapeFunc(Reshape);
	glutDisplayFunc(Display);

	glutTimerFunc(refreshGap, Idle, 0);

#ifdef WIN32
#endif

	while (true)
		glutMainLoopEvent();

	tracerThread.join();

	printf("Back from the 'freeglut' main loop\n");

	return 0;             /* ANSI C requires main to return int. */
}
