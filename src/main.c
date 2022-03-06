#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "window/Window.h"


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
	windowRender();
}
