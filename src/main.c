﻿#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "math/Vector.h"


int WINDOW_WIDTH = 750;
int WINDOW_HEIGHT = 750;

const float MOUSE_SENS = 0.001f;
const float WALK_SPEED = 15.0f;
const float UP_SPEED = 10.0f;


Vector3 cameraForwardDir = { 0.0f, 0.0f, -1.0f };
Vector3 cameraPos = { 0.0f, 1.0f, 5.0f };
Vector3 cameraUp = { 0.0f, 1.0f, 0.0f };
Vector3 moveDir = { 0.0f, 0.0f, 0.0f };

Vector2 mousePos = { 0.0f, 0.0f };
Vector2 mouseDeltaPos = { 0.0f, 0.0f };

int frame = 0;
int timebase = 0;
int fps = 0;

int currTime = 0;
float prevTime = 0.0f;
float deltaTime = 0.0f;

void reshapeWindow(int width, int height); // called when window gets resized
void calculateDeltaTime(); // calculate the delta time
void render(void); // called every frame

void onKeyDown(unsigned char key, int x, int y); // on key down
void onKeyUp(unsigned char key, int x, int y); // on key up

void onSpecialKeyDown(int key, int x, int y); // on special key up
void onSpecialKeyUp(int key, int x, int y); // on special key up

void onMouseButton(int button, int state, int x, int y); // on mouse buttons
void onMouseMove(int x, int y); // on mouse move

void computeCameraPos(); // compute the position of the camera

int main(int argc, char** argv)
{
	// initialise GLUT, with debug logs
	glutInit(&argc, argv);
	glutInitContextFlags(GLUT_DEBUG);

	// set RGBA mode, double buffer window, and have a depth buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// set the window starting position and size
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// set window name
	glutCreateWindow("Project Kathisto");

	// callback functions

	// on reshape
	glutReshapeFunc(reshapeWindow);

	// rendering callbacks
	glutDisplayFunc(render);
	glutIdleFunc(render);

	// keyboard and mouse input
	glutKeyboardFunc(onKeyDown); // on key down
	glutKeyboardUpFunc(onKeyUp); // on key up

	glutSpecialFunc(onSpecialKeyDown); // on special key down (function keys, ctrl etc)
	glutSpecialUpFunc(onSpecialKeyUp); // on special key up

	glutIgnoreKeyRepeat(1); // ignore auto repeat keystrokes so it doesnt constantly fire key up and key down

	glutMouseFunc(onMouseButton); // on mouse click
	glutPassiveMotionFunc(onMouseMove); // ALWAYS MOVING

	// hide the cursor
	glutSetCursor(GLUT_CURSOR_NONE);

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// enter loop
	glutMainLoop();

	return 1;
}

void render(void)
{
	// calculate delta time (time since last frame)
	calculateDeltaTime();

	// compute the cameras position you can move
	computeCameraPos();

	// clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// resets transformations
	glLoadIdentity();

	// Cam Position and rotation
	gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
		cameraPos.x + cameraForwardDir.x, cameraPos.y + cameraForwardDir.y, cameraPos.z + cameraForwardDir.z,
		cameraUp.x, cameraUp.y, cameraUp.z);


	// draw a basic purple triangle
	glColor3f(0.6f, 0.25f, 0.65f);
	glBegin(GL_TRIANGLES); // set mode to drawing in triangles
	glVertex3f(1.0f, 1.0f, 1.0f); // point 1
	glVertex3f(1.0f, 0.0f, 1.0f); // point 2
	glVertex3f(0.0f, 1.0f, 1.0f); // point 3
	glEnd();

	//Draw ground
	glColor3f(0.7f, 0.7f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-100.0f, 0.0f, -100.0f);
	glVertex3f(-100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, 100.0f);
	glVertex3f(100.0f, 0.0f, -100.0f);
	glEnd();


	// swap the buffers
	glutSwapBuffers();
}

