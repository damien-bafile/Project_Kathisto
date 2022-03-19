#include "Game.h"

void InitGameObjectManager(GameObjectManager* gameObjectManager)
{
	const size_t count = 20u;
	gameObjectManager->count = count;
	gameObjectManager->gameObjects = malloc(count * sizeof(GameObject));
	gameObjectManager->lastIndex = 0u;
	gameObjectManager->freeSpace = count;

	if (gameObjectManager->gameObjects == NULL) return;
	for (size_t i = 0; i < count; i++)
	{
		InitGameObject(&gameObjectManager->gameObjects[i]);
	}
}

void gameObjectManagerIncrease(GameObjectManager* gameObjectManager)
{
	const size_t newCount = gameObjectManager->count + (gameObjectManager->count / 2);
	GameObject* temp = realloc(gameObjectManager->gameObjects, newCount * sizeof(GameObject));
	if (temp)
	{
		gameObjectManager->gameObjects = temp;

		for (size_t i = gameObjectManager->count; i < newCount; i++)
		{
			InitGameObject(&gameObjectManager->gameObjects[i]);
		}

		gameObjectManager->count += newCount;
		gameObjectManager->freeSpace += newCount;
	}
}

/**
 * @brief
 * 	When a GameObject is added:
		add the game object to the end of the game object list at index of count using realloc
		increase count by 1
 * @param gameObjectManager
 * @param gameObject
 */
void gameObjectManagerAdd(GameObjectManager* gameObjectManager, GameObject gameObject)
{
	if (gameObjectManager->freeSpace == 0)
		gameObjectManagerIncrease(gameObjectManager);

	gameObject.id = gameObjectManager->lastIndex;

	gameObjectManager->gameObjects[gameObjectManager->lastIndex] = gameObject; // test this
	if (gameObjectManager->gameObjects[gameObjectManager->lastIndex].OnStart != NULL)
		gameObjectManager->gameObjects[gameObjectManager->lastIndex].OnStart(&gameObjectManager->gameObjects[gameObjectManager->lastIndex]);

	gameObjectManager->freeSpace--;
	gameObjectManager->lastIndex++;
}

/**
 * @brief
 * When a GameObject is removed:
		remove the gameobject from the game object list by setting by freeing it
		for all gameobjects where index > deleted index
		copy the gameobject over to gameobject[i - 1]
		take 1 from count
		freespace add 1
		lastIndex take 1
 * @param gameObjectManager
 * @param id
 */
void gameObjectManagerRemove(GameObjectManager* gameObjectManager, size_t id)
{
	freeGameObject(&gameObjectManager->gameObjects[id]);
	for (size_t i = id + 1; i < gameObjectManager->count; i++)
	{
		gameObjectManager->gameObjects[i - 1] = gameObjectManager->gameObjects[i];
		gameObjectManager->gameObjects[i - 1].id = i - 1;
		if (i == gameObjectManager->count - 1)
			freeGameObject(&gameObjectManager->gameObjects[i]);
	}

	gameObjectManager->count--;
	gameObjectManager->freeSpace++;
	gameObjectManager->lastIndex--;
}

GameObject* gameObjectManagerFind(GameObjectManager* gameObjectManager, size_t id)
{
	return &gameObjectManager->gameObjects[id];
}

void updateGameObjects(Time time, GameObjectManager* gameObjectManager)
{
	for (size_t i = 0; i < gameObjectManager->lastIndex; i++)
	{
		updateGameObject(time, &gameObjectManager->gameObjects[i]);
	}
}

void InitGameObject(GameObject* gameObject)
{
	gameObject->id = 0;
	gameObject->name = NULL;
	initTransform(&gameObject->transform);
	initMesh(&gameObject->mesh);
	initRigidBody(&gameObject->rigidBody);
	gameObject->debug = false;
	gameObject->OnStart = NULL;
	gameObject->OnUpdate = NULL;
	gameObject->OnFixedUpdate = NULL;
}

void SetupCallbacks(GameObject* gameObject, OnStart OnStart, OnUpdate OnUpdate, OnFixedUpdate OnFixedUpdate)
{
	gameObject->OnStart = OnStart;
	gameObject->OnUpdate = OnUpdate;
	gameObject->OnFixedUpdate = OnFixedUpdate;
}

