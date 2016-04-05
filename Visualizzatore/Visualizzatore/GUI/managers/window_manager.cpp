/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#include "window_manager.h"
#include "ui_window_manager.h"
#include "GUI/mainwindow.h"

#include <QFileDialog>
#include <QColorDialog>

WindowManager::WindowManager(QWidget *parent) : QDockWidget(parent), ui(new Ui::Window_manager)
{
    ui->setupUi(this);
    mw = parent;
    axis = NULL;
    ((MainWindow*)mw)->updateGlCanvas();

}

WindowManager::~WindowManager()
{
    delete ui;
}

void WindowManager::on_checkBox_stateChanged(int state)
{
    ((MainWindow*)mw)->set_full_screen(state == Qt::Checked);
}

void WindowManager::on_butBackgroundColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    ((MainWindow*)mw)->set_background_color(color);
    ((MainWindow*)mw)->updateGlCanvas();
}

void WindowManager::on_cbShowAxis_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        if (((MainWindow*)mw)->getNumberVisibleObjects() != 0) {
            if (axis == NULL) {
                axis = new DrawableAxis(((MainWindow*)mw)->getFullBoundingBox(), (((MainWindow*)mw)->getFullBoundingBox().diag()/5));
                axis->setVisible(true);
                ((MainWindow*)mw)->push_obj(axis);
            }
            else {
                axis->setBoundingBox(((MainWindow*)mw)->getFullBoundingBox());
                axis->setScaleFactor((((MainWindow*)mw)->getFullBoundingBox().diag()/5));
                axis->setVisible(true);
            }
        }
        else {
            if (axis == NULL) {
                axis = new DrawableAxis(BoundingBox(Pointd(-5,-5,-5), Pointd(5,5,5)), 5);
                axis->setVisible(true);
                ((MainWindow*)mw)->push_obj(axis);
            }
            else {
                axis->setBoundingBox(BoundingBox(Pointd(-5,-5,-5), Pointd(5,5,5)));
                axis->setScaleFactor(5);
                axis->setVisible(true);
            }
        }
    }
    else {
        axis->setVisible(false);
    }
    ((MainWindow*)mw)->updateGlCanvas();
}
