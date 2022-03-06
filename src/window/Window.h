#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "math/Vector.h"
#include "game/Player.h"


extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

extern int frame;
extern int timebase;
extern int fps;

extern int currTime;
extern float prevTime;
extern float deltaTime;

void reshapeWindow(int width, int height); // called when window gets resized
void calculateDeltaTime(); // calculate the delta time
void windowRender(void); // called every frame

void onKeyDown(unsigned char key, int x, int y); // on key down
void onKeyUp(unsigned char key, int x, int y); // on key up

void onSpecialKeyDown(int key, int x, int y); // on special key up
void onSpecialKeyUp(int key, int x, int y); // on special key up

void onMouseButton(int button, int state, int x, int y); // on mouse buttons
void onMouseMove(int x, int y); // on mouse move