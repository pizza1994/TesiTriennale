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
                qDebug () << i << " " << j << " " << k;
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
                        qDebug() << "cancellata in " << " " << i << " " << j;
                    }
                    else
                        qDebug() << "Salvata una.";

                    timesIntersected = 0;
                    p = 0;
                }

            }

            if (grid[i][j].size() == 0)
            {
                qDebug() << "Ciao!!";
                grid[i].erase(grid[i].begin() + j);
                j--;
            }
        }

        if (grid[i].size() == 0)
        {
            qDebug() <<"Oiac!!";
            grid.erase(grid.begin() + i);
            i--;
        }

   }


    qDebug() << "Dimensione in X" << " " << grid.size();


}

void Grid::eraseGridCell(int i, int j, int &k)
{
    qDebug() << "Cella posizione:" << i << " " << j << " " << k;

    for (int z=0; z<6; z++)
    {
        if ( grid[i][j][k]->getAdjCell(z) != NULL)
        {
            if (z % 2 == 0)
            {
               // qDebug() << "Attemping to set adjacency of z = " << z << "to z+1";
               // qDebug () << i << " " <<  j << " " << k;
                qDebug() << "Adiacenza Nonnulla in" << " " << z;
                (grid[i][j][k]->getAdjCell(z))->setAdjCell(NULL, z+1);
                qDebug() << "Q";
            }
            else
            {
              //  qDebug() << "Attemping to set adjacency of z = " << z << "to z-1";
               // qDebug () << i << " " <<  j << " " << k;
                qDebug() << "Adiacenza Nonnulla positiva in" << " " << z;
                (grid[i][j][k]->getAdjCell(z))->setAdjCell(NULL, z-1);
                qDebug() << "Q";
            }

        }
        else qDebug() << "Adiacenza Nulla in" << " " << z;
    }

    delete (grid[i][j][k]);
    grid[i][j].erase(grid[i][j].begin()+ k);
    k--;

}
