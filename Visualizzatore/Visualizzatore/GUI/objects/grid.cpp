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


    for(int i=0; i< (int) grid.size(); i++) //for della intera grid
    {
        for(int j=0; j< (int) grid[i].size(); j++) //for di un livello di cubi
        {
            for (int k=0; k< (int) grid[i][j].size(); k++) //for di una linea di cubi
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
    std::vector<Pointd> alreadyCheckVertices;
    std::vector<Pointd> firstSubdivision;
    std::vector<Pointd> secondSubdivision;
    std::vector<Pointd> thirdSubdivision;
    std::vector<Pointd> fourthSubdivision;
    std::vector<Pointd> fifthSubdivision;
    std::vector<Pointd> sixthSubdivision;
    std::vector<Pointd> seventhSubdivision;
    std::vector<Pointd> eighthSubdivision;

    for(int i = 0; i<t.numTriangles();i++){
        if(t.vertex(t.vectorTriangles()[p]).x() > internal_bbox.center().x() &&
           t.vertex(t.vectorTriangles()[p]).y() > internal_bbox.center().y() &&
           t.vertex(t.vectorTriangles()[p]).z() > internal_bbox.center().z()){


            eighthSubdivision.push_back(t.vertex(t.vectorTriangles()[p]));
            eighthSubdivision.push_back(t.vertex(t.vectorTriangles()[p+1]));
            eighthSubdivision.push_back(t.vertex(t.vectorTriangles()[p+2]));

        }
        else if(t.vertex(t.vectorTriangles()[p]).x() < internal_bbox.center().x() &&
                t.vertex(t.vectorTriangles()[p]).y() > internal_bbox.center().y() &&
                t.vertex(t.vectorTriangles()[p]).z() > internal_bbox.center().z()){
            seventhSubdivision.push_back(t.vertex(t.vectorTriangles()[p]));
            seventhSubdivision.push_back(t.vertex(t.vectorTriangles()[p+1]));
            seventhSubdivision.push_back(t.vertex(t.vectorTriangles()[p+2]));
        }
        else if(t.vertex(t.vectorTriangles()[p]).x() > internal_bbox.center().x() &&
                t.vertex(t.vectorTriangles()[p]).y() > internal_bbox.center().y() &&
                t.vertex(t.vectorTriangles()[p]).z() < internal_bbox.center().z()){
            sixthSubdivision.push_back(t.vertex(t.vectorTriangles()[p]));
            sixthSubdivision.push_back(t.vertex(t.vectorTriangles()[p+1]));
            sixthSubdivision.push_back(t.vertex(t.vectorTriangles()[p+2]));
        }
        else if(t.vertex(t.vectorTriangles()[p]).x() < internal_bbox.center().x() &&
                t.vertex(t.vectorTriangles()[p]).y() > internal_bbox.center().y() &&
                t.vertex(t.vectorTriangles()[p]).z() < internal_bbox.center().z()){
            fifthSubdivision.push_back(t.vertex(t.vectorTriangles()[p]));
            fifthSubdivision.push_back(t.vertex(t.vectorTriangles()[p+1]));
            fifthSubdivision.push_back(t.vertex(t.vectorTriangles()[p+2]));
        }
        else if(t.vertex(t.vectorTriangles()[p]).x() > internal_bbox.center().x() &&
                t.vertex(t.vectorTriangles()[p]).y() < internal_bbox.center().y() &&
                t.vertex(t.vectorTriangles()[p]).z() > internal_bbox.center().z()){
            fourthSubdivision.push_back(t.vertex(t.vectorTriangles()[p]));
            fourthSubdivision.push_back(t.vertex(t.vectorTriangles()[p+1]));
            fourthSubdivision.push_back(t.vertex(t.vectorTriangles()[p+2]));
        }
        else if(t.vertex(t.vectorTriangles()[p]).x() < internal_bbox.center().x() &&
                t.vertex(t.vectorTriangles()[p]).y() < internal_bbox.center().y() &&
                t.vertex(t.vectorTriangles()[p]).z() > internal_bbox.center().z()){
            thirdSubdivision.push_back(t.vertex(t.vectorTriangles()[p]));
            thirdSubdivision.push_back(t.vertex(t.vectorTriangles()[p+1]));
            thirdSubdivision.push_back(t.vertex(t.vectorTriangles()[p+2]));
        }
        else if(t.vertex(t.vectorTriangles()[p]).x() > internal_bbox.center().x() &&
                t.vertex(t.vectorTriangles()[p]).y() < internal_bbox.center().y() &&
                t.vertex(t.vectorTriangles()[p]).z() < internal_bbox.center().z()){
            secondSubdivision.push_back(t.vertex(t.vectorTriangles()[p]));
            secondSubdivision.push_back(t.vertex(t.vectorTriangles()[p+1]));
            secondSubdivision.push_back(t.vertex(t.vectorTriangles()[p+2]));
        }
        else
        {
            firstSubdivision.push_back(t.vertex(t.vectorTriangles()[p]));
            firstSubdivision.push_back(t.vertex(t.vectorTriangles()[p+1]));
            firstSubdivision.push_back(t.vertex(t.vectorTriangles()[p+2]));
        }
        p+=3;
    }
    p=0;



    for(int i=0; i<(int)grid.size(); i++) //for della intera grid
    {
        for(int j=0; j<(int)grid[i].size(); j++) //for di un livello di cubi
        {
            for (int k=0; k<(int)grid[i][j].size(); k++) //for di una linea di cubi
            {
                //qDebug () << i << " " << j << " " << k;
                for (int z=0; z<8; z++)
                {
                    if (grid[i][j][k]->getVertex(z).x() < internal_bbox.getMinX() ||
                        grid[i][j][k]->getVertex(z).y() < internal_bbox.getMinY() ||
                        grid[i][j][k]->getVertex(z).z() < internal_bbox.getMinZ() ||
                        grid[i][j][k]->getVertex(z).x() > internal_bbox.getMaxX() ||
                        grid[i][j][k]->getVertex(z).y() > internal_bbox.getMaxY() ||
                        grid[i][j][k]->getVertex(z).z() > internal_bbox.getMaxZ())
                    {
                        eraseGridCell(i, j, k);
                        z=8;
                    }
                    else if ( !checkPointInVector(grid[i][j][k]->getVertex(z), alreadyCheckVertices))
                    {

                        if(grid[i][j][k]->getVertex(z).x() > internal_bbox.center().x() &&
                           grid[i][j][k]->getVertex(z).y() > internal_bbox.center().y() &&
                           grid[i][j][k]->getVertex(z).z() > internal_bbox.center().z())
                        {
                            for (int x=0; x< (int) eighthSubdivision.size()/3; x++)
                            {
                                if(CheckIntersection::rayTriangleIntersect(grid[i][j][k]->getVertex(z),
                                                                           Pointd(1,1,1),
                                                                           eighthSubdivision[p],
                                                                           eighthSubdivision[p+1],
                                                                           eighthSubdivision[p+2]))
                                {
                                    timesIntersected++;
                                }

                                p+=3;


                            }
                        }
                        else if(grid[i][j][k]->getVertex(z).x() < internal_bbox.center().x() &&
                                grid[i][j][k]->getVertex(z).y() > internal_bbox.center().y() &&
                                grid[i][j][k]->getVertex(z).z() > internal_bbox.center().z())
                        {
                            for (int x=0; x< (int) seventhSubdivision.size()/3; x++)
                            {
                                if(CheckIntersection::rayTriangleIntersect(grid[i][j][k]->getVertex(z),
                                                                           Pointd(-1,1,1),
                                                                           seventhSubdivision[p],
                                                                           seventhSubdivision[p+1],
                                                                           seventhSubdivision[p+2]))
                                {
                                    timesIntersected++;
                                }

                                p+=3;


                            }
                        }
                        else if(grid[i][j][k]->getVertex(z).x() > internal_bbox.center().x() &&
                                grid[i][j][k]->getVertex(z).y() > internal_bbox.center().y() &&
                                grid[i][j][k]->getVertex(z).z() < internal_bbox.center().z())
                        {
                            for (int x=0; x< (int) sixthSubdivision.size()/3; x++)
                            {
                                if(CheckIntersection::rayTriangleIntersect(grid[i][j][k]->getVertex(z),
                                                                           Pointd(1,1,-1),
                                                                           sixthSubdivision[p],
                                                                           sixthSubdivision[p+1],
                                                                           sixthSubdivision[p+2]))
                                {
                                    timesIntersected++;
                                }

                                p+=3;


                            }
                        }

                        else if(grid[i][j][k]->getVertex(z).x() < internal_bbox.center().x() &&
                                grid[i][j][k]->getVertex(z).y() > internal_bbox.center().y() &&
                                grid[i][j][k]->getVertex(z).z() < internal_bbox.center().z())
                        {
                            for (int x=0; x< (int) fifthSubdivision.size()/3; x++)
                            {
                                if(CheckIntersection::rayTriangleIntersect(grid[i][j][k]->getVertex(z),
                                                                           Pointd(-1,1,-1),
                                                                           fifthSubdivision[p],
                                                                           fifthSubdivision[p+1],
                                                                           fifthSubdivision[p+2]))
                                {
                                    timesIntersected++;
                                }

                                p+=3;


                            }
                        }

                        else if(grid[i][j][k]->getVertex(z).x() > internal_bbox.center().x() &&
                                grid[i][j][k]->getVertex(z).y() < internal_bbox.center().y() &&
                                grid[i][j][k]->getVertex(z).z() > internal_bbox.center().z())
                        {
                            for (int x=0; x< (int) fourthSubdivision.size()/3; x++)
                            {
                                if(CheckIntersection::rayTriangleIntersect(grid[i][j][k]->getVertex(z),
                                                                           Pointd(1,-1,1),
                                                                           fourthSubdivision[p],
                                                                           fourthSubdivision[p+1],
                                                                           fourthSubdivision[p+2]))
                                {
                                    timesIntersected++;
                                }

                                p+=3;


                            }
                        }

                        else if(grid[i][j][k]->getVertex(z).x() < internal_bbox.center().x() &&
                                grid[i][j][k]->getVertex(z).y() < internal_bbox.center().y() &&
                                grid[i][j][k]->getVertex(z).z() > internal_bbox.center().z())
                        {
                            for (int x=0; x< (int) thirdSubdivision.size()/3; x++)
                            {
                                if(CheckIntersection::rayTriangleIntersect(grid[i][j][k]->getVertex(z),
                                                                           Pointd(-1,-1,1),
                                                                           thirdSubdivision[p],
                                                                           thirdSubdivision[p+1],
                                                                           thirdSubdivision[p+2]))
                                {
                                    timesIntersected++;
                                }

                                p+=3;


                            }
                        }

                        else if(grid[i][j][k]->getVertex(z).x() > internal_bbox.center().x() &&
                                grid[i][j][k]->getVertex(z).y() < internal_bbox.center().y() &&
                                grid[i][j][k]->getVertex(z).z() < internal_bbox.center().z())
                        {
                            for (int x=0; x< (int) secondSubdivision.size()/3; x++)
                            {
                                if(CheckIntersection::rayTriangleIntersect(grid[i][j][k]->getVertex(z),
                                                                           Pointd(1,-1,-1),
                                                                           secondSubdivision[p],
                                                                           secondSubdivision[p+1],
                                                                           secondSubdivision[p+2]))
                                {
                                    timesIntersected++;
                                }

                                p+=3;


                            }
                        }

                        else
                        {
                            for (int x=0; x< (int) firstSubdivision.size()/3; x++)
                            {
                                if(CheckIntersection::rayTriangleIntersect(grid[i][j][k]->getVertex(z),
                                                                           Pointd(-1,-1,-1),
                                                                           firstSubdivision[p],
                                                                           firstSubdivision[p+1],
                                                                           firstSubdivision[p+2]))
                                {
                                    timesIntersected++;
                                }

                                p+=3;


                            }
                        }


                        if (timesIntersected % 2 == 0) //Se il vertice è fuori dalla mesh
                        {

                            eraseGridCell(i, j, k); //Elimina l'intera cella dal grigliato.
                            z=8;
                        }
                        else{
                            alreadyCheckVertices.push_back(grid[i][j][k]->getVertex(z));

                        }
                        timesIntersected = 0;
                        p = 0;

                    }

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

    double volume=0;
    std::vector<Pointd> boxCoords;
    boxCoords.resize(8);
    int xSize, ySize, zSize;
    std::vector<GridCell*> vectorX;
    GridCell * tempCellj = NULL;
    GridCell * tempCelli = NULL;
    GridCell * finalCell = NULL;

    for(int x = 0; x < (int) grid.size(); x++)
    {
        for (int y = 0; y < (int)grid[x].size(); y++)
        {
            for (int z = 0; z < (int)grid[x][y].size(); z++)
            {
                calculateBox(grid[x][y][z], finalCell, volume, xSize, ySize, zSize, boxCoords);
            }
        }
    }





    vectorX.push_back(finalCell);
    tempCellj = finalCell;
    for (int x=0; x<xSize; x++)
    {
        vectorX.push_back(tempCellj->getAdjCell(X_PLUS));
        tempCellj = tempCellj->getAdjCell(X_PLUS);
    }


    //int counter = 0;

    GridCell* tempCellY;

    for (int x = 0; x < xSize; x++) // Faccia Z-
    {
        tempCelli = vectorX[x];
        tempCellj = tempCelli;

        for (int y = 0; y < ySize ; y++)
        {

            if (x == 0 && y == 0)
            {
                if (tempCellj->getAdjCell(X_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_MINUS));
                if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));
                if (tempCellj->getAdjCell(Z_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_MINUS));
            }
            else
                if (x == (xSize-1) && y == 0)
                {
                    if (tempCellj->getAdjCell(X_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_PLUS));
                    if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));
                    if (tempCellj->getAdjCell(Z_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_MINUS));
                }
                else
                    if (x == 0 && y == (ySize-1))
                    {
                        if (tempCellj->getAdjCell(X_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_MINUS));
                        if (tempCellj->getAdjCell(Y_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_PLUS));
                        if (tempCellj->getAdjCell(Z_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_MINUS));
                    }
                    else
                        if (x == (xSize-1) && y == (ySize-1) )
                        {
                            if (tempCellj->getAdjCell(X_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_PLUS));
                            if (tempCellj->getAdjCell(Y_PLUS) != NULL)nextCells.push_back( tempCellj->getAdjCell(Y_PLUS));
                            if (tempCellj->getAdjCell(Z_MINUS) != NULL)nextCells.push_back( tempCellj->getAdjCell(Z_MINUS));
                        }
                        else
                            if (x > 0 && y == 0)
                            {
                                if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));
                                if (tempCellj->getAdjCell(Z_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_MINUS));
                            }
                            else
                                if (x == (xSize-1) && y>0)
                                {
                                    if (tempCellj->getAdjCell(X_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_PLUS));
                                    if (tempCellj->getAdjCell(Z_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_MINUS));
                                }
                                else
                                    if (x == 0 && y>0)
                                    {
                                        if (tempCellj->getAdjCell(X_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_MINUS));
                                        if (tempCellj->getAdjCell(Z_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_MINUS));
                                    }
                                    else
                                        if (x>0 && y>0)
                                        {
                                            if (tempCellj->getAdjCell(Y_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_PLUS));
                                            if (tempCellj->getAdjCell(Z_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_MINUS));
                                        }

                tempCellj = tempCellj->getAdjCell(Y_PLUS);
        }
    }

    tempCelli = vectorX[0]->getAdjCell(Z_PLUS);

    for (int z = 1; z < zSize; z++) // Faccia X-
    {
        tempCellj = tempCelli;

        for (int y = 0 ; y < ySize; y++)
        {

            if (y == 0 && z == (zSize-1))
            {
                if (tempCellj->getAdjCell(X_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_MINUS));
                if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));
                if (tempCellj->getAdjCell(Z_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_PLUS));
            }
            else
                if (y == (ySize-1) && z == (zSize-1) )
                {
                    if (tempCellj->getAdjCell(X_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_MINUS));
                    if (tempCellj->getAdjCell(Y_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_PLUS));
                    if (tempCellj->getAdjCell(Z_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_PLUS));
                }
                else
                    if (z == (zSize-1) && y>0)
                    {
                        if (tempCellj->getAdjCell(X_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_MINUS));
                        if (tempCellj->getAdjCell(Z_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_PLUS));

                    }
                    else
                        if (y == (ySize-1))
                        {
                            if (tempCellj->getAdjCell(X_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_MINUS));
                            if (tempCellj->getAdjCell(Y_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_PLUS));
                        }
                        else
                            if (y==0)
                            {
                                if (tempCellj->getAdjCell(X_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_MINUS));
                                if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));
                            }
                            else
                            {
                                if (tempCellj->getAdjCell(X_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_MINUS));
                            }

            tempCellj = tempCellj->getAdjCell(Y_PLUS);
        }

        tempCelli = tempCelli->getAdjCell(Z_PLUS);
    }

    tempCelli = vectorX[0]->getAdjCell(Z_PLUS)->getAdjCell(X_PLUS);

    for(int x = 1; x < xSize; x++) //FACCIA Y-
    {
        tempCellj = tempCelli;

        for (int z = 1; z < zSize; z++ ){


            if(x == (xSize-1) && z == (zSize-1))
            {
                if (tempCellj->getAdjCell(X_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_PLUS));
                if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));
                if (tempCellj->getAdjCell(Z_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_PLUS));

            }
            else
                if(x == (xSize-1))
                {
                    if (tempCellj->getAdjCell(X_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_PLUS));
                    if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));

                }

                else
                    if(z == (zSize-1))
                    {
                        if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));
                        if (tempCellj->getAdjCell(Z_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_PLUS));

                    }

                    else
                        if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));

            tempCellj = tempCellj->getAdjCell(Z_PLUS);

        }
        tempCelli = tempCelli->getAdjCell(X_PLUS);
    }

    tempCelli = vectorX[xSize-1]->getAdjCell(Z_PLUS)->getAdjCell(Y_PLUS);

    for(int y = 1; y<ySize; y++) //FACCIA X+
    {
        tempCellj = tempCelli;

        for(int z = 1; z<zSize; z++)
        {
            if(y== (ySize-1) && z == (zSize-1))
            {
                if (tempCellj->getAdjCell(X_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_PLUS));
                if (tempCellj->getAdjCell(Y_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_PLUS));
                if (tempCellj->getAdjCell(Z_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_PLUS));


            }
            else
                if(y == (ySize-1))
                {
                    if (tempCellj->getAdjCell(X_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_PLUS));
                    if (tempCellj->getAdjCell(Y_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_PLUS));

                }

                else
                    if(z == (zSize-1))
                    {
                        if (tempCellj->getAdjCell(X_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_PLUS));
                        if (tempCellj->getAdjCell(Z_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_PLUS));

                    }
                    else
                        if (tempCellj->getAdjCell(X_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_PLUS));

            tempCellj = tempCellj->getAdjCell(Z_PLUS);

        }
        tempCelli = tempCelli->getAdjCell(Y_PLUS);
    }

    tempCelli = vectorX[1];

    for(int i = 0; i<ySize;i++){
        tempCelli = tempCelli->getAdjCell(Y_PLUS);
    }

    tempCelli = tempCelli->getAdjCell(Z_PLUS);

    for(int x = 1; x < xSize-1; x++) //FACCIA Y+
    {
        tempCellj = tempCelli;

        for(int z = 1; z < zSize; z++)
        {
            if(z== (zSize-1))
            {
                if (tempCellj->getAdjCell(Y_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_PLUS));
                if (tempCellj->getAdjCell(Z_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_PLUS));

            }
            else
                if (tempCellj->getAdjCell(Y_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_PLUS));

            tempCellj = tempCellj->getAdjCell(Z_PLUS);

        }
        tempCelli = tempCelli->getAdjCell(X_PLUS);
    }

    tempCelli = vectorX[1]->getAdjCell(Y_PLUS);

    for(int i=0; i<zSize;i++)
    {
        tempCelli = tempCelli->getAdjCell(Z_PLUS);
    }

    for(int x=1; x < xSize-1;x++) //FACCIA Z+
    {
        tempCellj = tempCelli;

        for(int y=1; y < ySize-1; y++){
            if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));

            tempCellj = tempCellj->getAdjCell(Y_PLUS);
        }
        tempCelli = tempCelli->getAdjCell(x_PLUS);
    }



       for (int x = 0; x < xSize; x++)
       {
           finalCell = vectorX[x];
           tempCelli = finalCell;
           for (int y = 0; y < ySize ; y++)
           {
                   if (y==0) tempCellj = finalCell;

                   for (int z = 0; z < zSize; z++)
                   {
                       tempCelli->setToDelete();
                       tempCelli = tempCelli->getAdjCell(Z_PLUS);
                   }

                   tempCellj = tempCellj->getAdjCell(Y_PLUS);
                   tempCelli = tempCellj;
           }
       }


    for(int x = 0; x < (int)grid.size(); x++)
    {
        for (int y = 0; y < (int) grid[x].size(); y++)
        {
            for (int z = 0; z < (int)grid[x][y].size(); z++)
            {
                if (grid[x][y][z]->getToDelete())
                {
                    eraseGridCell(x, y, z);
                }
            }
            if (grid[x][y].size() == 0)
            {
                grid[x].erase(grid[x].begin() + y);
                y--;
            }
        }

        if (grid[x].size() == 0)
        {
            grid.erase(grid.begin() + x);
            x--;
        }
    }


    std::vector<Pointd> finalBox = boxCoords;
    finalBoxes.push_back(finalBox);



    qDebug() << "volume: " <<volume;

}

void Grid::calculateBox(GridCell* startingCell, GridCell * & finalCell, double &volume, int & xSize, int & ySize, int & zSize, std::vector<Pointd> &boxCoords){

    std::vector<GridCell*> vectorX;
    GridCell* cell = startingCell;
    int minY=0;
    int localY = 0;
    int minZ=0;
    int localZ=0;


    vectorX.push_back(cell);
    if (!(cell->getAdjCell(X_PLUS) == NULL))
    {
        cell = cell->getAdjCell((X_PLUS));
        while (cell->getAdjCell(X_PLUS)){
            vectorX.push_back(cell);
            cell = cell->getAdjCell(X_PLUS);
        }
    }

    for (int x=0; x < (int) vectorX.size(); x++)
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

    for (int x = 0; x < (int) vectorX.size(); x++)
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
        finalCell = startingCell;
        xSize = vectorX.size();
        ySize = minY+1;
        zSize = minZ+1;

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






