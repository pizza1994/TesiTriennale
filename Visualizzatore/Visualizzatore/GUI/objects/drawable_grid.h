#ifndef DRAWABLE_GRID_H
#define DRAWABLE_GRID_H
#include "lib/common/drawable_object.h"
#include "grid.h"
#include <QColor>
#include <QDebug>


class DrawableGrid : public Grid ,
                        public DrawableObject
{
    public:
         DrawableGrid();
         DrawableGrid(const BoundingBox&  b, const int granularityFactor, DrawableTrimesh &t);

         // Implementation of the
         // DrawableObject interface
         //
         void  draw()        const;
         Pointd sceneCenter() const;
         float sceneRadius() const;
         bool isVisible() const;
         void setVisible(bool b);

    private:
         bool visible;


};

#endif // DRAWABLE_GRID_H
