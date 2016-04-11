#include "grid_cell.h"


GridCell::GridCell()
{
}

GridCell::GridCell(std::vector<Pointd> vertices)
{
    xyz = vertices;
    adjCells.resize(6);
}


void GridCell::setAdjCells(std::vector<GridCell*> adjCells)
{
    this->adjCells = adjCells;
}

void GridCell::setAdjCell(GridCell *adjCell, int index){
    adjCells[index] = adjCell;

}

GridCell* GridCell::getAdjCell(int index){
    return adjCells[index];
}

std::vector<GridCell *> GridCell::getAdjCells()
{
    return adjCells;
}


std::vector<Pointd> GridCell::getVertices() const
{
    return xyz;
}

Pointd GridCell::getVertex(const int &i) const
{
    return xyz[i];
}


