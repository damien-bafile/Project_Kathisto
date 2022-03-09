#include "Game.h"

void initGameObject(GameObject *gameObject)
{
    gameObject->id = 0;
    gameObject->name = NULL;
    initTransform(&gameObject->transform);
    initMesh(&gameObject->mesh);
    initRigidBody(&gameObject->rigidBody);
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
