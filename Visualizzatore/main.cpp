#include "GUI/mainwindow.h"
#include "GUI/managers/trimesh_manager.h"
#include "GUI/managers/window_manager.h"
#include "common.h"
#include <QApplication>

int main(int argc, char *argv[]){
    assert(argc > 0);

    QApplication app(argc, argv);


    MainWindow gui;

    // trimesh manager
    TrimeshManager * tm = new TrimeshManager(&gui);
    TRIMESH_MANAGER_ID = gui.add_manager(tm, Qt::RightDockWidgetArea);

    // window manager
    WindowManager * wm = new WindowManager(&gui);
    WINDOW_MANAGER_ID = gui.add_manager(wm, Qt::RightDockWidgetArea);

    gui.show();

    return app.exec();
}
