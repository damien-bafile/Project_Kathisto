#include "Events.h"

void onKeyDown(unsigned char key, int x, int y)
{
	switch (key) {
	case 'w':
		cameraMoveDir.z = 1.0f;
		break;
	case 'a':
		cameraMoveDir.x = -1.0f;
		break;
	case 's':
		cameraMoveDir.z = -1.0f;
		break;
	case 'd':
		cameraMoveDir.x = 1.0f;
		break;
	case ' ':
		cameraMoveDir.y = 1.0f;
		break;
	case 'z':
		cameraMoveDir.y = -1.0f;
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
		cameraMoveDir.z = 0.0f;
		break;
	case 'a':
		cameraMoveDir.x = 0.0f;
		break;
	case 's':
		cameraMoveDir.z = 0.0f;
		break;
	case 'd':
		cameraMoveDir.x = 0.0f;
		break;
	case ' ':
		cameraMoveDir.y = 0.0f;
		break;
	case 'z':
		cameraMoveDir.y = 0.0f;
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