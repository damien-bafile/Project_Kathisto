#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "math/Vector.h"
#include "game/Game.h"
#include "math/mathUtils.h"


extern GameObject cube;

void onCubeStart(GameObject* gameObject);

void onCubeUpdate(Time time, GameObject* gameObject);