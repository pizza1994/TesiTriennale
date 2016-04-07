#ifndef GRID_CELL_H
#define GRID_CELL_H

#include <cmath>
#include <vector>
#include "lib/common/point.h"
#include "lib/common/bounding_box.h"


class GridCell
{

    public:
        GridCell();
        GridCell(std::vector<Pointd> vertices);
        std::vector<&GridCell> getAdjCells();
        std::vector<Pointd> getVertices();

    private:
        std::vector<Pointd> xyz;
        std::vector<&GridCell> adjCells;


};

#endif // GRID_CELL_H
