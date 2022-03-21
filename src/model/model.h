#ifndef MODEL_H
#define MODEL_H
#include "../math/math.h"
#include <stdlib.h>

typedef struct rgb
{
	unsigned R;
	unsigned G;
	unsigned B;
} RGB;

typedef struct model
{
	unsigned nverts;
	unsigned nfaces;
	unsigned nedges;

	Vector3 *vertices;
	struct faces{
		unsigned **faces;
		RGB rgbColors;
	};
} model;

model InitModel(unsigned verts, unsigned faces, unsigned edges);
void FreeModel(model *mod);

#endif