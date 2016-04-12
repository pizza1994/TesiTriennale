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
                    verticesToReturn.push_back(grid[k][j][i]->getVertices()[z]);
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
                //qDebug() << verticesToAssign[0].x() << verticesToAssign[0].y() << verticesToAssign[0].z();
                grid[i][j].push_back(new GridCell(verticesToAssign));
                counter++;
            }
        }
    }

    std::vector<GridCell*> adjToAssign;
    adjToAssign.resize(6);


    for(int i=0; i<grid.size(); i++) //for della intera grid
    {
        for(int j=0; j<grid[i].size(); j++) //for di un livello di cubi
        {
            for (int k=0; k<grid[i][j].size(); k++) //for di una linea di cubi
            {

                if (i==0) grid[i][j][k]->setAdjCell(NULL, 0);
                else grid[i][j][k]->setAdjCell((grid[i-1][j][k]), 0);
                if (i==(granularityFactor-1)) grid[i][j][k]->setAdjCell(NULL, 1);
                else grid[i][j][k]->setAdjCell(grid[i+1][j][k], 1);

                if (j==0) grid[i][j][k]->setAdjCell(NULL, 2);
                else grid[i][j][k]->setAdjCell(grid[i][j-1][k], 2);
                if (j==(granularityFactor-1)) grid[i][j][k]->setAdjCell(NULL, 3);
                else grid[i][j][k]->setAdjCell(grid[i][j+1][k], 3);

                if (k==0) grid[i][j][k]->setAdjCell(NULL, 4);
                else grid[i][j][k]->setAdjCell(grid[i][j][k-1], 4);
                if (k==(granularityFactor-1)) grid[i][j][k]->setAdjCell(NULL, 5);
                else grid[i][j][k]->setAdjCell(grid[i][j][k+1], 5);

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
                //qDebug () << i << " " << j << " " << k;
                for (int z=0; z<8; z++)
                {

                    for (int x=0; x<t.numTriangles(); x++)
                    {
                        if(CheckIntersection::rayTriangleIntersect(grid[i][j][k]->getVertex(z),
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
                    else

                    timesIntersected = 0;
                    p = 0;
                }

            }

            if (grid[i][j].size() == 0)
            {
                grid[i].erase(grid[i].begin() + j);
                j--;
            }
        }

        if (grid[i].size() == 0)
        {
            grid.erase(grid.begin() + i);
            i--;
        }

   }


}

void Grid::eraseGridCell(int i, int j, int &k)
{

    for (int z=0; z<6; z++)
    {
        if ( grid[i][j][k]->getAdjCell(z) != NULL)
        {
            if (z % 2 == 0)
            {

                (grid[i][j][k]->getAdjCell(z))->setAdjCell(NULL, z+1);
            }
            else
            {
                (grid[i][j][k]->getAdjCell(z))->setAdjCell(NULL, z-1);

            }

        }
    }

    delete (grid[i][j][k]);
    grid[i][j].erase(grid[i][j].begin()+ k);
    k--;

}

void Grid::createBox(){

    int volume=0;
    std::vector<Pointd> boxCoords;
    boxCoords.resize(8);

    GridCell * finalCell = grid[0][0][0];

    for(int x = 0; x < grid.size(); x++)
    {
        for (int y = 0; y < grid[x].size(); y++)
        {
            for (int z = 0; z < grid[x][y].size(); z++)
            {
                calculateBox(grid[x][y][z], volume, boxCoords);
            }
        }
    }
    finalBox = boxCoords;
    qDebug() << "volume: " <<volume;

}

void Grid::calculateBox(GridCell* startingCell, int &volume, std::vector<Pointd> &boxCoords){

    std::vector<GridCell*> vectorX;
    GridCell* cell = startingCell;
    int minY=0;
    int localY = 0;
    int minZ=0;
    int localZ=0;


    vectorX.push_back(cell);
    if (!cell->getAdjCell(X_PLUS) == NULL)
    {
        cell = cell->getAdjCell((X_PLUS));
        while (cell->getAdjCell(X_PLUS)){
            vectorX.push_back(cell);
            cell = cell->getAdjCell(X_PLUS);
        }
    }

    for (int x=0; x < vectorX.size(); x++)
    {
        cell = vectorX[x];
        if (cell->getAdjCell(Y_PLUS) == NULL)
        {
            x = vectorX.size();
        }
        else
        {
            cell = cell->getAdjCell((Y_PLUS));
            localY++;
            while (cell->getAdjCell(Y_PLUS) )
                {
                    localY++;
                    cell = cell->getAdjCell(Y_PLUS);
                }

        }

        if (x == 0) minY = localY;
        else if (localY < minY) minY = localY;

        localY=0;
    }

    //qDebug() <<minY;

    for (int x = 0; x < vectorX.size(); x++)
    {
        cell = vectorX[x];
        for (int y = 0; y <= minY; y++)
        {
            if (cell->getAdjCell(Z_PLUS) != NULL)
            {
                GridCell * tempCell = cell;

                while (tempCell->getAdjCell(Z_PLUS) )
                {
                    localZ++;
                    tempCell = tempCell->getAdjCell(Z_PLUS);
                }
            }
            if (x==0 && y==0)   minZ = localZ;
            else if (localZ < minZ)     minZ = localZ;
            cell = cell->getAdjCell(Y_PLUS);

            localZ = 0;
        }

    }

    if (vectorX.size()*(minY+1)*(minZ+1)*pow(length,3 ) > volume)
    {
        volume = vectorX.size()*(minY+1)*(minZ+1)*pow(length,3 );

        Pointd v0 = startingCell->getVertex(0);

        boxCoords[0] = v0;
        boxCoords[1] = Pointd(v0.x() + length*vectorX.size(), v0.y(), v0.z() );
        boxCoords[2] = Pointd(v0.x(), v0.y() +length*(minY+1), v0.z() );
        boxCoords[3] = Pointd(v0.x() +length*vectorX.size(), v0.y() + length*(minY+1), v0.z() );
        boxCoords[4] = Pointd(v0.x(), v0.y(), v0.z() +length*(minZ+1) );
        boxCoords[5] = Pointd(v0.x() + length*vectorX.size(), v0.y(), v0.z() + length*(minZ+1) );
        boxCoords[6] = Pointd(v0.x(), v0.y() + length*(minY+1), v0.z() + length*(minZ+1) );
        boxCoords[7] = Pointd(v0.x() + length*vectorX.size(), v0.y() + length*(minY+1), v0.z() + length*(minZ+1) );
    }

}






