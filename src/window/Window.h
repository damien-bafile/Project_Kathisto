#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

#include "game/Game.h"

#include "Events.h"
#include "game/GameObjects/Camera.h"
#include "game/GameObjects/Ground.h"
#include "game/GameObjects/Cube.h"
#include "math/Vector.h"


extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern int frame;
extern int timebase;
extern int fps;

extern int currTime;
extern float prevTime;
extern float deltaTime;

extern GameObjectManager gameObjectManager;

// calculate the delta time
void calculateDeltaTime(); 

// called when window gets resized
void reshapeWindow(int width, int height); 

// called every frame
void windowRender(void); 

// initialise the window with a name
void initialiseWindow(int* argc, char** argv, char* windowName);
