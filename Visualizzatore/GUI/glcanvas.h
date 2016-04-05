/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#ifndef GLCANVAS_H
#define GLCANVAS_H

#include <QGLViewer/qglviewer.h>
#include <QGLWidget>
#include <vector>

#ifdef __APPLE__
#include <gl.h>
#else
#include <GL/gl.h>
#endif

#include "lib/common/bounding_box.h"
#include "lib/common/drawable_object.h"

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
        BoundingBox getFullBoundingBox();
        int getNumberVisibleObjects();

        int  push_obj(const DrawableObject * obj);
        void delete_obj(const DrawableObject* obj);

    private:

        QColor clear_color;
        vector<const DrawableObject *> drawlist;
};

#endif // GLCANVAS_H
