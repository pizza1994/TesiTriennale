/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#ifndef Window_manager_H
#define Window_manager_H

#include <QDockWidget>
#include <QColor>
#include <iostream>
#include "GUI/objects/drawable_axis.h"

namespace Ui
{
    class Window_manager;
}

class WindowManager : public QDockWidget
{
        Q_OBJECT

    public:

        explicit WindowManager(QWidget *parent = 0);
        ~WindowManager();

    private slots:

        void on_checkBox_stateChanged(int state);

        void on_butBackgroundColor_clicked();

        void on_cbShowAxis_stateChanged(int arg1);

    private:

        Ui::Window_manager *ui;
        QWidget* mw;
        DrawableAxis * axis;
};

#endif // Window_manager_H
