#ifndef DRAWABLE_GRID_H
#define DRAWABLE_GRID_H
#include "lib/common/drawable_object.h"
#include "grid.h"
#include <QColor>
#include <QDebug>
#include "GUI/objects/sphere.h"
#include "GUI/objects/cylinder.h"
#include "lib/hexmesh/mesh.h"
#include "lib/common/importobj.h"



class DrawableGrid : public Grid ,
                        public DrawableObject
{
    public:
         DrawableGrid();
         DrawableGrid(const BoundingBox&  b, const int granularityFactor, DrawableTrimesh &t, Polyhedron &p);

         // Implementation of the
         // DrawableObject interface
         //
         void  draw()        const;
         Pointd sceneCenter() const;
         float sceneRadius() const;
         bool isVisible() const;
         void setVisible(bool b);
         void setVisibleGrid(bool b);
         bool getVisibleGrid();

         void importOBJ(const std::string &fileName, Polyhedrone *polyhedron);
private:
         bool visible;
         bool visibleGrid;


};

#endif // DRAWABLE_GRID_H
