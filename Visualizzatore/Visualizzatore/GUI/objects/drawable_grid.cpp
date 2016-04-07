#include "drawable_grid.h"
#include <math.h>
#include "GUI/objects/sphere.h"


DrawableGrid::DrawableGrid()
{
    visible = false;
}

DrawableGrid::DrawableGrid(const BoundingBox& b, const int granularityFactor):Grid(b, granularityFactor)
{
}


void DrawableGrid::draw() const
{

    if (visible)
    {

        QColor blue = QColor(0,0,255);

        for (int i=0; i < granularityFactor; i++)
        {
            for(int j=0; j < granularityFactor; j++)
            {
                for(int k=0; k < granularityFactor; k++)
                {
                    for(int z=0; z<8; z++)
                        sphere(grid[k][j][i].getVertex(z), 1, blue);
                }
            }
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
