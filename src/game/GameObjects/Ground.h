#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <GL/freeglut.h>

#include "math/Vector.h"
#include "game/Game.h"
#include "game/GameConstants.h"


// position of each of the ground points
extern const Vector3 groundVertexBuffer[];

// index buffer on how to  the points
extern const Vector3Int groundIndexBuffer[];

// simple RGBA color buffer
extern const RGBA groundColorsBuffer[];

// create the mesh
extern Mesh groundMesh;

void groundRender(float deltaTime);