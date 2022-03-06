#include "Player.h"

const float MOUSE_SENS = 0.001f;
const float WALK_SPEED = 15.0f;
const float UP_SPEED = 10.0f;

Vector3 cameraForwardDir = { 0.0f, 0.0f, -1.0f };
Vector3 cameraPos = { 0.0f, 1.0f, 5.0f };
Vector3 cameraUp = { 0.0f, 1.0f, 0.0f };
Vector3 moveDir = { 0.0f, 0.0f, 0.0f };

Vector2 mousePos = { 0.0f, 0.0f };
Vector2 mouseDeltaPos = { 0.0f, 0.0f };


void computeCameraPos()
{
	// REMEMBER: multiplying by delta time helps create smooth movement

	// calculate the forward/back position
	// new pos = the cams forward dir * (the forward move direction * walk speed)
	Vector3 newPos = Vec3ScalarMultiply(cameraForwardDir, moveDir.z * (WALK_SPEED * deltaTime));
	// change camera's position
	cameraPos.x += newPos.x;
	cameraPos.y += newPos.y;
	cameraPos.z += newPos.z;

	// calculate the left/right position
	// a normalised vectors values are between 0 and 1.
	// a cross product of 2 vectors is a perpendicular vector
	// new pos = normalised (cross product of cameraForward pos and Camera Up) * the move left move direction * walk speed)
	newPos = Vec3ScalarMultiply(Vec3Normalize(Vec3CrossProduct(cameraForwardDir, cameraUp)), moveDir.x * (WALK_SPEED * deltaTime));
	cameraPos.x += newPos.x;
	cameraPos.y += newPos.y;
	cameraPos.z += newPos.z;

	// calculate the up/down position
	cameraPos.y += moveDir.y * (UP_SPEED * deltaTime);

}