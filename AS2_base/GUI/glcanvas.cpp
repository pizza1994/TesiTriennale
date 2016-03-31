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

void GLcanvas::fit_scene()
{
    vec3d center(0,0,0);
    float radius = 0.0;
    int   count  = 0;

    for(int i=0; i<(int)drawlist.size(); ++i)
    {
        const DrawableObject * obj = drawlist[i];

        center += obj->scene_center();
        radius  = max(radius, obj->scene_radius());
        ++count;
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
