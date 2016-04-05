/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "GUI/glcanvas.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionTrimesh;
    QAction *actionSkel;
    QAction *actionWindow;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    GLcanvas *glCanvas;
    QMenuBar *menuBar;
    QMenu *menuWidgets;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setBaseSize(QSize(800, 600));
        actionTrimesh = new QAction(MainWindow);
        actionTrimesh->setObjectName(QStringLiteral("actionTrimesh"));
        actionSkel = new QAction(MainWindow);
        actionSkel->setObjectName(QStringLiteral("actionSkel"));
        actionWindow = new QAction(MainWindow);
        actionWindow->setObjectName(QStringLiteral("actionWindow"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        glCanvas = new GLcanvas(centralWidget);
        glCanvas->setObjectName(QStringLiteral("glCanvas"));

        verticalLayout->addWidget(glCanvas);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        menuWidgets = new QMenu(menuBar);
        menuWidgets->setObjectName(QStringLiteral("menuWidgets"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuWidgets->menuAction());
        menuWidgets->addAction(actionWindow);
        menuWidgets->addAction(actionTrimesh);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QString());
        actionTrimesh->setText(QApplication::translate("MainWindow", "Trimesh", 0));
        actionSkel->setText(QApplication::translate("MainWindow", "Skel", 0));
        actionWindow->setText(QApplication::translate("MainWindow", "Window", 0));
        menuWidgets->setTitle(QApplication::translate("MainWindow", "Widgets", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
