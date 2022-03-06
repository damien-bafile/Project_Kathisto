#include "Cube.h"

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


const RGBA cubeColorBuffer[] =
{
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

void cubeRender(float deltaTime)
{
	drawMesh(cubeMesh);
}
