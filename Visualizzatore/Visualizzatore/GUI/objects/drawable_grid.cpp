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

    std::vector<int> empty;
    mesh<double> mymesh = mesh<double>(finalBoxes, Grid::getLength());
    save_mesh("/Users/lucapitzalis/volumetric.mesh", mymesh.coords(), mymesh.hexes(), 1 );
    //mymesh.construct_surface();

    mesh<double> mymeshSurface = mymesh.get_surface();
    mymeshSurface.cleanCoords();
    save_quadmesh("/Users/lucapitzalis/quadmesh.obj", mymeshSurface.coords(), mymeshSurface.quads(), mymeshSurface.tris(), 1);


    mymeshSurface.smoothNinetyDegreesAngles(Grid::getLength(), p);
    save_quadmesh("/Users/lucapitzalis/quadmeshSmooth.obj", mymeshSurface.coords(), mymeshSurface.quads(), mymeshSurface.tris(), 1);

}


void DrawableGrid::draw() const
{
    QColor blue = QColor(0,0,255);
    GLfloat red[3] = {1,0,0};

    if(visibleGrid){
        for (int i=0; i < grid.size(); i++)
        {
            for(int j=0; j < grid[i].size(); j++)
            {
                for(int k=0; k < grid[i][j].size(); k++)
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

