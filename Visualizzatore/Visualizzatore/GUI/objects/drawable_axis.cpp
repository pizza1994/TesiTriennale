#include "drawable_axis.h"
#include "cylinder.h"
#include "sphere.h"

#include <QDebug>

DrawableAxis::DrawableAxis()
{
    visible = false;
}

DrawableAxis::DrawableAxis(const BoundingBox& b, const double &scale)
{
    scaleFactor = scale;

    box = b;
}

void DrawableAxis::draw() const
{
    if (visible) {
        float axis_dim = AXIS_DIM * scaleFactor;
        float arrow_radius = ARROW_RADIUS * scaleFactor;
        float arrow_length = ARROW_LENGTH * scaleFactor;
        GLfloat red[3] = {1,0,0};
        GLfloat green[3] = {0,1,0};
        GLfloat blue[3] = {0,0,1};

        // assi cartesiani
        cylinder(Pointd(0,0,0), Pointd(box.getMaxX(),0,0), axis_dim, axis_dim, red); // x
        cylinder(Pointd(box.getMaxX(),0,0), Pointd(box.getMaxX()+arrow_length,0,0),
                 axis_dim+arrow_radius, 0, red); // punta di x

        cylinder(Pointd(0,0,0), Pointd(0,box.getMaxY(),0), axis_dim, axis_dim, green); // y
        cylinder(Pointd(0,box.getMaxY(),0), Pointd(0,box.getMaxY()+arrow_length,0),
                 axis_dim+arrow_radius, 0, green); // punti di y

        cylinder(Pointd(0,0,0), Pointd(0,0,box.getMaxZ()), axis_dim, axis_dim, blue); // z
        cylinder(Pointd(0,0,box.getMaxZ()), Pointd(0,0,box.getMaxZ()+arrow_length),
                 axis_dim+arrow_radius, 0, blue); // punta di z
    }

}

Pointd DrawableAxis::sceneCenter() const
{
    return box.center();
}

float DrawableAxis::sceneRadius() const
{
    return box.diag();
}

bool DrawableAxis::isVisible() const
{
    return visible;
}

void DrawableAxis::setVisible(bool b)
{
    visible = b;
}

void DrawableAxis::setScaleFactor(double scale)
{
    scaleFactor = scale;
}

void DrawableAxis::setBoundingBox(BoundingBox bb)
{
    box = bb;
}

void DrawableAxis::reset()
{
    scaleFactor = 0;
    box.reset();
}
