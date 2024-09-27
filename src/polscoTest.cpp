#include "geometrycentral/surface/manifold_surface_mesh.h"
#include "geometrycentral/surface/meshio.h"
#include "geometrycentral/surface/surface_mesh.h"

#include "polyscope/polyscope.h"
#include "polyscope/surface_mesh.h"
using namespace geometrycentral;
using namespace geometrycentral::surface;
// a few options
int main()
{
    std::unique_ptr<SurfaceMesh> mesh;
    std::unique_ptr<VertexPositionGeometry> geometry;
    std::tie(mesh, geometry) = readSurfaceMesh("bunny.obj");

    polyscope::init(); // initialize the gui

    // add the mesh to the gui
    polyscope::registerSurfaceMesh("my mesh", geometry->vertexPositions, mesh->getFaceVertexList());

    polyscope::show(); // pass control to the gui until the user exits
}
