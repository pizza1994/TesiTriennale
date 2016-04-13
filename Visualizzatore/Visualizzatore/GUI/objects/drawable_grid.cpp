#include "drawable_grid.h"
#include <math.h>


DrawableGrid::DrawableGrid()
{
    visible = false;
}

DrawableGrid::DrawableGrid(const BoundingBox& b, const int granularityFactor, DrawableTrimesh &t):Grid(b, granularityFactor)
{
    Grid::cleanGrid(t);
    Grid::createBox();
}


void DrawableGrid::draw() const
{

    if (visible)
    {

        QColor blue = QColor(0,0,255);
        GLfloat red[3] = {1,0,0};


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


        cylinder(finalBox[0], finalBox[1], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[0], finalBox[2], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[0], finalBox[4], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[3], finalBox[2], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[3], finalBox[1], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[3], finalBox[7], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[5], finalBox[4], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[5], finalBox[1], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[5], finalBox[7], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[6], finalBox[7], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[6], finalBox[2], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);
        cylinder(finalBox[6], finalBox[4], 0.005*internal_bbox.diag()/5, 0.005*internal_bbox.diag()/5, red);


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