void updateGameObject(Time time, GameObject* gameObject)
{
	glPushMatrix();

	if (gameObject->OnUpdate != NULL) gameObject->OnUpdate(time, gameObject);

	Mesh* mesh = &gameObject->mesh;

	updateTransform(time, &gameObject->transform);

	updateMesh(time, mesh);

	if (gameObject->debug)
		drawGizmos(time, mesh->maxPosition);

	glPopMatrix();
}

void updateTransform(Time time, Transform* transform)
{
	Vector3* pos = &transform->position;
	Vector3* rot = &transform->rotation;
	Vector3* scale = &transform->scale;

	glTranslatef(pos->x, pos->y, pos->z);

	glRotatef(rot->x, 1.0f, 0.0f, 0.0f);
	glRotatef(rot->y, 0.0f, 1.0f, 0.0f);
	glRotatef(rot->z, 0.0f, 0.0f, 1.0f);

	glScalef(scale->x, scale->y, scale->z);
}

void updateMesh(Time time, Mesh* mesh)
{
	if (!mesh->isUniformColor) glEnableClientState(GL_COLOR_ARRAY);

	if (mesh->isUniformColor)
		glColor4f(mesh->colors[0].r, mesh->colors[0].g, mesh->colors[0].b, mesh->colors[0].a);
	else
		glColorPointer(4, GL_FLOAT, 4, mesh->colors);

	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, mesh->points);

	glDrawElements(mesh->debug ? GL_LINE_LOOP : GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, mesh->indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	if (!mesh->isUniformColor) glDisableClientState(GL_COLOR_ARRAY);
}

void drawGizmos(Time time, Vector3 maxSize)
{
	Vector3 gizmoSize = Vec3ScalarAdd(maxSize, 1.5f);

	// X
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(gizmoSize.x, 0.0f, 0.0f);
	glEnd();

	// Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, gizmoSize.y, 0.0f);
	glEnd();

	// Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, gizmoSize.z);
	glEnd();
}

void fixedUpdateGameObject(Time time, GameObject* gameObject)
{

}

void freeGameObject(GameObject* gameObject)
{
	free(gameObject->name);
	gameObject->name = NULL;

	freeMesh(&gameObject->mesh);
	free(gameObject);
	gameObject = NULL;

}

void initTransform(Transform* transform)
{
	transform->position = EmptyVec3();
	transform->rotation = EmptyVec3();
	transform->scale = (Vector3){ 1.0f, 1.0f, 1.0f };
}

void initMesh(Mesh* mesh)
{
	mesh->points = NULL;
	mesh->indices = NULL;
	mesh->indexCount = 0;
	mesh->colors = NULL;
	mesh->isUniformColor = false;
	mesh->minPosition = EmptyVec3();
	mesh->maxPosition = EmptyVec3();
}

void calculateMeshBoundBox(Mesh* mesh)
{
	if (mesh->points == NULL || mesh->pointSize == 0) return;

	Vector3 min = mesh->points[0];
	Vector3 max = mesh->points[0];

	for (size_t i = 0; i < mesh->pointSize; i++)
	{
		if (mesh->points[i].x < min.x) min.x = mesh->points[i].x;
		if (mesh->points[i].y < min.y) min.y = mesh->points[i].y;
		if (mesh->points[i].z < min.z) min.z = mesh->points[i].z;

		if (mesh->points[i].x > max.x) max.x = mesh->points[i].x;
		if (mesh->points[i].y > max.y) max.y = mesh->points[i].y;
		if (mesh->points[i].z > max.z) max.z = mesh->points[i].z;
	}

	mesh->minPosition = min;
	mesh->maxPosition = max;
}

void initRigidBody(RigidBody* rigidBody)
{
	rigidBody->isStatic = false;
	rigidBody->useGravity = false;
	rigidBody->mass = 0.0f;
	rigidBody->velocity = 0.0f;
}

void freeMesh(Mesh* mesh)
{
	free(mesh->points);
	free(mesh->indices);
	free(mesh->colors);

	free(mesh);
	mesh = NULL;
}

void simulateRigidBody(RigidBody* RigidBody)
{

}