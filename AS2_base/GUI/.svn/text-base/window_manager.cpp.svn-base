/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#include "window_manager.h"
#include "ui_window_manager.h"

#include <QFileDialog>
#include <QColorDialog>

Window_manager::Window_manager(QWidget *parent) : QDockWidget(parent), ui(new Ui::Window_manager)
{
    ui->setupUi(this);
}

Window_manager::~Window_manager()
{
    delete ui;
}

void Window_manager::on_checkBox_stateChanged(int state)
{
    emit set_full_screen(state == Qt::Checked);
}

void Window_manager::on_butBackgroundColor_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, this);

    emit set_background_color(color);
}
