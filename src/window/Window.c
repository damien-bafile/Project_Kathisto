#include "Window.h"

int WINDOW_WIDTH = 750;
int WINDOW_HEIGHT = 750;

int frame = 0;
int timebase = 0;
int fps = 0;

int currTime = 0;
float prevTime = 0.0f;
float deltaTime = 0.0f;

GameObjectManager gameObjectManager;

void calculateDeltaTime()
{
	// get the current delta time (time since last frame)
	currTime = glutGet(GLUT_ELAPSED_TIME);
	deltaTime = (currTime - prevTime) / 1000.0f;
	prevTime = currTime;
}

void windowRender(void)
{

	GameObjectManager gameObectManager;

	// calculate delta time (time since last frame)
	calculateDeltaTime();

	// clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// resets transformations
	glLoadIdentity();

	// ======= GAME OBJECTS RENDER  ======= \\
	

	updateGameObjects(&gameObectManager);

	// CAMERA RENDER
	cameraRender(deltaTime);

	// GROUND RENDER
	groundRender(deltaTime);

	// RENDER EXAMPLE CUBE
	//cubeRender(deltaTime);

	// ======================================= \\


	// swap the buffers
	glutSwapBuffers();
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

void initialiseWindow(int *argc, char** argv, char* windowName)
{

	// initialise GLUT, with debug logs
	glutInit(argc, argv);
	glutInitContextFlags(GLUT_DEBUG);

	// set RGBA mode, double buffer window, and have a depth buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// set the window starting position and size
	glutInitWindowPosition(200, 200);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// set window name
	glutCreateWindow(windowName);

	// callback functions

	// on reshape
	glutReshapeFunc(reshapeWindow);

	// rendering callbacks
	glutDisplayFunc(windowRender);
	glutIdleFunc(windowRender);

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

	// SETUP GAME OBJECT MANAGER \\
	// 
	// setup game object manager
	initGameObjectManager(&gameObjectManager);

	GameObject cube;
	initGameObject(&cube);

	const Vector3 cubeVertexBuffer[] = {
		// front
		{ -1.0, 4.0,  1.0},
		{1.0, 4.0,  1.0 },
		{1.0,  6.0,  1.0},
		{-1.0,  6.0,  1.0},
		// back
		{-1.0, 4.0, -1.0},
		{ 1.0, 4.0, -1.0},
		{ 1.0,  6.0, -1.0},
		{-1.0,  6.0, -1.0}
	};

	const Vector3Int cubeIndexBuffer[] = {
		// front
		{0, 1, 2},
		{2, 3, 0},
		// right
		{1, 5, 6},
		{6, 2, 1},
		// back
		{7, 6, 5},
		{5, 4, 7},
		// left
		{4, 0, 3},
		{3, 7, 4},
		// bottom
		{4, 5, 1},
		{1, 0, 4},
		// top
		{3, 2, 6},
		{6, 7, 3}
	};

	const RGBA cubeColorBuffer[] = {
		// front colors
		{1.0, 0.0, 0.0, 1.0f},
		{0.0, 1.0, 0.0, 1.0f},
		{0.0, 0.0, 1.0, 1.0f},
		{1.0, 1.0, 1.0, 1.0f},
		// back colors
		{1.0, 0.0, 0.0, 1.0f},
		{0.0, 1.0, 0.0, 1.0f},
		{0.0, 0.0, 1.0, 1.0f},
		{1.0, 1.0, 1.0, 1.0f}
	};

	Mesh cubeMesh = { .points = cubeVertexBuffer, .indices = cubeIndexBuffer, .indexCount = 36, .colors = cubeColorBuffer, .isUniformColor = false };
	
	cube.mesh = cubeMesh;

	gameObjectManagerAdd(&gameObjectManager, cube);

	// enter loop
	glutMainLoop();
}
