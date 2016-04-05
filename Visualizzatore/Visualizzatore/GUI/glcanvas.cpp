/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#include "glcanvas.h"

GLcanvas::GLcanvas(QWidget * parent)
{
    setParent(parent);

    clear_color = Qt::white;
}

void GLcanvas::init()
{
    setFPSIsDisplayed(true);
}

void GLcanvas::clear()
{
    drawlist.clear();
}

void GLcanvas::draw()
{
    setBackgroundColor(clear_color);

    for(int i=0; i<(int)drawlist.size(); ++i)
    {
        drawlist[i]->draw();
    }
}

int GLcanvas::push_obj(const DrawableObject * obj)
{
    drawlist.push_back(obj);
    updateGL();

    return drawlist.size();
}

void GLcanvas::delete_obj(const DrawableObject* obj)
{
    vector<const DrawableObject *>::iterator it = std::find(drawlist.begin(), drawlist.end(), obj);
    if (it != drawlist.end()) drawlist.erase(it);
}

void GLcanvas::fit_scene()
{
    Pointd center(0,0,0);
    float radius = 0.0;
    int   count  = 0;

    for(int i=0; i<(int)drawlist.size(); ++i)
    {
        const DrawableObject * obj = drawlist[i];
        if (obj->isVisible()) {
            center += obj->sceneCenter();
            radius  = max(radius, obj->sceneRadius());
            ++count;
        }
    }

    center /= (double)count;

    setSceneCenter(qglviewer::Vec(center.x(), center.y(), center.z()));
    setSceneRadius(radius);

    showEntireScene();       
}

void GLcanvas::set_clear_color(const QColor &color)
{
    clear_color = color;
    updateGL();
}

BoundingBox GLcanvas::getFullBoundingBox()
{
    BoundingBox bb;
    for(int i=0; i<(int)drawlist.size(); ++i)
    {
        const DrawableObject * obj = drawlist[i];
        if (obj->isVisible()) {
            Pointd center = obj->sceneCenter();
            bb.setMin(bb.getMin().min(Pointd(center.x() - obj->sceneRadius(), center.y() - obj->sceneRadius(), center.z() - obj->sceneRadius())));
            bb.setMax(bb.getMax().max(Pointd(center.x() + obj->sceneRadius(), center.y() + obj->sceneRadius(), center.z() + obj->sceneRadius())));
        }
    }
    return bb;
}

int GLcanvas::getNumberVisibleObjects()
{
    int count = 0;
    for(int i=0; i<(int)drawlist.size(); ++i)
    {
        const DrawableObject * obj = drawlist[i];
        if (obj->isVisible()) count++;
    }
    return count;
}
