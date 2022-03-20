#include "Cube2.h"

GameObject cube2 = { 0 };

const Vector3 cube2VertexBuffer[] = {
	{ -1.0f, -1.0f, -1.0f },
	{ 1.0f, -1.0f, -1.0f },
	{ -1.0f,  1.0f,  -1.0f },
	{ 1.0f, 1.0f,  -1.0f },
	{ 0.0f,  0.0f,  5.0f },
};

const Vector3Int cube2IndexBuffer[] = {
	// base
	{0, 1, 2},
	{3, 2, 1},
	// front
	{0, 5, 1},
	// back
	{1, 5, 2},
	// left
	{2, 5, 3},
	// right
	{3, 5, 0},
};

const RGBA cube2ColorBuffer[] = {
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

Mesh cube2Mesh = {
	.points = cube2VertexBuffer,
	.indices = cube2IndexBuffer,
	.pointSize = 5,
	.indexCount = 18,
	.colors = cube2ColorBuffer,
	.isUniformColor = true,
	.debug = false
};

OnStart OnCube2Start(GameObject* gameObject)
{
	gameObject->name = "cube2";

	gameObject->mesh = cube2Mesh;
	CalculateMeshBoundBox(&gameObject->mesh);

	gameObject->transform.position = (Vector3){ 10.0f, 4.0f, 0.0f };
	gameObject->transform.scale = (Vector3){ 1.0f, 1.0f, 5.0f };
}

OnUpdate OnCube2Update(Time time, GameObject* gameObject)
{
	Vector3* pos = &gameObject->transform.position;

	float amplitude = 1.0f;
	float period = 1.0f;

	float theta = (time.currTime) * period;
	float distance = sin(theta) / amplitude;

	float hover = lerp(6.0f, 12.0f, distance);

	pos->y = hover;


	Vector3* rot = &gameObject->transform.rotation;
	rot->x += (time.deltaTime * 100);
	rot->y += (time.deltaTime * 100);
	rot->z += (time.deltaTime * 100);

}

OnFixedUpdate OnCube2FixedUpdate(Time time, GameObject* gameObject)
{
}