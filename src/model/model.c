#include "model.h"

model InitModel(unsigned verts, unsigned faces, unsigned edges)
{
	model mod;
	mod.nverts = verts;
	mod.nfaces = faces;
	mod.nedges = edges;
	return mod;
}

void FreeModel(model* mod)
{
	free(mod->vertices);

	for (size_t i = 0; i < mod->nfaces; i++)
		free(mod->faces[i]);
	free(mod->faces);

}
