/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#include "trimesh_manager.h"
#include "ui_trimesh_manager.h"
#include "GUI/mainwindow.h"
#include <QFileDialog>
#include <QColorDialog>
#include <iostream>
#include "lib/common/importobj.h"


void TrimeshManager::importOBJ(const std::string& fileName, Polyhedrone* polyhedron)
{
    if(polyhedron)
    {
        try
        {
            // Build Polyhedron_3 from the OBJ file.
            BuildCgalPolyhedronFromObj<Polyhedron::HalfedgeDS> _buildPolyhedron(fileName);

            // Calls is_valid at the end. Throws an exception in debug mode if polyhedron is not
            // manifold.
            polyhedron->delegate(_buildPolyhedron);

            // CGAL::Assert_exception is thrown in the debug mode when
            // CGAL::Polyhedron_incremental_builder_3 is destroyed in BuildCgalPolyhedronFromObj.
            // However, in the release mode assertions is disabled and hence no exception is thrown.
            // Thus for uniform error reporting, if the polyhedron is not valid then throw a dummy
            // exception in release mode.
            if(!polyhedron->is_valid())
            {
                throw CGAL::Assertion_exception("", "", "", 0, "");
            }
        }
        catch(const CGAL::Assertion_exception&)
        {
            std::string _msg = "SMeshLib::importOBJ: Error loading " + fileName;
            //throw std::exception(_msg.c_str());
        }
    }
}


TrimeshManager::TrimeshManager(QWidget *parent) : QDockWidget(parent), ui(new Ui::Trimesh_manager)
{
    ui->setupUi(this);
    mw = parent;
    visibleBoundingBox = NULL;
    visibleGrid = NULL;
}

TrimeshManager::~TrimeshManager()
{
    delete ui;
}

void TrimeshManager::on_butLoadTrimesh_clicked()
{
    QString filename = QFileDialog::getOpenFileName(NULL,
                       "Open Trimesh",
                       ".",
                       "OBJ(*.obj)");

    std::cout << "load: " << filename.toStdString() << std::endl;

    if (!filename.isEmpty())
    {
        if(t != NULL){ t->clear(); visibleGrid = NULL; visibleBoundingBox = NULL;}
        t = new DrawableTrimesh(filename.toStdString().c_str());
        p = new Polyhedron();
        importOBJ(filename.toStdString(), p);
        ((MainWindow*)mw)->push_obj(t);
        ((MainWindow*)mw)->updateGlCanvas();

        ui->butSetTcolor->setEnabled(true);
        ui->butSetVColor->setEnabled(true);
        ui->butSetWireframeColor->setEnabled(true);
        ui->cbDrawTrimesh->setEnabled(true);
        ui->cbWireframe->setEnabled(true);
        ui->hsWireframeWidth->setEnabled(true);
        ui->rbFlat->setEnabled(true);
        ui->rbPoints->setEnabled(true);
        ui->rbSmooth->setEnabled(true);
        ui->rbTriangleColor->setEnabled(true);
        ui->rbVertexColor->setEnabled(true);

    }
}

void TrimeshManager::on_cbWireframe_stateChanged(int state)
{
    t->setWireframe(state == Qt::Checked);
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_rbPoints_toggled(bool checked)
{
    if (checked)
        t->setPointsShading();
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_rbFlat_toggled(bool checked)
{
    if (checked)
        t->setFlatShading();
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_rbSmooth_toggled(bool checked)
{
    if (checked)
        t->setSmoothShading();
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_butSetVColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    t->setVertexColor(color.redF(), color.greenF(), color.blueF());
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_butSetTcolor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    t->setTriangleColor(color.redF(), color.greenF(), color.blueF());
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_rbVertexColor_toggled(bool checked)
{
    if (checked)
        t->setEnableVertexColor();
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_rbTriangleColor_toggled(bool checked)
{
    if (checked)
        t->setEnableTriangleColor();
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_butSetWireframeColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    t->setWireframeColor(color.redF(), color.greenF(), color.blueF());
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_cbShowBBox_stateChanged(int state){

    if (state == Qt::Checked) {
        if (((MainWindow*)mw)->getNumberVisibleObjects() != 0) {
            if (visibleBoundingBox == NULL) {
                visibleBoundingBox = new DrawableBBox( t->getBbox() , (((MainWindow*)mw)->getFullBoundingBox().diag()/5) );
                visibleBoundingBox->setVisible(true);
                ((MainWindow*)mw)->push_obj(visibleBoundingBox);
            }
            else {
                visibleBoundingBox->setBoundingBox(t->getBbox());
                visibleBoundingBox->setScaleFactor((((MainWindow*)mw)->getFullBoundingBox().diag()/5));
                visibleBoundingBox->setVisible(true);
            }
        }
        else {
            if (visibleBoundingBox == NULL) {
                visibleBoundingBox = new DrawableBBox(BoundingBox(Pointd(-5,-5,-5), Pointd(5,5,5)) , (((MainWindow*)mw)->getFullBoundingBox().diag()/5));
                visibleBoundingBox->setVisible(true);
                ((MainWindow*)mw)->push_obj(visibleBoundingBox);
            }
            else {
                visibleBoundingBox->setBoundingBox(BoundingBox(Pointd(-5,-5,-5), Pointd(5,5,5)));
                visibleBoundingBox->setScaleFactor((((MainWindow*)mw)->getFullBoundingBox().diag()/5));
                visibleBoundingBox->setVisible(true);
            }
        }
    }
    else {
        visibleBoundingBox->setVisible(false);
    }
    ((MainWindow*)mw)->updateGlCanvas();

}

void TrimeshManager::on_hsWireframeWidth_valueChanged(int width)
{
    t->setWireframeWidth(width);
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_cbDrawTrimesh_stateChanged(int state)
{
    t->setVisible(state == Qt::Checked);
    ((MainWindow*)mw)->updateGlCanvas();
}

void TrimeshManager::on_cbShowGrid_stateChanged(int state)
{
    if (state == Qt::Checked)
    {
            visibleGrid->setVisibleGrid(true);
            ((MainWindow*)mw)->push_obj(visibleGrid);

    }
    else
    {
        visibleGrid->setVisibleGrid(false);
        ((MainWindow*)mw)->push_obj(visibleGrid);
    }
    ((MainWindow*)mw)->updateGlCanvas();

}

void TrimeshManager::on_sbGranularity_valueChanged(int value){
    granularity = value;
}



void TrimeshManager::on_cbShowMaxBox_stateChanged(int state){

    if (state == Qt::Checked)
    {
        if (((MainWindow*)mw)->getNumberVisibleObjects() != 0)
        {
            if (visibleGrid == NULL)
            {
                visibleGrid = new DrawableGrid( t->getBbox() , granularity, *t, *p);
                visibleGrid->setVisible(true);
                visibleGrid->setVisibleGrid(false);
                ((MainWindow*)mw)->push_obj(visibleGrid);
            }
            else
            {
                visibleGrid = new DrawableGrid( t->getBbox() , granularity, *t, *p);
                visibleGrid->setVisible(true);
                visibleGrid->setVisibleGrid(false);
                ((MainWindow*)mw)->push_obj(visibleGrid);
            }
        }
        else { //TO complete

        }

    }
    else{
        visibleGrid->setVisible(false);
    }
    ((MainWindow*)mw)->updateGlCanvas();
}
