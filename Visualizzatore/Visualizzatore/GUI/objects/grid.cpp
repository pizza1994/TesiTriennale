#include "grid.h"
#include <QDebug>



Grid::Grid(BoundingBox & bbox, int granularityFactor){

    internal_bbox = bbox;
    this->granularityFactor = granularityFactor;
    setLength();
    createGrid();
}


void Grid::setLength()
{
    if ( internal_bbox.getMin().dist(new Pointd(internal_bbox.getMaxX(), internal_bbox.getMinY(), internal_bbox.getMinZ()) ) >
         internal_bbox.getMin().dist(new Pointd(internal_bbox.getMinX(), internal_bbox.getMaxY(), internal_bbox.getMinZ()) ) )
        if (internal_bbox.getMin().dist(new Pointd(internal_bbox.getMaxX(), internal_bbox.getMinY(), internal_bbox.getMinZ()) ) >
            internal_bbox.getMin().dist(new Pointd(internal_bbox.getMinX(), internal_bbox.getMinY(), internal_bbox.getMaxZ()) ))
            length = internal_bbox.getMin().dist(new Pointd(internal_bbox.getMaxX(), internal_bbox.getMinY(), internal_bbox.getMinZ()) ) / granularityFactor;
        else
            length = internal_bbox.getMin().dist(new Pointd(internal_bbox.getMinX(), internal_bbox.getMinY(), internal_bbox.getMaxZ()) ) / granularityFactor;
    else
        length = internal_bbox.getMin().dist(new Pointd(internal_bbox.getMinX(), internal_bbox.getMaxY(), internal_bbox.getMinZ()) ) / granularityFactor;
}

void Grid::createGrid()
{

    grid.resize(granularityFactor);

    for(int j=0; j<granularityFactor; j++)
    {
        grid[j].resize(granularityFactor);

        for (int k=0; k<granularityFactor; k++)
        {
            grid[j][k].resize(granularityFactor);
        }

    }

    //CREARE GRIDCELL - 8 VERTICI E 6 PUNTATORI A GRIDCELL - QUANDO ELIMINO UNA GRIDCELL METTO A NULL I PUNTATORI CHE LO PUNTANO NELLE SUE ADIACENZE.

    Pointd startVertex = internal_bbox.getMin();
    std::vector<Pointd> verticesToAssign;


    for(int i=0; i<granularityFactor; i++) //for della intera grid
    {
        for(int j=0; j<granularityFactor; j++) //for di un livello di cubi
        {
            for (int k=0; k<granularityFactor; k++) //for di una linea di cubi
            {
                verticesToAssign.push_back(new Pointd( (startVertex.x() + length*k), (startVertex.y() + length*j),  (startVertex.z() + length*i)));
                verticesToAssign.push_back(new Pointd( (startVertex.x() + length*(k+1)), (startVertex.y() + length*j),  (startVertex.z() + length*i)));
                verticesToAssign.push_back(new Pointd( (startVertex.x() + length*k), (startVertex.y() + length*(j+1)),  (startVertex.z() + length*i)));
                verticesToAssign.push_back(new Pointd( (startVertex.x() + length*(k+1)), (startVertex.y() + length*(j+1)),  (startVertex.z() + length*i)));
                verticesToAssign.push_back(new Pointd( (startVertex.x() + length*k), (startVertex.y() + length*j),  (startVertex.z() + length*(i+1))));
                verticesToAssign.push_back(new Pointd( (startVertex.x() + length*(k+1)), (startVertex.y() + length*j),  (startVertex.z() + length*(i+1))));
                verticesToAssign.push_back(new Pointd( (startVertex.x() + length*k), (startVertex.y() + length*(j+1)),  (startVertex.z() + length*(i+1))));
                verticesToAssign.push_back(new Pointd( (startVertex.x() + length*(k+1)), (startVertex.y() + length*(j+1)),  (startVertex.z() + length*(i+1))));


                grid[k][j][i] = new GridCell(verticesToAssign);
            }
        }
    }


    std::vector<&GridCell> adjToAssign;
    adjToAssign.resize(6);

    for(int i=0; i<granularityFactor; i++) //for della intera grid
    {
        for(int j=0; j<granularityFactor; j++) //for di un livello di cubi
        {
            for (int k=0; k<granularityFactor; k++) //for di una linea di cubi
            {
                if (k==0) adjToAssign[0] = NULL;
                else adjToAssign[0] = (&(grid[k-1][j][i]));
                if (k==(granularityFactor-1)) adjToAssign[1] = NULL;
                else adjToAssign[1] = (&(grid[k+1][j][i]));

                if (j==0) adjToAssign[2] = NULL;
                else adjToAssign[2] = (&(grid[k][j-1][i]));
                if (j==(granularityFactor-1)) adjToAssign[3] = NULL;
                else adjToAssign[3] = (&(grid[k][j+1][i]));

                if (i==0) adjToAssign[4] = NULL;
                else adjToAssign[4] = (&(grid[k][j][i-1]));
                if (i==(granularityFactor-1)) adjToAssign[5] = NULL;
                else adjToAssign[5] = (&(grid[k][j][i+1]));

                grid[k][j][i].setAdjCells(adjToAssign);
           }
        }
    }





}
