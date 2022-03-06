#include <stdlib.h>
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
Vector3 cameraDeltaPos = { 0.0f, 0.0f, 0.0f };

Vector2 mousePos = { 0.0f, 0.0f };
Vector2 mouseDeltaPos = { 0.0f, 0.0f };

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
	// get the current delta time (time since last frame)
	currTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currTime - prevTime) / 1000.0f;
	prevTime = currTime;

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
	//glColor3f(0.7f, 0.7f, 0.7f);
	//glBegin(GL_QUADS);
	//glVertex3f(-100.0f, 0.0f, -100.0f);
	//glVertex3f(-100.0f, 0.0f, 100.0f);
	//glVertex3f(100.0f, 0.0f, 100.0f);
	//glVertex3f(100.0f, 0.0f, -100.0f);
	//glEnd();


	// swap the buffers
	glutSwapBuffers();
}

// Called when the window gets resized
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
		cameraDeltaPos.z = 1.0f;
		break;
	case 'a':
		cameraDeltaPos.x = -1.0f;
		break;
	case 's':
		cameraDeltaPos.z = -1.0f;
		break;
	case 'd':
		cameraDeltaPos.x = 1.0f;
		break;
	case ' ':
		cameraDeltaPos.y = 1.0f;
		break;
	case 'z':
		cameraDeltaPos.y = -1.0f;
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
		cameraDeltaPos.z = 0.0f;
		break;
	case 'a':
		cameraDeltaPos.x = 0.0f;
		break;
	case 's':
		cameraDeltaPos.z = 0.0f;
		break;
	case 'd':
		cameraDeltaPos.x = 0.0f;
		break;
	case ' ':
		cameraDeltaPos.y = 0.0f;
		break;
	case 'z':
		cameraDeltaPos.y = 0.0f;
		break;
	}
}

void onSpecialKeyDown(int key, int x, int y)
{
}

void onSpecialKeyUp(int key, int x, int y)
{
}

void onMouseButton(int button, int state, int xx, int yy)
{
}

void onMouseMove(int x, int y)
{
	glutWarpPointer(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2);

	// update mouse deltas
	mouseDeltaPos.x = (x - (WINDOW_WIDTH / 2)) * MOUSE_SENS;
	mouseDeltaPos.y = (y - (WINDOW_WIDTH / 2)) * MOUSE_SENS;

	// update camera's direction
	cameraForwardDir.x = sin(mousePos.x + mouseDeltaPos.x);
	cameraForwardDir.y = -tan(mousePos.y + mouseDeltaPos.y);
	cameraForwardDir.z = -cos(mousePos.x + mouseDeltaPos.x);

	mousePos.x += mouseDeltaPos.x;
	mousePos.y += mouseDeltaPos.y;

}