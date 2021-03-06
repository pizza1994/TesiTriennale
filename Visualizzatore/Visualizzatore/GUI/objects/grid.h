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
#include "common.h"
#include <CGAL/compiler_config.h>
#include "lib/common/bounding_box.h"
#include "lib/trimesh/drawable_trimesh.h"
#include <math.h>


#include <algorithm>
#define X_MINUS 0
#define X_PLUS 1
#define Y_MINUS 2
#define Y_PLUS 3
#define Z_MINUS 4
#define Z_PLUS 5

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

typedef CGAL::Simple_cartesian<double> K;
typedef CGAL::Polyhedron_3<K> Polyhedron;
typedef CGAL::AABB_face_graph_triangle_primitive<Polyhedron> Primitive;
typedef CGAL::AABB_traits<K, Primitive> Traits;
typedef CGAL::AABB_tree<Traits> Tree;



class Grid
{
    public:
        Grid();
        Grid(BoundingBox bbox, int granularityFactor);
        std::vector<Pointd> getVertices() const;
        double getLength();

    private:
        double length;
        void setLength();
        void createGrid();
        void eraseGridCell(int i, int j, int &k);

    protected:
        std::vector< std::vector< std::vector<GridCell*> > > grid;
        int granularityFactor;
        BoundingBox internal_bbox;
        std::vector<GridCell*> nextCells;
        std::vector<std::vector<Pointd>> finalBoxes;
        void cleanGrid(DrawableTrimesh &t, Polyhedron &poly);
        void createBox();

        void calculateBox(GridCell* startingCell, GridCell * &finalCell, double &volume, int & xSize, int & ySize, int & zSize, std::vector<Pointd> &boxCoords);
};

#endif
