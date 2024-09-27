#include "polyscope/polyscope.h"
// #include "polyscope/surface_mesh.h"
int main()
{
    polyscope::init(); // initialize the gui

    // // add the mesh to the gui
    // polyscope::registerSurfaceMesh("my mesh",
    // 	geometry->vertexPositions, mesh->getFaceVertexList());

    polyscope::show(); // pass control to the gui until the user exits
}
