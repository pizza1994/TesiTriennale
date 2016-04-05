/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //window_manager  = NULL;
    first = true;

    //add_window_widget_to_dock();

    //link_gui_to_core();
    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateGlCanvas()
{
    //ui->glCanvas->fit_scene();
    ui->glCanvas->updateGL();
}

void MainWindow::push_obj(DrawableObject *obj)
{
    ui->glCanvas->push_obj(obj);
    ui->glCanvas->fit_scene();
    ui->glCanvas->updateGL();
}

void MainWindow::delete_obj(DrawableObject* obj)
{
    ui->glCanvas->delete_obj(obj);
    ui->glCanvas->fit_scene();
    ui->glCanvas->updateGL();
}

BoundingBox MainWindow::getFullBoundingBox()
{
    return ui->glCanvas->getFullBoundingBox();
}

int MainWindow::getNumberVisibleObjects()
{
    return ui->glCanvas->getNumberVisibleObjects();
}

int MainWindow::add_manager(QDockWidget * m, Qt::DockWidgetArea position)
{
    managers.push_back(m);
    m->show();
    addDockWidget(position, m);
    return managers.size()-1;
}

QDockWidget *MainWindow::get_manager(unsigned int i)
{
    if (i < managers.size()) return managers[i];
    else return NULL;
}

/**
 * WIDGETS SLOTS
 */

void MainWindow::set_full_screen(bool b)
{
    ui->glCanvas->setFullScreen(b);
}

void MainWindow::set_background_color(const QColor & color)
{
    ui->glCanvas->set_clear_color(color);
}
