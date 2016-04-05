/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#include "trimesh_manager.h"
#include "ui_trimesh_manager.h"

#include <QFileDialog>
#include <QColorDialog>
#include <iostream>

Trimesh_manager::Trimesh_manager(QWidget *parent) : QDockWidget(parent), ui(new Ui::Trimesh_manager)
{
    ui->setupUi(this);
}

Trimesh_manager::~Trimesh_manager()
{
    delete ui;
}

void Trimesh_manager::on_butLoadTrimesh_clicked()
{
    QString filename = QFileDialog::getOpenFileName(NULL,
                       "Open Trimesh",
                       ".",
                       "OBJ(*.obj)");

    std::cout << "load: " << filename.toStdString() << std::endl;

    if (!filename.isEmpty())
    {
        emit load_trimesh(filename.toStdString().c_str());
    }
}

void Trimesh_manager::on_cbWireframe_stateChanged(int state)
{
    emit set_wireframe(state == Qt::Checked);
}

void Trimesh_manager::on_rbPoints_toggled(bool checked)
{
    if (checked) emit set_points_shading();
}

void Trimesh_manager::on_rbFlat_toggled(bool checked)
{
    if (checked) emit set_flat_shading();
}

void Trimesh_manager::on_rbSmooth_toggled(bool checked)
{
    if (checked) emit set_smooth_shading();
}

void Trimesh_manager::on_butSetVColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    emit set_vertex_color(color);
}

void Trimesh_manager::on_addGridButton_clicked()
{
    emit set_enable_grid();
}

void Trimesh_manager::on_butSetTcolor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    emit set_triangle_color(color);
}

void Trimesh_manager::on_rbVertexColor_toggled(bool checked)
{
    if (checked) emit set_enable_vertex_color();
}

void Trimesh_manager::on_rbTriangleColor_toggled(bool checked)
{
    if (checked) emit set_enable_triangle_color();
}

void Trimesh_manager::on_butSetWireframeColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    emit set_wireframe_color(color);
}

void Trimesh_manager::on_hsWireframeWidth_valueChanged(int width)
{
    emit set_wireframe_width(width);
}

void Trimesh_manager::on_cbDrawTrimesh_stateChanged(int state)
{
    emit set_draw_mesh(state == Qt::Checked);
}

void Trimesh_manager::on_butShowBBox_clicked(){
    std::cout <<"button clicked";
}
