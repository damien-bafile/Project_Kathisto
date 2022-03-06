#include "Window.h"

int WINDOW_WIDTH = 750;
int WINDOW_HEIGHT = 750;

int frame = 0;
int timebase = 0;
int fps = 0;

int currTime = 0;
float prevTime = 0.0f;
float deltaTime = 0.0f;

void windowRender(void)
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