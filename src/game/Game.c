#include "Game.h"

void drawMesh(Mesh mesh)
{
    glEnableClientState(GL_COLOR_ARRAY);

    glColorPointer(4, GL_FLOAT, 4, RGBAToArray(mesh.color));
    glEnableClientState(GL_VERTEX_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, mesh.points);
    glDrawElements(GL_POLYGON, mesh.pointCount, GL_UNSIGNED_INT, mesh.indices);

    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
