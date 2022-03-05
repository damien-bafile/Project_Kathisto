#include <stdlib.h>
#include <stdio.h>

#include "math/Vector.h"

int main()
{
	Vector3 vec3 = { 1.0f, 2.0f, 3.0f };
	printf("Hello World!\n");
	printf("%f %f %f\n", vec3.x, vec3.y, vec3.z);

	vec3 = Vec3ScalarMultiply(vec3, 12.0f);
	printf("%f %f %f\n", vec3.x, vec3.y, vec3.z);
	return 0;
}
