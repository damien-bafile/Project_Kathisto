#include "Ground.h"

// position of each of the ground points
const Vector3 groundVertexBuffer[] =
{
	{-100.0f, 0.0f, -100.0f},
	{-100.0f, 0.0f, 100.0f},
	{100.0f, 0.0f, 100.0f},
	{100.0f, 0.0f, -100.0f},
};

// index buffer on how to  the points
const Vector3Int groundIndexBuffer[] =
{
	{0, 1, 2},
	{2, 3, 0}
};

// simple RGBA color buffer
const RGBA groundColorsBuffer[] = { {0.7f, 0.7f, 0.7f, 1.0f} };

// create the mesh
Mesh groundMesh = {
	.points = groundVertexBuffer,
	.indices = groundIndexBuffer,
	.indexCount = 6,
	.colors = groundColorsBuffer,
	.isUniformColor = true };


void groundRender(float deltaTime)
{
	// draw the mesh
	drawMesh(groundMesh);
}