#include "src/math/Vector.h"


extern const float MOUSE_SENS;
extern const float WALK_SPEED;
extern const float UP_SPEED;

extern Vector3 cameraForwardDir;
extern Vector3 cameraPos;
extern Vector3 cameraUp;
extern Vector3 moveDir;

extern Vector2 mousePos;
extern Vector2 mouseDeltaPos;


void computeCameraPos(); // compute the position of the camera
