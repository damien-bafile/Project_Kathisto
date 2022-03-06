#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <GL/freeglut.h>

#include "math/Vector.h"

typedef struct Transform
{
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
} Transform;

typedef struct Mesh
{
	Vector3* points;
	int pointCount;
	int* indices;
	float* colors;
	bool isUniformColor;
} Mesh;

void drawMesh(Mesh mesh);