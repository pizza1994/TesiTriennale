/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    window_manager  = NULL;
    trimesh_manager = NULL;

    add_window_widget_to_dock();
    add_trimesh_widget_to_dock();

    link_gui_to_core();
    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::link_gui_to_core()
{
    connect(ui->actionWindow,   SIGNAL(triggered()),
            this,               SLOT(add_window_widget_to_dock()));

    connect(ui->actionTrimesh,  SIGNAL(triggered()),
            this,               SLOT(add_trimesh_widget_to_dock()));

    connect(window_manager,     SIGNAL(set_full_screen(bool)),
            this,               SLOT  (set_full_screen(bool)));

    connect(window_manager,     SIGNAL(set_background_color(const QColor &)),
            this,               SLOT  (set_background_color(const QColor &)));

    connect(trimesh_manager,    SIGNAL(set_draw_mesh(bool)),
            this,               SLOT  (set_draw_mesh(bool)));

    connect(trimesh_manager,    SIGNAL(load_trimesh(const char *)),
            this,               SLOT  (load_trimesh(const char *)));

    connect(trimesh_manager,    SIGNAL(set_wireframe(bool)),
            this,               SLOT  (set_wireframe(bool)));

    connect(trimesh_manager,    SIGNAL(set_flat_shading()),
            this,               SLOT  (set_flat_shading()));

    connect(trimesh_manager,    SIGNAL(set_smooth_shading()),
            this,               SLOT  (set_smooth_shading()));

    connect(trimesh_manager,    SIGNAL(set_points_shading()),
            this,               SLOT  (set_points_shading()));

    connect(trimesh_manager,    SIGNAL(set_enable_vertex_color()),
            this,               SLOT  (set_enable_vertex_color()));

    connect(trimesh_manager,    SIGNAL(set_enable_grid()),
            this,               SLOT  (set_enable_grid()));

    connect(trimesh_manager,    SIGNAL(set_enable_triangle_color()),
            this,               SLOT  (set_enable_triangle_color()));

    connect(trimesh_manager,    SIGNAL(set_vertex_color(const QColor &)),
            this,               SLOT  (set_vertex_color(const QColor &)));

    connect(trimesh_manager,    SIGNAL(set_triangle_color(const QColor &)),
            this,               SLOT  (set_triangle_color(const QColor &)));

    connect(trimesh_manager,    SIGNAL(set_wireframe_color(const QColor &)),
            this,               SLOT  (set_wireframe_color(const QColor &)));

    connect(trimesh_manager,    SIGNAL(set_wireframe_width(int)),
            this,               SLOT  (set_wireframe_width(int)));

    /*connect(trimesh_manager,    SIGNAL(createBoundingBox()),
            this,               SLOT  (createBoundingBox()));*/
}

/*
 * SLOTS
*/

void MainWindow::load_trimesh(const char *filename)
{
    m = DrawableTrimesh(filename);

    ui->glCanvas->clear();
    ui->glCanvas->push_obj(&m);
    ui->glCanvas->fit_scene();
}

void MainWindow::set_full_screen(bool b)
{
    ui->glCanvas->setFullScreen(b);
}

void MainWindow::set_wireframe(bool b)
{
    m.set_wireframe(b);
    ui->glCanvas->updateGL();
}

void MainWindow::set_flat_shading()
{
    m.set_flat_shading();
    ui->glCanvas->updateGL();
}

void MainWindow::set_smooth_shading()
{
    m.set_smooth_shading();
    ui->glCanvas->updateGL();
}

void MainWindow::set_points_shading()
{
    m.set_points_shading();
    ui->glCanvas->updateGL();
}

void MainWindow::set_background_color(const QColor & color)
{
    ui->glCanvas->set_clear_color(color);
}

void MainWindow::set_vertex_color(const QColor & color)
{
    m.set_v_color(color.redF(), color.greenF(), color.blueF());
    ui->glCanvas->updateGL();
}

void MainWindow::set_triangle_color(const QColor & color)
{
    m.set_t_color(color.redF(), color.greenF(), color.blueF());
    ui->glCanvas->updateGL();
}

void MainWindow::set_wireframe_color(const QColor & color)
{
    m.set_wireframe_color(color.redF(), color.greenF(), color.blueF());
    ui->glCanvas->updateGL();
}

void MainWindow::set_enable_vertex_color()
{
    m.set_enable_vertex_color();
    ui->glCanvas->updateGL();
}


void MainWindow::set_enable_grid()
{
    m.set_enable_grid();
    ui->glCanvas->updateGL();
}

void MainWindow::set_enable_triangle_color()
{
    m.set_enable_triangle_color();
    ui->glCanvas->updateGL();
}

void MainWindow::set_wireframe_width(int width)
{
    m.set_wireframe_width(width);
    ui->glCanvas->updateGL();
}

void MainWindow::set_draw_mesh(bool b)
{
    m.set_draw_mesh(b);
    ui->glCanvas->updateGL();
}

void MainWindow::add_window_widget_to_dock()
{
    if (!window_manager)
    {
        window_manager = new Window_manager(this);
    }
    window_manager->show();
    addDockWidget(Qt::RightDockWidgetArea, window_manager);
}

void MainWindow::add_trimesh_widget_to_dock()
{
    if (!trimesh_manager)
    {
        trimesh_manager = new Trimesh_manager(this);
    }
    trimesh_manager->show();
    addDockWidget(Qt::RightDockWidgetArea, trimesh_manager);
}
