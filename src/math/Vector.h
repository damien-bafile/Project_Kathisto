#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Vector2
{
	float x;
	float y;
} Vector2;

typedef struct Vector3
{
	float x;
	float y;
	float z;
} Vector3;

typedef struct RGBA
{
	float r;
	float g;
	float b;
	float a;
} RGBA;


Vector2 ArrayToVec2(const float arr[2]);
Vector3 ArrayToVec3(const float arr[3]);

float* Vec2ToArray(const Vector2 vec);
float* Vec3ToArray(const Vector3 vec);
float* RGBAToArray(const RGBA vec);

float Vec2Length(Vector2 vec);
float Vec3Length(Vector3 vec);

Vector2 Vec2Normalize(Vector2 vec);
Vector3 Vec3Normalize(Vector3 vec);

Vector2 Vec2ScalarMultiply(Vector2 vec, float scalar);
Vector3 Vec3ScalarMultiply(Vector3 vec, float scalar);

Vector2 Vec2Multiply(Vector2 vec1, Vector2 vec2);
Vector3 Vec3Multiply(Vector3 vec1, Vector3 vec2);

Vector3 Vec3CrossProduct(Vector3 vec1, Vector3 vec2);

float Vec2DotProduct(Vector2 vec1, Vector2 vec2);
float Vec3DotProduct(Vector3 vec1, Vector3 vec2);
