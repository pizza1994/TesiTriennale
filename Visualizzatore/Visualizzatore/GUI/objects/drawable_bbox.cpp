#include "drawable_bbox.h"
#include "cylinder.h"
#include "sphere.h"

#include <QDebug>



DrawableBBox::DrawableBBox()
{
    visible = false;
}

DrawableBBox::DrawableBBox(const BoundingBox& b, const double &scale)
{
    box = b;
    scaleFactor = scale;
}

void DrawableBBox::draw() const
{
    if (visible) {

        GLfloat red[3] = {1,0,0};
        double edgesDim = scaleFactor * BB_DIM;

        // Bounding Box Edges
        cylinder(box.getMin(), Pointd(box.getMaxX(),box.getMinY(),box.getMinZ()), edgesDim, edgesDim, red);
        cylinder(box.getMin(), Pointd(box.getMinX(),box.getMinY(),box.getMaxZ()), edgesDim, edgesDim, red);
        cylinder(box.getMin(), Pointd(box.getMinX(),box.getMaxY(),box.getMinZ()), edgesDim, edgesDim, red);
        cylinder(box.getMax(), Pointd(box.getMinX(),box.getMaxY(),box.getMaxZ()), edgesDim, edgesDim, red);
        cylinder(box.getMax(), Pointd(box.getMaxX(),box.getMaxY(),box.getMinZ()), edgesDim, edgesDim, red);
        cylinder(box.getMax(), Pointd(box.getMaxX(),box.getMinY(),box.getMaxZ()), edgesDim, edgesDim, red);
        cylinder(Pointd(box.getMaxX(), box.getMinY(), box.getMinZ()), Pointd(box.getMaxX(),box.getMinY(),box.getMaxZ()), edgesDim, edgesDim, red);
        cylinder(Pointd(box.getMaxX(), box.getMinY(), box.getMinZ()), Pointd(box.getMaxX(),box.getMaxY(),box.getMinZ()), edgesDim, edgesDim, red);
        cylinder(Pointd(box.getMinX(), box.getMinY(), box.getMaxZ()), Pointd(box.getMaxX(),box.getMinY(),box.getMaxZ()), edgesDim, edgesDim, red);
        cylinder(Pointd(box.getMinX(), box.getMaxY(), box.getMaxZ()), Pointd(box.getMinX(),box.getMaxY(),box.getMinZ()), edgesDim, edgesDim, red);
        cylinder(Pointd(box.getMinX(), box.getMaxY(), box.getMaxZ()), Pointd(box.getMinX(),box.getMinY(),box.getMaxZ()), edgesDim, edgesDim, red);
        cylinder(Pointd(box.getMinX(), box.getMaxY(), box.getMinZ()), Pointd(box.getMaxX(),box.getMaxY(),box.getMinZ()), edgesDim, edgesDim, red);
    }

}

Pointd DrawableBBox::sceneCenter() const
{
    return box.center();
}

float DrawableBBox::sceneRadius() const
{
    return box.diag();
}

bool DrawableBBox::isVisible() const
{
    return visible;
}

void DrawableBBox::setScaleFactor(double scale)
{
    scaleFactor = scale;
}

void DrawableBBox::setVisible(bool b)
{
    visible = b;
}

void DrawableBBox::setBoundingBox(BoundingBox bb)
{
    box = bb;
}

