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
        if ( internal_bbox.getMin().dist( Pointd(internal_bbox.getMinX(), internal_bbox.getMaxY(), internal_bbox.getMinZ()) ) >
            internal_bbox.getMin().dist( Pointd(internal_bbox.getMinX(), internal_bbox.getMinY(), internal_bbox.getMaxZ()) ) )
            length = internal_bbox.getMin().dist( Pointd(internal_bbox.getMinX(), internal_bbox.getMaxY(), internal_bbox.getMinZ()) ) / granularityFactor;

        else
            length = internal_bbox.getMin().dist( Pointd(internal_bbox.getMinX(), internal_bbox.getMinY(), internal_bbox.getMaxZ()) ) / granularityFactor;

    int intLength = length;
    qDebug()<<intLength;
    qDebug()<<length;
    if(length-intLength > 0.4){
        length = intLength + 1;
    }
    else length = intLength;
    qDebug()<<length;

}

double Grid::getLength(){
    return length;
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


void Grid::cleanGrid(DrawableTrimesh &t, Polyhedron &poly)
{
    std::list<Triangle> triangles;

    Tree tree(faces(poly).first, faces(poly).second, poly);

    tree.accelerate_distance_queries();

    for(int i=0; i< (int) grid.size(); i++) //for della intera grid
    {
        for(int j=0; j< (int) grid[i].size(); j++) //for di un livello di cubi
        {
            for (int k=0; k< (int) grid[i][j].size(); k++) //for di una linea di cubi
            {
                if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(0)), point_to_point3(grid[i][j][k]->getVertex(1)))))
                {
                    eraseGridCell(i, j, k);
                }
                else
                    if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(0)), point_to_point3(grid[i][j][k]->getVertex(4)))))
                    {
                        eraseGridCell(i, j, k);
                    }
                    else
                        if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(1)), point_to_point3(grid[i][j][k]->getVertex(5)))))
                        {
                            eraseGridCell(i, j, k);
                        }
                        else
                            if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(4)), point_to_point3(grid[i][j][k]->getVertex(5)))))
                            {
                                eraseGridCell(i, j, k);
                            }
                            else
                                if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(0)), point_to_point3(grid[i][j][k]->getVertex(2)))))
                                {
                                    eraseGridCell(i, j, k);
                                }
                                else
                                    if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(1)), point_to_point3(grid[i][j][k]->getVertex(3)))))
                                    {
                                        eraseGridCell(i, j, k);
                                    }
                                    else
                                        if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(5)), point_to_point3(grid[i][j][k]->getVertex(7)))))
                                        {
                                            eraseGridCell(i, j, k);
                                        }
                                        else
                                            if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(4)), point_to_point3(grid[i][j][k]->getVertex(6)))))
                                            {
                                                eraseGridCell(i, j, k);
                                            }
                                            else
                                                if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(2)), point_to_point3(grid[i][j][k]->getVertex(3)))))
                                                {
                                                    eraseGridCell(i, j, k);
                                                }
                                                else
                                                    if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(2)), point_to_point3(grid[i][j][k]->getVertex(6)))))
                                                    {
                                                        eraseGridCell(i, j, k);
                                                    }
                                                    else
                                                        if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(3)), point_to_point3(grid[i][j][k]->getVertex(7)))))
                                                        {
                                                            eraseGridCell(i, j, k);
                                                        }
                                                        else
                                                            if (tree.do_intersect(K::Segment_3(point_to_point3(grid[i][j][k]->getVertex(6)), point_to_point3(grid[i][j][k]->getVertex(7)))))
                                                            {
                                                                eraseGridCell(i, j, k);
                                                            }
                                                        else
                                                            {
                                                                for (int n = 0; n < 8; n++)
                                                                {
                                                                    if (!pointInside(tree, point_to_point3(grid[i][j][k]->getVertex(n))))
                                                                    {
                                                                        eraseGridCell(i, j, k);
                                                                        n = 8;

                                                                    }
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


    do
    {
        vectorX.push_back(finalCell);
        tempCellj = finalCell;

        for (int x=0; x<xSize; x++)
        {
            vectorX.push_back(tempCellj->getAdjCell(X_PLUS));
            tempCellj = tempCellj->getAdjCell(X_PLUS);
        }

//INIZIO FACCIA Z+
        for(int x = 0; x < xSize; x++){
            tempCelli = vectorX[x];
            tempCellj = tempCelli;
            for (int y = 0; y < ySize ; y++)
            {
                if (tempCellj->getAdjCell(Z_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_MINUS));
                tempCellj = tempCellj->getAdjCell(Y_PLUS);
            }
        }

//INIZIO FACCIA X-
        tempCelli = vectorX[0];

        for (int z = 0; z < zSize; z++)
        {
            tempCellj = tempCelli;

            for (int y = 0 ; y < ySize; y++)
            {
                if (tempCellj->getAdjCell(X_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_MINUS));
                tempCellj = tempCellj->getAdjCell(Y_PLUS);
            }
            tempCelli = tempCelli->getAdjCell(Z_PLUS);
        }


//INIZIO FACCIA Y-

        tempCelli = vectorX[0];

        for(int x = 0; x < xSize; x++)
        {
            tempCellj = tempCelli;

            for (int z = 0; z < zSize; z++ )
            {
                if (tempCellj->getAdjCell(Y_MINUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_MINUS));

                tempCellj = tempCellj->getAdjCell(Z_PLUS);

            }
            tempCelli = tempCelli->getAdjCell(X_PLUS);
        }

//INIZIO FACCIA X+

        tempCelli = vectorX[xSize-1];

        for(int y = 0; y<ySize; y++)
        {
            tempCellj = tempCelli;

            for(int z = 0; z<zSize; z++)
            {
                if (tempCellj->getAdjCell(X_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(X_PLUS));
                tempCellj = tempCellj->getAdjCell(Z_PLUS);

            }
            tempCelli = tempCelli->getAdjCell(Y_PLUS);
        }

//INIZIO FACCIA Y+

        tempCelli = vectorX[0];

        for(int i = 1; i<ySize;i++)
        {
            tempCelli = tempCelli->getAdjCell(Y_PLUS);
        }


        for(int x = 0; x < xSize; x++)
        {
            tempCellj = tempCelli;

            for(int z = 0; z < zSize; z++)
            {
                if (tempCellj->getAdjCell(Y_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Y_PLUS));
                tempCellj = tempCellj->getAdjCell(Z_PLUS);
            }

            tempCelli = tempCelli->getAdjCell(X_PLUS);
        }

        tempCelli = vectorX[0];
        for(int i=1; i<zSize;i++)
        {
            tempCelli = tempCelli->getAdjCell(Z_PLUS);
        }
//INIZIO FACCIA Z+

        for(int x=0; x < xSize;x++)
        {
            tempCellj = tempCelli;

            for(int y=0; y < ySize; y++){
                if (tempCellj->getAdjCell(Z_PLUS) != NULL) nextCells.push_back( tempCellj->getAdjCell(Z_PLUS));

                tempCellj = tempCellj->getAdjCell(Y_PLUS);
            }
            tempCelli = tempCelli->getAdjCell(X_PLUS);
        }


//INIZIO SET_DO_DELETE
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

//DELETE
        for(int x = 0; x < (int)grid.size(); x++)
        {
            for (int y = 0; y < (int) grid[x].size(); y++)
            {
                for (int z = 0; z < (int)grid[x][y].size(); z++)
                {
                    if (grid[x][y][z]->getToDelete())
                    {
                        for (int i = 0; i <(int) nextCells.size(); i++)
                            if (grid[x][y][z] == nextCells[i])
                            {
                                nextCells.erase(nextCells.begin() + i);
                                i--;
                            }
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

        volume = 0;
        vectorX.clear();
//CALCOLO BOX
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

        //qDebug() << "volume: " <<volume;

    }
    while (nextCells.size() > 0 /*&& counter++ < 2*/);
}

void Grid::calculateBox(GridCell* startingCell, GridCell * & finalCell, double &volume, int & xSize, int & ySize, int & zSize, std::vector<Pointd> &boxCoords){

    std::vector<GridCell*> vectorX;
    GridCell* cell = startingCell;
    int minY=0;
    int localY = 0;
    int minZ=0;
    int localZ=0;


    vectorX.push_back(cell);

    if (!(cell->getAdjCell(X_PLUS) == NULL) )
    {
        cell = cell->getAdjCell((X_PLUS));
        while (cell->getAdjCell(X_PLUS)){
            vectorX.push_back(cell);
            cell = cell->getAdjCell(X_PLUS);
        }
        vectorX.push_back(cell);

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
        GridCell * tempCellk = NULL;
        GridCell * tempCelli = NULL;
        GridCell * tempCellj = NULL;
        bool flagFound = false;

        if (nextCells.size() != 0)
        {
            tempCellk = startingCell;


            for (int x = 0; x < (int) vectorX.size(); x++)
            {
                tempCelli = tempCellk;
                for (int y = 0; y < minY+1 ; y++)
                {
                    if (y==0) tempCellj = tempCellk;

                    for (int z = 0; z < minZ+1; z++)
                    {

                        for (GridCell * tempNextCell : nextCells)
                        {

                            if (tempCelli == tempNextCell)
                            {

                                flagFound = true;
                                break;
                            }
                        }
                        tempCelli = tempCelli->getAdjCell(Z_PLUS);
                    }

                    tempCellj = tempCellj->getAdjCell(Y_PLUS);
                    tempCelli = tempCellj;
                }
                tempCellk = tempCellk->getAdjCell(X_PLUS);
            }
        }

        if (nextCells.size() == 0 || flagFound)
        {


            volume = vectorX.size()*(minY+1)*(minZ+1)*pow(length,3 );

            Pointd v0 = startingCell->getVertex(0);
            finalCell = startingCell;
            xSize = vectorX.size();
            ySize = minY+1;
            zSize = minZ+1;

            boxCoords[0] = v0;
            boxCoords[1] = Pointd(v0.x() + length*vectorX.size(), v0.y(), v0.z() );
            boxCoords[2] = Pointd(v0.x() + length*vectorX.size(), v0.y(), v0.z() + length*(minZ+1) );
            boxCoords[3] = Pointd(v0.x(), v0.y(), v0.z() +length*(minZ+1) );
            boxCoords[4] = Pointd(v0.x(), v0.y() +length*(minY+1), v0.z() );
            boxCoords[5] = Pointd(v0.x() +length*vectorX.size(), v0.y() + length*(minY+1), v0.z() );
            boxCoords[6] = Pointd(v0.x() + length*vectorX.size(), v0.y() + length*(minY+1), v0.z() + length*(minZ+1) );
            boxCoords[7] = Pointd(v0.x(), v0.y() + length*(minY+1), v0.z() + length*(minZ+1) );
        }
    }
}






