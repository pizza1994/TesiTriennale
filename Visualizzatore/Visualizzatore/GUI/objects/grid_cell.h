#ifndef GRID_CELL_H
#define GRID_CELL_H

#include <cmath>
#include <vector>
#include "lib/common/point.h"

class GridCell
{

    public:

        GridCell();
        GridCell(std::vector<Pointd> vertices);
        void setAdjCells(std::vector<GridCell*> adjCells);
        void setAdjCell(GridCell *adjCell, int index);
        std::vector<GridCell*> getAdjCells();
        GridCell* getAdjCell(int index);
        std::vector<Pointd> getVertices() const;
        Pointd getVertex(const int &i) const;

    private:

        std::vector<Pointd> xyz;
        std::vector<GridCell*> adjCells;

};

#endif // GRID_CELL_H
