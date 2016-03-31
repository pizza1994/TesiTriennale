/**
 @author    Marco Livesu (marco.livesu@gmail.com)
 @copyright Marco Livesu 2014.
*/

#ifndef Window_manager_H
#define Window_manager_H

#include <QDockWidget>
#include <QColor>
#include <iostream>

namespace Ui
{
    class Window_manager;
}

class Window_manager : public QDockWidget
{
        Q_OBJECT

    public:

        explicit Window_manager(QWidget *parent = 0);
        ~Window_manager();

    signals:

        void set_full_screen (bool);
        void set_background_color(const QColor &);

    private slots:

        void on_checkBox_stateChanged(int state);

        void on_butBackgroundColor_clicked();

    private:

        Ui::Window_manager *ui;
};

#endif // Window_manager_H
