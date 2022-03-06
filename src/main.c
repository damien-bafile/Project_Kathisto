#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "math/Vector.h"


int WINDOW_WIDTH = 750;
int WINDOW_HEIGHT = 750;

Vector3 cameraForwardDir = { 0.0f, 0.0f, -1.0f };
Vector3 cameraPos = { 0.0f, 1.0f, 5.0f };
Vector3 cameraUp = { 0.0f, 1.0f, 0.0f };
Vector3 cameraDeltaPos = { 0.0f, 0.0f, 0.0f };

int frame = 0;
int timebase = 0;
int fps = 0;

int currTime = 0;
float prevTime = 0.0f;
float deltaTime = 0.0f;

void reshapeWindow(int width, int height);
void render(void);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitContextFlags(GLUT_DEBUG);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Project Kathisto");

	glutReshapeFunc(reshapeWindow);

	glutDisplayFunc(render);
	glutIdleFunc(render);

	glEnable(GL_DEPTH_TEST);

	glutMainLoop();

	return 1;
}

void render(void)
{

	//frame++;
	currTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currTime - prevTime) / 1000.0f;
	prevTime = currTime;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// resets transformations
	glLoadIdentity();

	// Cam Position and rotation
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
		cameraPos.x + cameraForwardDir.x, cameraPos.y + cameraForwardDir.y, cameraPos.z + cameraForwardDir.z,
		cameraUp.x, cameraUp.y, cameraUp.z);


	glColor3f(0.6f, 0.25f, 0.65f);
	glBegin(GL_TRIANGLES);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 1.0f, 1.0f);
	
	//Draw ground
	//glColor3f(0.7f, 0.7f, 0.7f);
	//glBegin(GL_QUADS);
	//glVertex3f(-100.0f, 0.0f, -100.0f);
	//glVertex3f(-100.0f, 0.0f, 100.0f);
	//glVertex3f(100.0f, 0.0f, 100.0f);
	//glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();


	glutSwapBuffers();
}


void reshapeWindow(int width, int height)
{
	if (height == 0) height = 1;

	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;

	float ratio = width * 1.0f / height;


	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glViewport(0, 0, width, height);

	gluPerspective(45, ratio, 1, 100);

	glMatrixMode(GL_MODELVIEW);
}