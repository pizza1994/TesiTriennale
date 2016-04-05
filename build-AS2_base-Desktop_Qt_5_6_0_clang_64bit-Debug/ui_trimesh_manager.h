/********************************************************************************
** Form generated from reading UI file 'trimesh_manager.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRIMESH_MANAGER_H
#define UI_TRIMESH_MANAGER_H

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

class Ui_Trimesh_manager
{
public:
    QWidget *dockWidgetContents;
    QGridLayout *gridLayout;
    QFrame *verticalFrame;
    QVBoxLayout *verticalLayout_2;
    QPushButton *butLoadTrimesh;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QRadioButton *rbTriangleColor;
    QRadioButton *rbVertexColor;
    QSpacerItem *verticalSpacer_3;
    QPushButton *butSetTcolor;
    QPushButton *butSetVColor;
    QPushButton *addGridButton;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QCheckBox *cbDrawTrimesh;
    QRadioButton *rbPoints;
    QRadioButton *rbFlat;
    QRadioButton *rbSmooth;
    QSpacerItem *horizontalSpacer_2;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *cbWireframe;
    QSlider *hsWireframeWidth;
    QPushButton *butSetWireframeColor;
    QPushButton *butShowBBox;
    QSpacerItem *verticalSpacer;

    void setupUi(QDockWidget *Trimesh_manager)
    {
        if (Trimesh_manager->objectName().isEmpty())
            Trimesh_manager->setObjectName(QStringLiteral("Trimesh_manager"));
        Trimesh_manager->resize(438, 443);
        Trimesh_manager->setMinimumSize(QSize(438, 330));
        Trimesh_manager->setMaximumSize(QSize(524287, 9999));
        QFont font;
        font.setPointSize(10);
        Trimesh_manager->setFont(font);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        gridLayout = new QGridLayout(dockWidgetContents);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalFrame = new QFrame(dockWidgetContents);
        verticalFrame->setObjectName(QStringLiteral("verticalFrame"));
        verticalLayout_2 = new QVBoxLayout(verticalFrame);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        butLoadTrimesh = new QPushButton(verticalFrame);
        butLoadTrimesh->setObjectName(QStringLiteral("butLoadTrimesh"));
        butLoadTrimesh->setFont(font);

        verticalLayout_2->addWidget(butLoadTrimesh);


        gridLayout->addWidget(verticalFrame, 0, 3, 1, 1);

        frame_2 = new QFrame(dockWidgetContents);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        rbTriangleColor = new QRadioButton(frame_2);
        rbTriangleColor->setObjectName(QStringLiteral("rbTriangleColor"));
        rbTriangleColor->setFont(font);

        gridLayout_2->addWidget(rbTriangleColor, 2, 0, 1, 1);

        rbVertexColor = new QRadioButton(frame_2);
        rbVertexColor->setObjectName(QStringLiteral("rbVertexColor"));
        rbVertexColor->setFont(font);
        rbVertexColor->setChecked(true);

        gridLayout_2->addWidget(rbVertexColor, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_3, 5, 0, 1, 2);

        butSetTcolor = new QPushButton(frame_2);
        butSetTcolor->setObjectName(QStringLiteral("butSetTcolor"));
        butSetTcolor->setFont(font);

        gridLayout_2->addWidget(butSetTcolor, 2, 1, 1, 1);

        butSetVColor = new QPushButton(frame_2);
        butSetVColor->setObjectName(QStringLiteral("butSetVColor"));
        butSetVColor->setFont(font);

        gridLayout_2->addWidget(butSetVColor, 0, 1, 1, 1);

        addGridButton = new QPushButton(frame_2);
        addGridButton->setObjectName(QStringLiteral("addGridButton"));

        gridLayout_2->addWidget(addGridButton, 3, 0, 1, 1);


        gridLayout->addWidget(frame_2, 1, 4, 1, 1);

        frame = new QFrame(dockWidgetContents);
        frame->setObjectName(QStringLiteral("frame"));
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        cbDrawTrimesh = new QCheckBox(frame);
        cbDrawTrimesh->setObjectName(QStringLiteral("cbDrawTrimesh"));
        cbDrawTrimesh->setChecked(true);

        verticalLayout->addWidget(cbDrawTrimesh);

        rbPoints = new QRadioButton(frame);
        rbPoints->setObjectName(QStringLiteral("rbPoints"));

        verticalLayout->addWidget(rbPoints);

        rbFlat = new QRadioButton(frame);
        rbFlat->setObjectName(QStringLiteral("rbFlat"));

        verticalLayout->addWidget(rbFlat);

        rbSmooth = new QRadioButton(frame);
        rbSmooth->setObjectName(QStringLiteral("rbSmooth"));
        rbSmooth->setChecked(true);

        verticalLayout->addWidget(rbSmooth);


        gridLayout->addWidget(frame, 0, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 5, 3, 1);

        frame_3 = new QFrame(dockWidgetContents);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setFrameShape(QFrame::NoFrame);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_3);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        cbWireframe = new QCheckBox(frame_3);
        cbWireframe->setObjectName(QStringLiteral("cbWireframe"));

        verticalLayout_3->addWidget(cbWireframe);

        hsWireframeWidth = new QSlider(frame_3);
        hsWireframeWidth->setObjectName(QStringLiteral("hsWireframeWidth"));
        hsWireframeWidth->setMinimum(1);
        hsWireframeWidth->setMaximum(4);
        hsWireframeWidth->setTracking(false);
        hsWireframeWidth->setOrientation(Qt::Horizontal);
        hsWireframeWidth->setTickPosition(QSlider::TicksBelow);
        hsWireframeWidth->setTickInterval(1);

        verticalLayout_3->addWidget(hsWireframeWidth);

        butSetWireframeColor = new QPushButton(frame_3);
        butSetWireframeColor->setObjectName(QStringLiteral("butSetWireframeColor"));
        butSetWireframeColor->setFont(font);

        verticalLayout_3->addWidget(butSetWireframeColor);

        butShowBBox = new QPushButton(frame_3);
        butShowBBox->setObjectName(QStringLiteral("butShowBBox"));

        verticalLayout_3->addWidget(butShowBBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        gridLayout->addWidget(frame_3, 1, 3, 1, 1);

        Trimesh_manager->setWidget(dockWidgetContents);

        retranslateUi(Trimesh_manager);

        QMetaObject::connectSlotsByName(Trimesh_manager);
    } // setupUi

    void retranslateUi(QDockWidget *Trimesh_manager)
    {
        Trimesh_manager->setWindowTitle(QApplication::translate("Trimesh_manager", "Triangle Mesh", 0));
        butLoadTrimesh->setText(QApplication::translate("Trimesh_manager", "Load TriMesh", 0));
        rbTriangleColor->setText(QApplication::translate("Trimesh_manager", "T color", 0));
        rbVertexColor->setText(QApplication::translate("Trimesh_manager", "V color", 0));
        butSetTcolor->setText(QApplication::translate("Trimesh_manager", "Set", 0));
        butSetVColor->setText(QApplication::translate("Trimesh_manager", "Set", 0));
        addGridButton->setText(QApplication::translate("Trimesh_manager", "Add Grid", 0));
        cbDrawTrimesh->setText(QApplication::translate("Trimesh_manager", "Draw", 0));
        rbPoints->setText(QApplication::translate("Trimesh_manager", "Points", 0));
        rbFlat->setText(QApplication::translate("Trimesh_manager", "Flat", 0));
        rbSmooth->setText(QApplication::translate("Trimesh_manager", "Smooth", 0));
        cbWireframe->setText(QApplication::translate("Trimesh_manager", "Wireframe", 0));
        butSetWireframeColor->setText(QApplication::translate("Trimesh_manager", "Set W color", 0));
        butShowBBox->setText(QApplication::translate("Trimesh_manager", "Show BBox", 0));
    } // retranslateUi

};

namespace Ui {
    class Trimesh_manager: public Ui_Trimesh_manager {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRIMESH_MANAGER_H
