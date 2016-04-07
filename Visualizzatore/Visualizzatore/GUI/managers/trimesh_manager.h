/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#ifndef Trimesh_manager_H
#define Trimesh_manager_H

#include <QDockWidget>
#include <QColor>
#include "lib/trimesh/drawable_trimesh.h"
#include "GUI/objects/drawable_bbox.h"
#include "GUI/objects/drawable_grid.h"

namespace Ui
{
    class Trimesh_manager;
}

class TrimeshManager : public QDockWidget
{
    Q_OBJECT

    public:

        explicit TrimeshManager(QWidget *parent = 0);
        ~TrimeshManager();


    private
    slots:

        void on_butLoadTrimesh_clicked();
        void on_cbWireframe_stateChanged(int state);
        void on_rbPoints_toggled(bool checked);
        void on_rbFlat_toggled(bool checked);
        void on_rbSmooth_toggled(bool checked);
        void on_rbVertexColor_toggled(bool checked);
        void on_rbTriangleColor_toggled(bool checked);
        void on_butSetVColor_clicked();
        void on_butSetTcolor_clicked();
        void on_cbShowBBox_stateChanged(int state);
        void on_cbShowGrid_stateChanged(int state);
        void on_butSetWireframeColor_clicked();
        void on_hsWireframeWidth_valueChanged(int width);
        void on_cbDrawTrimesh_stateChanged(int state);



    private:

        Ui::Trimesh_manager *ui;
        QWidget* mw;
        DrawableTrimesh * t;
        DrawableBBox * visibleBoundingBox;
        DrawableGrid * visibleGrid;
};

#endif // Trimesh_manager_H
