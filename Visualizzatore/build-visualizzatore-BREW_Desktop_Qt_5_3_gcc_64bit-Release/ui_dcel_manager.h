/********************************************************************************
** Form generated from reading UI file 'dcel_manager.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DCEL_MANAGER_H
#define UI_DCEL_MANAGER_H

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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DCEL_manager
{
public:
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer_2;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout_2;
    QPushButton *loadDcelButton;
    QPushButton *cleanDcelButton;
    QPushButton *saveDcelButton;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QCheckBox *cbDrawDCEL;
    QRadioButton *rbPointsDCEL;
    QRadioButton *rbFlatDCEL;
    QRadioButton *rbSmoothDCEL;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *cbWireframeDCEL;
    QCheckBox *cbSegWireframe;
    QSpacerItem *verticalSpacer_2;
    QSlider *hsWireframeWidthDCEL;
    QPushButton *butSetWireframeColorDCEL;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QRadioButton *rbTriangleColorDCEL;
    QRadioButton *rbVertexColorDCEL;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDockWidget *DCEL_manager)
    {
        if (DCEL_manager->objectName().isEmpty())
            DCEL_manager->setObjectName(QStringLiteral("DCEL_manager"));
        DCEL_manager->resize(326, 286);
        DCEL_manager->setMinimumSize(QSize(326, 286));
        DCEL_manager->setMaximumSize(QSize(524287, 286));
        QFont font;
        font.setPointSize(10);
        DCEL_manager->setFont(font);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 5, 3, 1);

        verticalFrame = new QFrame(dockWidgetContents);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalLayout_2 = new QVBoxLayout(verticalFrame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        loadDcelButton = new QPushButton(verticalFrame);
        loadDcelButton->setObjectName(QStringLiteral("loadDcelButton"));
        loadDcelButton->setFont(font);

        verticalLayout_2->addWidget(loadDcelButton);

        cleanDcelButton = new QPushButton(verticalFrame);
        cleanDcelButton->setObjectName(QStringLiteral("cleanDcelButton"));
        cleanDcelButton->setEnabled(false);

        verticalLayout_2->addWidget(cleanDcelButton);

        saveDcelButton = new QPushButton(verticalFrame);
        saveDcelButton->setObjectName(QStringLiteral("saveDcelButton"));
        saveDcelButton->setEnabled(false);

        verticalLayout_2->addWidget(saveDcelButton);


        gridLayout->addWidget(verticalFrame, 0, 3, 1, 1);

        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QStringLiteral("frame"));
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        cbDrawDCEL = new QCheckBox(frame);
        cbDrawDCEL->setObjectName(QStringLiteral("cbDrawDCEL"));
        cbDrawDCEL->setEnabled(false);
        cbDrawDCEL->setChecked(true);

        verticalLayout->addWidget(cbDrawDCEL);

        rbPointsDCEL = new QRadioButton(frame);
        rbPointsDCEL->setObjectName(QStringLiteral("rbPointsDCEL"));
        rbPointsDCEL->setEnabled(false);

        verticalLayout->addWidget(rbPointsDCEL);

        rbFlatDCEL = new QRadioButton(frame);
        rbFlatDCEL->setObjectName(QStringLiteral("rbFlatDCEL"));
        rbFlatDCEL->setEnabled(false);
        rbFlatDCEL->setChecked(true);

        verticalLayout->addWidget(rbFlatDCEL);

        rbSmoothDCEL = new QRadioButton(frame);
        rbSmoothDCEL->setObjectName(QStringLiteral("rbSmoothDCEL"));
        rbSmoothDCEL->setEnabled(false);
        rbSmoothDCEL->setChecked(false);

        verticalLayout->addWidget(rbSmoothDCEL);


        gridLayout->addWidget(frame, 0, 4, 1, 1);

        frame_3 = new QFrame(dockWidgetContents);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        cbWireframeDCEL = new QCheckBox(frame_3);
        cbWireframeDCEL->setObjectName(QStringLiteral("cbWireframeDCEL"));
        cbWireframeDCEL->setEnabled(false);

        verticalLayout_3->addWidget(cbWireframeDCEL);

        cbSegWireframe = new QCheckBox(frame_3);
        cbSegWireframe->setObjectName(QStringLiteral("cbSegWireframe"));
        cbSegWireframe->setEnabled(false);

        verticalLayout_3->addWidget(cbSegWireframe);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        hsWireframeWidthDCEL = new QSlider(frame_3);
        hsWireframeWidthDCEL->setObjectName(QStringLiteral("hsWireframeWidthDCEL"));
        hsWireframeWidthDCEL->setEnabled(false);
        hsWireframeWidthDCEL->setMinimum(1);
        hsWireframeWidthDCEL->setMaximum(4);
        hsWireframeWidthDCEL->setSingleStep(1);
        hsWireframeWidthDCEL->setValue(3);
        hsWireframeWidthDCEL->setTracking(false);
        hsWireframeWidthDCEL->setOrientation(Qt::Horizontal);
        hsWireframeWidthDCEL->setTickPosition(QSlider::TicksBelow);
        hsWireframeWidthDCEL->setTickInterval(1);

        verticalLayout_3->addWidget(hsWireframeWidthDCEL);

        butSetWireframeColorDCEL = new QPushButton(frame_3);
        butSetWireframeColorDCEL->setObjectName(QStringLiteral("butSetWireframeColorDCEL"));
        butSetWireframeColorDCEL->setEnabled(false);
        butSetWireframeColorDCEL->setFont(font);

        verticalLayout_3->addWidget(butSetWireframeColorDCEL);


        gridLayout->addWidget(frame_3, 1, 3, 1, 1);

        frame_2 = new QFrame(dockWidgetContents);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        rbTriangleColorDCEL = new QRadioButton(frame_2);
        rbTriangleColorDCEL->setObjectName(QStringLiteral("rbTriangleColorDCEL"));
        rbTriangleColorDCEL->setEnabled(false);
        rbTriangleColorDCEL->setFont(font);
        rbTriangleColorDCEL->setChecked(true);

        gridLayout_2->addWidget(rbTriangleColorDCEL, 2, 0, 1, 1);

        rbVertexColorDCEL = new QRadioButton(frame_2);
        rbVertexColorDCEL->setObjectName(QStringLiteral("rbVertexColorDCEL"));
        rbVertexColorDCEL->setEnabled(false);
        rbVertexColorDCEL->setFont(font);
        rbVertexColorDCEL->setChecked(false);

        gridLayout_2->addWidget(rbVertexColorDCEL, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 4, 0, 1, 2);


        gridLayout->addWidget(frame_2, 1, 4, 1, 1);

        DCEL_manager->setWidget(dockWidgetContents);

        retranslateUi(DCEL_manager);

        QMetaObject::connectSlotsByName(DCEL_manager);
    } // setupUi

    void retranslateUi(QDockWidget *DCEL_manager)
    {
        DCEL_manager->setWindowTitle(QApplication::translate("DCEL_manager", "DCEL Mesh", 0));
        loadDcelButton->setText(QApplication::translate("DCEL_manager", "Load DCEL", 0));
        cleanDcelButton->setText(QApplication::translate("DCEL_manager", "Clean DCEL", 0));
        saveDcelButton->setText(QApplication::translate("DCEL_manager", "Save DCEL", 0));
        cbDrawDCEL->setText(QApplication::translate("DCEL_manager", "Draw", 0));
        rbPointsDCEL->setText(QApplication::translate("DCEL_manager", "Points", 0));
        rbFlatDCEL->setText(QApplication::translate("DCEL_manager", "Flat", 0));
        rbSmoothDCEL->setText(QApplication::translate("DCEL_manager", "Smooth", 0));
        cbWireframeDCEL->setText(QApplication::translate("DCEL_manager", "Wireframe", 0));
        cbSegWireframe->setText(QApplication::translate("DCEL_manager", "Ch. Wireframe", 0));
        butSetWireframeColorDCEL->setText(QApplication::translate("DCEL_manager", "Set W color", 0));
        rbTriangleColorDCEL->setText(QApplication::translate("DCEL_manager", "T color", 0));
        rbVertexColorDCEL->setText(QApplication::translate("DCEL_manager", "V color", 0));
    } // retranslateUi

};

namespace Ui {
    class DCEL_manager: public Ui_DCEL_manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DCEL_MANAGER_H
