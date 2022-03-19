#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "math/Vector.h"
#include "game/Game.h"
#include "math/mathUtils.h"


extern GameObject cube;

void OnCubeStart(GameObject* gameObject);

void OnCubeUpdate(Time time, GameObject* gameObject);