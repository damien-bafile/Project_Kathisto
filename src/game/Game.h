#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
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
	int* indices;
	int indexCount;
	RGBA* colors;
	bool isUniformColor;
} Mesh;

typedef struct RigidBody
{
	bool isStatic;
	bool useGravity;
	float mass;
	float velocity;

} RigidBody;

typedef struct GameObject
{
	uint32_t id;
	char *name;
	Transform transform;
	Mesh mesh;
	RigidBody rigidBody;
} GameObject;

typedef struct GameObjectManager
{
	GameObject *gameObjects;
	size_t count;
} GameObjectManager;

typedef struct IdKeyValue
{
	uint32_t id;
	size_t index;
} IdKeyValue;

typedef struct IdMap
{
	IdKeyValue *values;
} IdMap;

/*
	*When a GameObject is added:
		add the game object to the end of the game object list at index of count
		add value to the IDMap of gamobjects id : pushed index (count)
		increase count by 1

	*When a GameObject is removed:
		first find the index in IdMap where id == id
		remove the key value from the IdMap
		remove the gameobject from the game object list by setting it to null




*/





void gameObjectManagerAdd(GameObject GameObject);
void gameObjectManagerRemove(uint32_t id);
GameObject* gameObjectManagerFind(uint32_t id);

void initGameObject(GameObject *gameObject); // initialise the game object
void updateGameObject(GameObject *gameObject); // called every frame update
void fixedUpdateGameObject(GameObject *gameObject); // called on physics update

void initTransform(Transform *transform);
void initMesh(Mesh *mesh);
void initRigidBody(RigidBody *RigidBody);

void drawMesh(Mesh mesh); // draw a mesh
void simulateRigidBody(RigidBody *RigidBody); // simulate rigid body
