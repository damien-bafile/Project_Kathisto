#include "Window.h"


#include "math/mathUtils.h"

int WINDOW_WIDTH = 1280;
int WINDOW_HEIGHT = 750;

int frame = 0;
int timebase = 0;
int fps = 0;

Time time =
{
	.currTime = 0,
	.prevTime = 0.0f,
	.deltaTime = 0.0f,
};


GameObjectManager gameObjectManager;


void onCubeUpdate(Time time, GameObject* gameObject)
{
	Vector3* pos = &gameObject->transform.position;

	float amplitude = 2.0f;
	float period = 2.0f;

	float theta = (time.currTime) * period;
	float distance = sin(theta) / amplitude;

	float hover = lerp(6.0f, 12.0f, distance);

	pos->y = hover;


	Vector3* rot = &gameObject->transform.rotation;
	rot->x += (time.deltaTime * 20);
	rot->y += (time.deltaTime * 20);
	rot->z += (time.deltaTime * 20);

}


void initialiseWindow(int* argc, char** argv, char* windowName)
{
	// initialise GLUT, with debug logs
	glutInit(argc, argv);
	glutInitContextFlags(GLUT_DEBUG);


	// set RGBA mode, double buffer window, and have a depth buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	// set the window starting position and size
	glutInitWindowPosition(100, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	// set window name
	glutCreateWindow(windowName);

	// Initialise the GUI
	GuiInit();

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
		{ -1.0f, -1.0f, -1.0f },
		{ 1.0f, -1.0f, -1.0f },
		{ -1.0f,  1.0f, -1.0f },
		{ 1.0f,  1.0f, -1.0f },


		{ 1.0f,  1.0f,  1.0f },
		{ 1.0f, -1.0f,  1.0f },
		{ -1.0f,  1.0f,  1.0f },
		{ -1.0f, -1.0f,  1.0f },
	};

	const Vector3Int cubeIndexBuffer[] = {
		// front
		{0, 2, 1},
		{1, 3, 2},
		// right
		{1, 3, 4},
		{4, 5, 1},
		// back
		{5, 4, 6},
		{6, 7, 5},
		// left
		{7, 6, 0},
		{0, 2, 6},
		// bottom
		{0, 1, 7},
		{7, 5, 1},
		// top
		{2, 3, 6},
		{6, 4, 3}
	};

	const RGBA cubeColorBuffer[] = {
		// front colors
		{1.0f, 0.0f, 0.0f, 1.0f},
		{0.0f, 1.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		// back colors
		{1.0f, 0.0f, 0.0f, 1.0f},
		{0.0f, 1.0f, 0.0f, 1.0f},
		{0.0f, 0.0f, 1.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f}
	};

	Mesh cubeMesh = {
		.points = cubeVertexBuffer,
		.indices = cubeIndexBuffer,
		.pointSize = 8,
		.indexCount = 36,
		.colors = cubeColorBuffer,
		.isUniformColor = false,
		.debug = false
	};

	cube.name = "cube";

	cube.mesh = cubeMesh;
	calculateMeshBoundBox(&cube.mesh);

	cube.transform.position = (Vector3){ 5.0f, 4.0f, 0.0f };
	cube.transform.scale = (Vector3){ 1.0f, 1.0f, 1.0f };

	cube.onUpdate = &onCubeUpdate;

	gameObjectManagerAdd(&gameObjectManager, cube);


	GameObject floor;
	initGameObject(&floor);

	// position of each of the ground points
	const Vector3 floorVertexBuffer[] = {
		{ -1.0f, 0.0f, -1.0f },
		{ -1.0f, 0.0f, 1.0f },
		{ 1.0f,  0.0f, 1.0f },
		{ 1.0f,  0.0f, -1.0f },

	};

	// index buffer on how to  the points
	const Vector3Int floorIndexBuffer[] = {
		{0, 1, 2},
		{2, 3, 0}
	};

	// simple RGBA color buffer
	const RGBA floorColorBuffer[] = { {0.7f, 0.7f, 0.7f, 1.0f} };

	// create the mesh
	Mesh floorMesh = {
		.points = floorVertexBuffer,
		.indices = floorIndexBuffer,
		.pointSize = 4,
		.indexCount = 6,
		.colors = floorColorBuffer,
		.isUniformColor = true };

	floor.mesh = floorMesh;
	floor.transform.scale = (Vector3){ 100.0f, 1.0f, 100.0f };

	calculateMeshBoundBox(&floor.mesh);
	gameObjectManagerAdd(&gameObjectManager, floor);

	// enter loop
	glutMainLoop();

	// on program close
	GuiFree();
}


void windowRender(void)
{

	// calculate delta time (time since last frame)
	calculateDeltaTime();

	GuiUpdate(&gameObjectManager);

	// clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// resets transformations
	glLoadIdentity();

	// CAMERA RENDER
	cameraRender(time.deltaTime);

	// ======= GAME OBJECTS RENDER  ======= \\
	
	updateGameObjects(time, &gameObjectManager);

	// ======================================= \\

	GuiRender();

	// swap the buffers
	glutSwapBuffers();
}

void calculateDeltaTime()
{
	// get the current delta time (time since last frame)
	time.currTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	time.deltaTime = (time.currTime - time.prevTime);
	time.prevTime = time.currTime;
}

void reshapeWindow(int width, int height)
{
	ImGui_ImplGLUT_ReshapeFunc();
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
