#ifndef DRAWABLE_AXIS_H
#define DRAWABLE_AXIS_H

#include "lib/common/drawable_object.h"
#include "lib/common/bounding_box.h"

#define AXIS_DIM 0.005
#define ARROW_RADIUS 0.007
#define ARROW_LENGTH 0.04

class DrawableAxis : public DrawableObject
{
    public:
        DrawableAxis();
        DrawableAxis(const BoundingBox &b, const double &scale);

        // Implementation of the
        // DrawableObject interface
        //
        void  draw()         const;
        Pointd sceneCenter() const;
        float sceneRadius() const;
        bool isVisible() const;
        void setVisible(bool b);

        void setScaleFactor(double scale);
        void setBoundingBox(BoundingBox bb);
        void reset();

    private:
        double scaleFactor;
        BoundingBox box;
        bool visible;
};

#endif // DRAWABLE_AXIS_H
