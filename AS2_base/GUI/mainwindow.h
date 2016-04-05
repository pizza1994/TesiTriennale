/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// GUI
//
#include "window_manager.h"
#include "trimesh_manager.h"

// CORE
//
#include "trimesh/drawable_trimesh.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

        void link_gui_to_core();

    private
    slots:

        void add_window_widget_to_dock();
        void add_trimesh_widget_to_dock();

        void set_full_screen(bool);
        void set_background_color(const QColor &);

        void load_trimesh(const char *);
        void set_flat_shading();
        void set_smooth_shading();
        void set_points_shading();
        void set_draw_mesh(bool);
        void set_wireframe(bool);
        void set_wireframe_width(int);
        void set_enable_vertex_color();
        void set_enable_triangle_color();
        void set_vertex_color(const QColor &);
        void set_triangle_color(const QColor &);
        void set_wireframe_color(const QColor &);
        void set_enable_grid();

    private:

        // GUI
        //
        Ui::MainWindow  * ui;
        Window_manager  * window_manager;
        Trimesh_manager * trimesh_manager;

        // Core
        //
        DrawableTrimesh m;
};

#endif // MAINWINDOW_H
