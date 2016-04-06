/****************************************************************************
** Meta object code from reading C++ file 'trimesh_manager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Visualizzatore/GUI/managers/trimesh_manager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trimesh_manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TrimeshManager_t {
    QByteArrayData data[18];
    char stringdata0[370];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrimeshManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrimeshManager_t qt_meta_stringdata_TrimeshManager = {
    {
QT_MOC_LITERAL(0, 0, 14), // "TrimeshManager"
QT_MOC_LITERAL(1, 15, 25), // "on_butLoadTrimesh_clicked"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 27), // "on_cbWireframe_stateChanged"
QT_MOC_LITERAL(4, 70, 5), // "state"
QT_MOC_LITERAL(5, 76, 19), // "on_rbPoints_toggled"
QT_MOC_LITERAL(6, 96, 7), // "checked"
QT_MOC_LITERAL(7, 104, 17), // "on_rbFlat_toggled"
QT_MOC_LITERAL(8, 122, 19), // "on_rbSmooth_toggled"
QT_MOC_LITERAL(9, 142, 24), // "on_rbVertexColor_toggled"
QT_MOC_LITERAL(10, 167, 26), // "on_rbTriangleColor_toggled"
QT_MOC_LITERAL(11, 194, 23), // "on_butSetVColor_clicked"
QT_MOC_LITERAL(12, 218, 23), // "on_butSetTcolor_clicked"
QT_MOC_LITERAL(13, 242, 26), // "on_cbShowBBox_stateChanged"
QT_MOC_LITERAL(14, 269, 31), // "on_butSetWireframeColor_clicked"
QT_MOC_LITERAL(15, 301, 32), // "on_hsWireframeWidth_valueChanged"
QT_MOC_LITERAL(16, 334, 5), // "width"
QT_MOC_LITERAL(17, 340, 29) // "on_cbDrawTrimesh_stateChanged"

    },
    "TrimeshManager\0on_butLoadTrimesh_clicked\0"
    "\0on_cbWireframe_stateChanged\0state\0"
    "on_rbPoints_toggled\0checked\0"
    "on_rbFlat_toggled\0on_rbSmooth_toggled\0"
    "on_rbVertexColor_toggled\0"
    "on_rbTriangleColor_toggled\0"
    "on_butSetVColor_clicked\0on_butSetTcolor_clicked\0"
    "on_cbShowBBox_stateChanged\0"
    "on_butSetWireframeColor_clicked\0"
    "on_hsWireframeWidth_valueChanged\0width\0"
    "on_cbDrawTrimesh_stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrimeshManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x08 /* Private */,
       3,    1,   80,    2, 0x08 /* Private */,
       5,    1,   83,    2, 0x08 /* Private */,
       7,    1,   86,    2, 0x08 /* Private */,
       8,    1,   89,    2, 0x08 /* Private */,
       9,    1,   92,    2, 0x08 /* Private */,
      10,    1,   95,    2, 0x08 /* Private */,
      11,    0,   98,    2, 0x08 /* Private */,
      12,    0,   99,    2, 0x08 /* Private */,
      13,    1,  100,    2, 0x08 /* Private */,
      14,    0,  103,    2, 0x08 /* Private */,
      15,    1,  104,    2, 0x08 /* Private */,
      17,    1,  107,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void TrimeshManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrimeshManager *_t = static_cast<TrimeshManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_butLoadTrimesh_clicked(); break;
        case 1: _t->on_cbWireframe_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_rbPoints_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_rbFlat_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_rbSmooth_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_rbVertexColor_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_rbTriangleColor_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_butSetVColor_clicked(); break;
        case 8: _t->on_butSetTcolor_clicked(); break;
        case 9: _t->on_cbShowBBox_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_butSetWireframeColor_clicked(); break;
        case 11: _t->on_hsWireframeWidth_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_cbDrawTrimesh_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TrimeshManager::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_TrimeshManager.data,
      qt_meta_data_TrimeshManager,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TrimeshManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrimeshManager::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TrimeshManager.stringdata0))
        return static_cast<void*>(const_cast< TrimeshManager*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int TrimeshManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
