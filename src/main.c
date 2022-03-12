#include <stdlib.h>
#include <stdio.h>
#include <GL/glut.h>
#include <GL/freeglut_ext.h>

#include "window/Window.h"



void render(void)
{
	windowRender();
}

int main(int argc, char** argv)
{
	initialiseWindow(&argc, argv, "Project Kathisto");

	return 1;
}