#ifndef DRAWABLE_BBOX_H
#define DRAWABLE_BBOX_H

#include "lib/common/drawable_object.h"
#include "lib/common/bounding_box.h"

#define BB_DIM 0.005

class DrawableBBox : public DrawableObject
{

    public:
        DrawableBBox();
        DrawableBBox(const BoundingBox &b , const double &scale);

        // Implementation of the
        // DrawableObject interface
        //
        void  draw()         const;
        Pointd sceneCenter() const;
        float sceneRadius() const;
        bool isVisible() const;
        void setVisible(bool b);

        //BBox Settings and Viewing Methods
        //
        void setBoundingBox(BoundingBox bb);
        void setScaleFactor(double scale);

    private:
        double scaleFactor;
        BoundingBox box;
        bool visible;
};

#endif // DRAWABLE_AXIS_H
