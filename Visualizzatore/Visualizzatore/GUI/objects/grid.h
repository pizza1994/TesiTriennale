#ifndef GRID_H
#define GRID_H
#ifdef __APPLE__
#include <gl.h>
#include <glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <cmath>
#include "grid_cell.h"
#include <vector>
#include "lib/common/point.h"
#include "lib/common/bounding_box.h"
#include "lib/trimesh/drawable_trimesh.h"
#include <math.h>
#include "lib/common/check_intersection.h"


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
        Grid();
        Grid(BoundingBox bbox, int granularityFactor);
        std::vector<Pointd> getVertices() const;

    private:
        double length;
        void setLength();
        void createGrid();
        void eraseGridCell(int i, int j, int k);

    protected:
        std::vector< std::vector<std::vector<GridCell> > > grid;
        int granularityFactor;
        BoundingBox internal_bbox;
        void cleanGrid(DrawableTrimesh &t);
};

#endif
