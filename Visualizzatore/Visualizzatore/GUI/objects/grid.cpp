#include "grid.h"
#include <QDebug>


Grid::Grid()
{
}

Grid::Grid(BoundingBox bbox, int granularityFactor){

    internal_bbox = bbox;
    this->granularityFactor = granularityFactor;
    setLength();
    createGrid();
}


void Grid::setLength()
{


    if ( internal_bbox.getMin().dist( Pointd(internal_bbox.getMaxX(), internal_bbox.getMinY(), internal_bbox.getMinZ()) ) >
         internal_bbox.getMin().dist( Pointd(internal_bbox.getMinX(), internal_bbox.getMaxY(), internal_bbox.getMinZ()) ) )
        if (internal_bbox.getMin().dist( Pointd(internal_bbox.getMaxX(), internal_bbox.getMinY(), internal_bbox.getMinZ()) ) >
            internal_bbox.getMin().dist( Pointd(internal_bbox.getMinX(), internal_bbox.getMinY(), internal_bbox.getMaxZ()) ))
            length = internal_bbox.getMin().dist( Pointd(internal_bbox.getMaxX(), internal_bbox.getMinY(), internal_bbox.getMinZ()) ) / granularityFactor;
        else
            length = internal_bbox.getMin().dist( Pointd(internal_bbox.getMinX(), internal_bbox.getMinY(), internal_bbox.getMaxZ()) ) / granularityFactor;
    else
        length = internal_bbox.getMin().dist( Pointd(internal_bbox.getMinX(), internal_bbox.getMaxY(), internal_bbox.getMinZ()) ) / granularityFactor;
}

std::vector<Pointd> Grid::getVertices() const
{
   std::vector<Pointd> verticesToReturn;

   for(int i=0; i<granularityFactor; i++)
    {
        for(int j=0; j<granularityFactor; j++)
        {
            for (int k=0; k<granularityFactor; k++)
            {
                for (int z=0; z<8; z++)
                    verticesToReturn.push_back(grid[k][j][i].getVertices()[z]);
            }

        }
    }

   return verticesToReturn;
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
    verticesToAssign.resize(8);

    int counter = 0;

    for(int i=0; i<granularityFactor; i++) //for della intera grid
    {
        for(int j=0; j<granularityFactor; j++) //for di un livello di cubi
        {
            for (int k=0; k<granularityFactor; k++) //for di una linea di cubi
            {
                verticesToAssign[0]= ( Pointd( (startVertex.x() + length*i), (startVertex.y() + length*j),  (startVertex.z() + length*k)));
                verticesToAssign[1]= ( Pointd( (startVertex.x() + length*(i+1)), (startVertex.y() + length*j),  (startVertex.z() + length*k)));
                verticesToAssign[2]= ( Pointd( (startVertex.x() + length*i), (startVertex.y() + length*(j+1)),  (startVertex.z() + length*k)));
                verticesToAssign[3]= ( Pointd( (startVertex.x() + length*(i+1)), (startVertex.y() + length*(j+1)),  (startVertex.z() + length*k)));
                verticesToAssign[4]= ( Pointd( (startVertex.x() + length*i), (startVertex.y() + length*j),  (startVertex.z() + length*(k+1))));
                verticesToAssign[5]= ( Pointd( (startVertex.x() + length*(i+1)), (startVertex.y() + length*j),  (startVertex.z() + length*(k+1))));
                verticesToAssign[6]= ( Pointd( (startVertex.x() + length*i), (startVertex.y() + length*(j+1)),  (startVertex.z() + length*(k+1))));
                verticesToAssign[7]= ( Pointd( (startVertex.x() + length*(i+1)), (startVertex.y() + length*(j+1)),  (startVertex.z() + length*(k+1))));
                qDebug() << verticesToAssign[0].x() << verticesToAssign[0].y() << verticesToAssign[0].z();
                grid[i][j][k] = GridCell(verticesToAssign);
                counter++;
            }
        }
    }

    std::vector<GridCell*> adjToAssign;
    adjToAssign.resize(6);


    for(int i=0; i<granularityFactor; i++) //for della intera grid
    {
        for(int j=0; j<granularityFactor; j++) //for di un livello di cubi
        {
            for (int k=0; k<granularityFactor; k++) //for di una linea di cubi
            {
                if (i==0) adjToAssign[0] = NULL;
                else adjToAssign[0] = (&(grid[i-1][j][k]));
                if (i==(granularityFactor-1)) adjToAssign[1] = NULL;
                else adjToAssign[1] = (&(grid[i+1][j][k]));

                if (j==0) adjToAssign[2] = NULL;
                else adjToAssign[2] = (&(grid[k][j-1][i]));
                if (j==(granularityFactor-1)) adjToAssign[3] = NULL;
                else adjToAssign[3] = (&(grid[k][j+1][i]));

                if (k==0) adjToAssign[4] = NULL;
                else adjToAssign[4] = (&(grid[i][j][k-1]));
                if (k==(granularityFactor-1)) adjToAssign[5] = NULL;
                else adjToAssign[5] = (&(grid[i][j][k+1]));

                grid[k][j][i].setAdjCells(adjToAssign);
           }

        }
    }
}

void Grid::cleanGrid(DrawableTrimesh &t){

    int timesIntersected = 0;
    int p = 0;

    for(int i=0; i<(int)grid.size(); i++) //for della intera grid
    {
        for(int j=0; j<(int)grid[i].size(); j++) //for di un livello di cubi
        {
            for (int k=0; k<(int)grid[i][j].size(); k++) //for di una linea di cubi
            {
                for (int z=0; z<8; z++)
                {

                    for (int x=0; x<t.numTriangles(); x++)
                    {
                        if(CheckIntersection::rayTriangleIntersect(grid[i][j][k].getVertex(z),
                                            Pointd(1,0,0),
                                            t.vertex(t.vectorTriangles()[p]),
                                            t.vertex(t.vectorTriangles()[p+1]),
                                            t.vertex(t.vectorTriangles()[p+2])))
                        {
                            timesIntersected++;
                        }
                        p+=3;

                    }

                    if (timesIntersected % 2 == 0) //Se il vertice è fuori dalla mesh
                    {
                        Grid::eraseGridCell(i, j, k); //Elimina l'intera cella dal grigliato.
                        z=8;
                    }

                    timesIntersected = 0;
                    p = 0;
                }

            }
        }
   }


}

void Grid::eraseGridCell(int i, int j, int k)
{
/*
    for (int z=0; z<6; z++)
    {
        if (grid[k][j][i].getAdjCells()[z] != NULL)
        {
            if (z % 2 == 0)
            {
                qDebug() << "Attemping to set adjacency of z = " << z << "to z+1";
                grid[k][j][i].getAdjCells()[z]->setAdjCell(NULL, z+1);
            }
            else
            {
                qDebug() << "Attemping to set adjacency of z = " << z << "to z-1";

                grid[k][j][i].getAdjCells()[z]->setAdjCell(NULL, z-1);
            }
        }
    }
*/
    //grid[i][j].erase(grid[i][j].begin() + (k - (granularityFactor - grid[i][j].size())));
    std::vector<Pointd> vertici = {Pointd(0,0,0),Pointd(0,0,0),Pointd(0,0,0),Pointd(0,0,0),Pointd(0,0,0),Pointd(0,0,0),Pointd(0,0,0),Pointd(0,0,0)};
    grid[i][j][k] = GridCell(vertici);
    //free(&grid[i][j][k]);
}
