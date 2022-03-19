#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <GL/freeglut.h>

#include "math/Vector.h"

typedef struct Time
{
	float currTime;
	float prevTime;
	float deltaTime;
} Time;


typedef struct Transform
{
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

} Transform;

typedef struct Mesh
{
	Vector3* points;
	size_t pointSize;
	Vector3Int* indices;
	int indexCount;
	RGBA* colors;
	bool isUniformColor;

	Vector3 minPosition;
	Vector3 maxPosition;
	bool debug;
} Mesh;

typedef struct RigidBody
{
	bool isStatic;
	bool useGravity;
	float mass;
	float velocity;

} RigidBody;

typedef struct GameObject GameObject;
typedef void (*OnStart)(GameObject*);
typedef void (*OnUpdate)(Time, GameObject*);
typedef void (*OnFixedUpdate)(Time, GameObject*);

struct GameObject
{
	size_t id;
	char* name;
	Transform transform;
	Mesh mesh;
	RigidBody rigidBody;
	bool debug;

	OnStart OnStart;
	OnUpdate OnUpdate;
	OnFixedUpdate OnFixedUpdate;
};

typedef struct GameObjectManager
{
	GameObject* gameObjects;
	size_t count;
	size_t lastIndex;
	size_t freeSpace;
} GameObjectManager;


// game manager struct??
// contains all managers, e.g game object manager etc
// not needed for this unit tbh

void InitGameObjectManager(GameObjectManager* gameObjectManager);
void gameObjectManagerIncrease(GameObjectManager* gameObjectManager);
void gameObjectManagerAdd(GameObjectManager* gameObjectManager, GameObject GameObject);
void gameObjectManagerRemove(GameObjectManager* gameObjectManager, size_t id);
GameObject* gameObjectManagerFind(GameObjectManager* gameObjectManager, size_t id);
void updateGameObjects(Time time, GameObjectManager* gameObjectManager);

void InitGameObject(GameObject* gameObject); // initialise the game object
void SetupCallbacks(GameObject* gameObject, OnStart OnStart, OnUpdate OnUpdate, OnFixedUpdate OnFixedUpdate); // setup the callbacks
void fixedUpdateGameObject(Time time, GameObject* gameObject); // called on physics update
void freeGameObject(GameObject* gameObject); // free the game object

void initTransform(Transform* transform);
void initMesh(Mesh* mesh);
void initRigidBody(RigidBody* RigidBody);


void updateGameObject(Time time, GameObject* gameObject); // called every frame update
void updateTransform(Time time, Transform* transform);
void updateMesh(Time time, Mesh* mesh);
void drawGizmos(Time time, Vector3 maxSize);

void calculateMeshBoundBox(Mesh* mesh);
void freeMesh(Mesh* mesh);

void simulateRigidBody(RigidBody* RigidBody); // simulate rigid body
