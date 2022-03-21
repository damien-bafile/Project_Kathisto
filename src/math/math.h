#ifndef MATH_H
#define MATH_H

typedef struct Point3
{
  double x;
  double y;
  double z;
} Point3;

typedef struct Vector2
{
  double x;
  double y;
} Vector2;

typedef struct Vector3
{
  double x;
  double y;
  double z;
} Vector3;

Vector2 MultiplyVector2(unsigned k, Vector2 v);
Vector3 MultiplyVector3(unsigned k, Vector3 v);

double DotProductVector2(Vector2 v1, Vector2 v2);
double DotProductVector3(Vector3 v1, Vector3 v2);

Vector3 CrossProductVector3(Vector3 v1, Vector3 v2);
#endif