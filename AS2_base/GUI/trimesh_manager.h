/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#ifndef Trimesh_manager_H
#define Trimesh_manager_H

#include <QDockWidget>
#include <QColor>

namespace Ui
{
    class Trimesh_manager;
}

class Trimesh_manager : public QDockWidget
{
    Q_OBJECT

    public:

        explicit Trimesh_manager(QWidget *parent = 0);
        ~Trimesh_manager();

    signals:

        void load_trimesh(const char *);
        void set_wireframe(bool);
        void set_draw_mesh(bool);
        void set_flat_shading();
        void set_smooth_shading();
        void set_points_shading();
        void set_enable_vertex_color();
        void set_enable_triangle_color();
        void set_wireframe_width(int width);
        void set_vertex_color(const QColor &);
        void set_triangle_color(const QColor &);
        void set_wireframe_color(const QColor &);



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
        void on_butSetWireframeColor_clicked();
        void on_hsWireframeWidth_valueChanged(int width);
        void on_cbDrawTrimesh_stateChanged(int state);
        void on_butShowBBox_clicked();

    private:

        Ui::Trimesh_manager *ui;
};

#endif // Trimesh_manager_H