void calculateDeltaTime()
{
	// get the current delta time (time since last frame)
	currTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currTime - prevTime) / 1000.0f;
	prevTime = currTime;
}

void reshapeWindow(int width, int height)
{
	// if height is 0 then set it 1
	if (height == 0) height = 1;

	// set the window width and height
	WINDOW_WIDTH = width;
	WINDOW_HEIGHT = height;

	// get the width:height ratio
	float ratio = width * 1.0f / height;

	// set the matrix to projection
	glMatrixMode(GL_PROJECTION);

	// reset transformations
	glLoadIdentity();

	// set the viewports width and height
	glViewport(0, 0, width, height);

	// set the perspective for the projection matrix
	// fov, aspect ratio, near clipping distance, far clipping distance
	gluPerspective(45, ratio, 1, 500);

	// set the matrix mode back to model view
	glMatrixMode(GL_MODELVIEW);
}

void onKeyDown(unsigned char key, int x, int y)
{

	switch (key) {
	case 'w':
		moveDir.z = 1.0f;
		break;
	case 'a':
		moveDir.x = -1.0f;
		break;
	case 's':
		moveDir.z = -1.0f;
		break;
	case 'd':
		moveDir.x = 1.0f;
		break;
	case ' ':
		moveDir.y = 1.0f;
		break;
	case 'z':
		moveDir.y = -1.0f;
		break;
	case 27:
		exit(0);
		break;
	}
}

void onKeyUp(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		moveDir.z = 0.0f;
		break;
	case 'a':
		moveDir.x = 0.0f;
		break;
	case 's':
		moveDir.z = 0.0f;
		break;
	case 'd':
		moveDir.x = 0.0f;
		break;
	case ' ':
		moveDir.y = 0.0f;
		break;
	case 'z':
		moveDir.y = 0.0f;
		break;
	}
}

void onSpecialKeyDown(int key, int x, int y)
{
}

void onSpecialKeyUp(int key, int x, int y)
{
}

void onMouseButton(int button, int state, int x, int y)
{
}

void onMouseMove(int x, int y)
{
	glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2);

	// update mouse deltas
	mouseDeltaPos.x = (x - (WINDOW_WIDTH / 2)) * MOUSE_SENS;
	mouseDeltaPos.y = (y - (WINDOW_WIDTH / 2)) * MOUSE_SENS;

	// update camera's direction
	cameraForwardDir.x = sin(mousePos.x + mouseDeltaPos.x);  // left/right
	cameraForwardDir.y = -tan(mousePos.y + mouseDeltaPos.y); // up/down
	cameraForwardDir.z = -cos(mousePos.x + mouseDeltaPos.x); // forward/back

	// increase the mouse pos by the delta mouse pos
	mousePos.x += mouseDeltaPos.x;
	mousePos.y += mouseDeltaPos.y;

}

void computeCameraPos()
{
	// REMEMBER: multiplying by delta time helps create smooth movement

	// calculate the forward/back position
	// new pos = the cams forward dir * (the forward move direction * walk speed)
	Vector3 newPos = Vec3ScalarMultiply(cameraForwardDir, moveDir.z * (WALK_SPEED * deltaTime));
	// change camera's position
	cameraPos.x += newPos.x;
	cameraPos.y += newPos.y;
	cameraPos.z += newPos.z;

	// calculate the left/right position
	// a normalised vectors values are between 0 and 1.
	// a cross product of 2 vectors is a perpendicular vector
	// new pos = normalised (cross product of cameraForward pos and Camera Up) * the move left move direction * walk speed)
	newPos = Vec3ScalarMultiply(Vec3Normalize(Vec3CrossProduct(cameraForwardDir, cameraUp)), moveDir.x * (WALK_SPEED * deltaTime));
	cameraPos.x += newPos.x;
	cameraPos.y += newPos.y;
	cameraPos.z += newPos.z;

	// calculate the up/down position
	cameraPos.y += moveDir.y * (UP_SPEED * deltaTime);

}