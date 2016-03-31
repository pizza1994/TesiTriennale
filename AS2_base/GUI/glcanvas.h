/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#ifndef GLCANVAS_H
#define GLCANVAS_H


#include <QGLWidget>
#include <vector>
#include <QGLViewer/qglviewer.h>

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

#include "bbox.h"
#include "drawable_object.h"

using namespace std;

class GLcanvas : public QGLViewer
{
    public:

        GLcanvas(QWidget * parent = NULL);

        void init();
        void draw();
        void clear();
        void fit_scene();
        void set_clear_color(const QColor & color);

        int  push_obj(const DrawableObject * obj);

    private:

        QColor clear_color;
        vector<const DrawableObject *> drawlist;
};

#endif // GLCANVAS_H
