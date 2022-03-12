#include "Game.h"

void initGameObjectManager(GameObjectManager* gameObjectManager)
{
    const size_t count = 20u;
    gameObjectManager->count = count;
    gameObjectManager->gameObjects = malloc(count * sizeof(GameObject));
    gameObjectManager->lastIndex = 0u;
    gameObjectManager->freeSpace = count;

    if (gameObjectManager->gameObjects == NULL) return;
    for (size_t i = 0; i < count; i++)
    {
        initGameObject(&gameObjectManager->gameObjects[i]);
    }
}

void gameObjectManagerIncrease(GameObjectManager *gameObjectManager)
{
    const size_t newCount = gameObjectManager->count + (gameObjectManager->count / 2);
    GameObject *temp = realloc(gameObjectManager->gameObjects, newCount * sizeof(GameObject));
    if(temp)
    {
        gameObjectManager->gameObjects = temp;

        for (size_t i = gameObjectManager->count; i < newCount; i++)
        {
            initGameObject(&gameObjectManager->gameObjects[i]);
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
void gameObjectManagerAdd(GameObjectManager *gameObjectManager, GameObject gameObject)
{
    if(gameObjectManager->freeSpace == 0)
        gameObjectManagerIncrease(gameObjectManager);

    gameObject.id = gameObjectManager->lastIndex;

    gameObjectManager->gameObjects[gameObjectManager->lastIndex] = gameObject; // test this

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
void gameObjectManagerRemove(GameObjectManager *gameObjectManager, size_t id)
{
    freeGameObject(&gameObjectManager->gameObjects[id]);
    for (size_t i = id + 1; i < gameObjectManager->count; i++)
    {
        gameObjectManager->gameObjects[i - 1] = gameObjectManager->gameObjects[i];
        gameObjectManager->gameObjects[i - 1].id = i - 1;
        if(i == gameObjectManager->count - 1)
        freeGameObject(&gameObjectManager->gameObjects[i]);
    }
    
    gameObjectManager->count--;
    gameObjectManager->freeSpace++;
    gameObjectManager->lastIndex--;
}

GameObject* gameObjectManagerFind(GameObjectManager *gameObjectManager, size_t id)
{
    return &gameObjectManager->gameObjects[id];
}

void updateGameObjects(GameObjectManager* gameObjectManager)
{
    for (size_t i = 0; i <= gameObjectManager->lastIndex; i++)
    {
        updateGameObject(&gameObjectManager->gameObjects[i]);
    }
}

void initGameObject(GameObject* gameObject)
{
    gameObject->id = NULL;
    gameObject->name = NULL;
    initTransform(&gameObject->transform);
    initMesh(&gameObject->mesh);
    initRigidBody(&gameObject->rigidBody);
}

void updateGameObject(GameObject* gameObject)
{

}

void fixedUpdateGameObject(GameObject* gameObject)
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

void initTransform(Transform *transform)
{
    transform->position = EmptyVec3();
    transform->rotation = EmptyVec3();
    transform->scale = (Vector3){1.0f, 1.0f, 1.0f};
}

void initMesh(Mesh* mesh)
{
    mesh->points = NULL;
    mesh->indices = NULL;
    mesh->indexCount = 0;
    mesh->colors = NULL;
    mesh->isUniformColor = false;
}

void initRigidBody(RigidBody* rigidBody)
{
    rigidBody->isStatic = false;
    rigidBody->useGravity = false;
    rigidBody->mass = 0.0f;
    rigidBody->velocity = 0.0f;
}

void freeMesh(Mesh *mesh)
{
    free(mesh->points);
    free(mesh->indices);
    free(mesh->colors);

    free(mesh);
    mesh = NULL;
}

void drawMesh(Mesh mesh)
{
    if(!mesh.isUniformColor) glEnableClientState(GL_COLOR_ARRAY);

    if (mesh.isUniformColor) 
        glColor4f(mesh.colors[0].r, mesh.colors[0].g, mesh.colors[0].b, mesh.colors[0].a);
    else
        glColorPointer(4, GL_FLOAT, 4, mesh.colors);

    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, mesh.points);
    glDrawElements(GL_TRIANGLES, mesh.indexCount, GL_UNSIGNED_INT, mesh.indices);

    glDisableClientState(GL_VERTEX_ARRAY);
   if(!mesh.isUniformColor) glDisableClientState(GL_COLOR_ARRAY);
}

void simulateRigidBody(RigidBody* RigidBody)
{

}