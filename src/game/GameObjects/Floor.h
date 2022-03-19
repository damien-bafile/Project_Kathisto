#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "math/Vector.h"
#include "game/Game.h"
#include "math/mathUtils.h"


extern GameObject floor;

void OnFloorStart(GameObject *gameObject);
void OnFloorUpdate(Time time, GameObject* gameObject);
void OnFloorFixedUpdate(Time time, GameObject* gameObject)