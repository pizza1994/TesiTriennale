/********************************************************************************
** Form generated from reading UI file 'mesh_stack_manager.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESH_STACK_MANAGER_H
#define UI_MESH_STACK_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeshStack_manager
{
public:
    QWidget *dockWidgetContents;
    QListWidget *listWidget;

    void setupUi(QDockWidget *MeshStack_manager)
    {
        if (MeshStack_manager->objectName().isEmpty())
            MeshStack_manager->setObjectName(QStringLiteral("MeshStack_manager"));
        MeshStack_manager->resize(453, 416);
        MeshStack_manager->setMinimumSize(QSize(150, 41));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        listWidget = new QListWidget(dockWidgetContents);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(20, 10, 171, 371));
        MeshStack_manager->setWidget(dockWidgetContents);

        retranslateUi(MeshStack_manager);

        QMetaObject::connectSlotsByName(MeshStack_manager);
    } // setupUi

    void retranslateUi(QDockWidget *MeshStack_manager)
    {
        MeshStack_manager->setWindowTitle(QApplication::translate("MeshStack_manager", "Mesh Stack", 0));
    } // retranslateUi

};

namespace Ui {
    class MeshStack_manager: public Ui_MeshStack_manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESH_STACK_MANAGER_H
