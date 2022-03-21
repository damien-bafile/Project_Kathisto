#include "math.h"

Vector2 MultiplyVector2(unsigned k, Vector2 v)
{
	Vector2 v2 = 
	{ 
		.x = k * v.x, 
		.y = k * v.y 
	};

	return v2;
}

Vector3 MultiplyVector3(unsigned k, Vector3 v)
{
	Vector3 v2 = 
	{ 
		.x = k * v.x, 
		.y = k * v.y , 
		.z = k * v.z 
	};
	
	return v2;
}

double DotProductVector2(Vector2 v1, Vector2 v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

double DotProductVector3(Vector3 v1, Vector3 v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 CrossProductVector3(Vector3 v1, Vector3 v2)
{
	Vector3 v3 =
	{
		.x = v1.y * v2.z - v1.z * v2.y,
		.y = v1.z * v2.x - v1.x * v2.z,
		.z = v1.x * v2.y - v1.y * v2.x,
	};

	return v3;
}