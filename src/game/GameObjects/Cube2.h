#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "math/Vector.h"
#include "game/Game.h"
#include "math/mathUtils.h"


extern GameObject cube2;

OnStart OnCube2Start(GameObject* gameObject);

OnUpdate OnCube2Update(Time time, GameObject* gameObject);

OnFixedUpdate OnCube2FixedUpdate(Time time, GameObject* gameObject);