/********************************************************************************
** Form generated from reading UI file 'window_manager.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_MANAGER_H
#define UI_WINDOW_MANAGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window_manager
{
public:
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QPushButton *butBackgroundColor;
    QCheckBox *checkBox;
    QCheckBox *cbShowAxis;

    void setupUi(QDockWidget *Window_manager)
    {
        if (Window_manager->objectName().isEmpty())
            Window_manager->setObjectName(QStringLiteral("Window_manager"));
        Window_manager->resize(237, 165);
        Window_manager->setMinimumSize(QSize(181, 143));
        Window_manager->setMaximumSize(QSize(1070, 200));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout_2 = new QGridLayout(dockWidgetContents);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 1, 1, 1);

        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        butBackgroundColor = new QPushButton(frame);
        butBackgroundColor->setObjectName(QStringLiteral("butBackgroundColor"));
        QFont font;
        font.setPointSize(10);
        butBackgroundColor->setFont(font);

        verticalLayout->addWidget(butBackgroundColor);

        checkBox = new QCheckBox(frame);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setFont(font);
        checkBox->setChecked(false);

        verticalLayout->addWidget(checkBox);

        cbShowAxis = new QCheckBox(frame);
        cbShowAxis->setObjectName(QStringLiteral("cbShowAxis"));
        cbShowAxis->setFont(font);

        verticalLayout->addWidget(cbShowAxis);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);

        Window_manager->setWidget(dockWidgetContents);

        retranslateUi(Window_manager);

        QMetaObject::connectSlotsByName(Window_manager);
    } // setupUi

    void retranslateUi(QDockWidget *Window_manager)
    {
        Window_manager->setWindowTitle(QApplication::translate("Window_manager", "Window", 0));
        butBackgroundColor->setText(QApplication::translate("Window_manager", "Background Color", 0));
        checkBox->setText(QApplication::translate("Window_manager", "Full Screen", 0));
        cbShowAxis->setText(QApplication::translate("Window_manager", "Show Axis", 0));
    } // retranslateUi

};

namespace Ui {
    class Window_manager: public Ui_Window_manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_MANAGER_H
