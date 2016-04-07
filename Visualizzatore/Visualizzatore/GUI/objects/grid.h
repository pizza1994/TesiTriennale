#ifndef GRID_CELL_H
#define GRID_CELL_H

#endif // GRID_CELL_H
#ifdef __APPLE__
#include <gl.h>
#include <glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <cmath>
#include <vector>
#include "lib/common/point.h"
#include "lib/common/bounding_box.h"
#include "GUI/objects/grid_cell.h"


/**
 * @class Grid
 * @brief The Grid class defines a three-dimensional Grid based on a given bounding box.
 *
 *        The grid is made up of cubes, and as such will use the largest edge of the
 *        bounding box to make sure the whole mesh is contained in the grid.
 *
 * @author Giovanni Laerte Frongia (sirbardo@gmail.com)
 * @author Luca Pitzalis (lucapizza@gmail.com)
 */

//TODO: Optimize the amount of useless cubes we create.

class Grid
{
    public:
        Grid(BoundingBox & bbox, int granularityFactor);

    private:
        double length;
        int granularityFactor;
        void setLength();
        void createGrid();
        BoundingBox internal_bbox;
        std::vector< std::vector<std::vector<GridCell> > > grid;
};
