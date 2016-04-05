/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>

#include "lib/common/drawable_object.h"
#include "lib/common/bounding_box.h"

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

        void updateGlCanvas();
        void push_obj(DrawableObject * obj);
        void delete_obj(DrawableObject * obj);
        BoundingBox getFullBoundingBox();
        int getNumberVisibleObjects();

        void set_full_screen(bool);
        void set_background_color(const QColor &);

        int add_manager(QDockWidget *, Qt::DockWidgetArea position);
        QDockWidget *get_manager(unsigned int i);

    private:

        // GUI
        //
        Ui::MainWindow  * ui;
        std::vector<QDockWidget *> managers;

        bool first;
};

#endif // MAINWINDOW_H
