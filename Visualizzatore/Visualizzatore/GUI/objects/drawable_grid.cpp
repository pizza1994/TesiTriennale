#include "drawable_grid.h"
#include <math.h>

DrawableGrid::DrawableGrid()
{
    visible = false;
}

DrawableGrid::DrawableGrid(const BoundingBox& b, const int granularityFactor, DrawableTrimesh &t, Polyhedron &p):Grid(b, granularityFactor)
{
    Grid::cleanGrid(t, p);
    Grid::createBox();
    char* home = getenv("HOME");
    char homeToStrcat[100];
    strcpy(homeToStrcat, home);
    std::vector<int> empty;
    mesh<double> mymesh = mesh<double>(finalBoxes, Grid::getLength());
    save_mesh((strcat(homeToStrcat,"/volumetric.mesh")), mymesh.coords(), mymesh.hexes(), 1 );
    //mymesh.construct_surface();
    mesh<double> mymeshSurface = mymesh.get_surface();
    mymeshSurface.cleanCoords();


    strcpy(homeToStrcat, home);
    save_quadmesh((strcat(homeToStrcat,"/quadmesh.obj")), mymeshSurface.coords(), mymeshSurface.quads(), mymeshSurface.tris(), 1);
    Polyhedron* pStructure = new Polyhedron();

    strcpy(homeToStrcat, home);

    importOBJ((strcat(homeToStrcat,"/quadmesh.obj")), pStructure);

    mymeshSurface.smoothNinetyDegreesAngles(Grid::getLength(), p, *pStructure);
    strcpy(homeToStrcat, home);
    save_quadmesh((strcat(homeToStrcat,"/quadmeshSmooth.obj")), mymeshSurface.coords(), mymeshSurface.quads(), mymeshSurface.tris(), 1);

}


void DrawableGrid::draw() const
{
    QColor blue = QColor(0,0,255);
    GLfloat red[3] = {1,0,0};

    if(visibleGrid){
        for (int i=0; i < (int) grid.size(); i++)
        {
            for(int j=0; j < (int) grid[i].size(); j++)
            {
                for(int k=0; k < (int) grid[i][j].size(); k++)
                {

                    for(int z=0; z<8; z++){
                         sphere(grid[i][j][k]->getVertex(z), 0.005*internal_bbox.diag()/5, blue);
                        }
                }
            }
        }
    }

    if (visible)
    {


        for (std::vector<Pointd> finalBox : finalBoxes)
        {
            cylinder(finalBox[0], finalBox[1], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[0], finalBox[3], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[0], finalBox[4], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[5], finalBox[1], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[5], finalBox[4], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[5], finalBox[6], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[7], finalBox[6], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[7], finalBox[3], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[7], finalBox[4], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[2], finalBox[6], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[2], finalBox[3], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
            cylinder(finalBox[2], finalBox[1], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        }

    }
}



void DrawableGrid::importOBJ(const std::string& fileName, Polyhedrone* polyhedron)
{
    if(polyhedron)
    {
        try
        {
            // Build Polyhedron_3 from the OBJ file.
            BuildCgalPolyhedronFromObj<Polyhedron::HalfedgeDS> _buildPolyhedron(fileName);

            // Calls is_valid at the end. Throws an exception in debug mode if polyhedron is not
            // manifold.
            polyhedron->delegate(_buildPolyhedron);

            // CGAL::Assert_exception is thrown in the debug mode when
            // CGAL::Polyhedron_incremental_builder_3 is destroyed in BuildCgalPolyhedronFromObj.
            // However, in the release mode assertions is disabled and hence no exception is thrown.
            // Thus for uniform error reporting, if the polyhedron is not valid then throw a dummy
            // exception in release mode.
            if(!polyhedron->is_valid())
            {
                throw CGAL::Assertion_exception("", "", "", 0, "");
            }
        }
        catch(const CGAL::Assertion_exception&)
        {
            std::string _msg = "SMeshLib::importOBJ: Error loading " + fileName;
            //throw std::exception(_msg.c_str());
        }
    }
}



Pointd DrawableGrid::sceneCenter() const
{
    return internal_bbox.center();
}

float DrawableGrid::sceneRadius() const
{
    return internal_bbox.diag();
}

bool DrawableGrid::isVisible() const
{
    return visible;
}

void DrawableGrid::setVisible(bool b)
{
    visible = b;
}

void DrawableGrid::setVisibleGrid(bool b)
{
    visibleGrid = b;
}

bool DrawableGrid::getVisibleGrid()
{
    return visibleGrid;
}

