#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <GL/freeglut.h>

void onKeyDown(unsigned char key, int x, int y); // on key down
void onKeyUp(unsigned char key, int x, int y); // on key up

void onSpecialKeyDown(int key, int x, int y); // on special key up
void onSpecialKeyUp(int key, int x, int y); // on special key up

void onMouseButton(int button, int state, int x, int y); // on mouse buttons
void onMouseMove(int x, int y); // on mouse move

