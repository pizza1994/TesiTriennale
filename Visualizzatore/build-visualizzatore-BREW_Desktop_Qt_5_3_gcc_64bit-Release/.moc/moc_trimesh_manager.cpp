/****************************************************************************
** Meta object code from reading C++ file 'trimesh_manager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Visualizzatore/GUI/managers/trimesh_manager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trimesh_manager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TrimeshManager_t {
    QByteArrayData data[17];
    char stringdata[343];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrimeshManager_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrimeshManager_t qt_meta_stringdata_TrimeshManager = {
    {
QT_MOC_LITERAL(0, 0, 14),
QT_MOC_LITERAL(1, 15, 25),
QT_MOC_LITERAL(2, 41, 0),
QT_MOC_LITERAL(3, 42, 27),
QT_MOC_LITERAL(4, 70, 5),
QT_MOC_LITERAL(5, 76, 19),
QT_MOC_LITERAL(6, 96, 7),
QT_MOC_LITERAL(7, 104, 17),
QT_MOC_LITERAL(8, 122, 19),
QT_MOC_LITERAL(9, 142, 24),
QT_MOC_LITERAL(10, 167, 26),
QT_MOC_LITERAL(11, 194, 23),
QT_MOC_LITERAL(12, 218, 23),
QT_MOC_LITERAL(13, 242, 31),
QT_MOC_LITERAL(14, 274, 32),
QT_MOC_LITERAL(15, 307, 5),
QT_MOC_LITERAL(16, 313, 29)
    },
    "TrimeshManager\0on_butLoadTrimesh_clicked\0"
    "\0on_cbWireframe_stateChanged\0state\0"
    "on_rbPoints_toggled\0checked\0"
    "on_rbFlat_toggled\0on_rbSmooth_toggled\0"
    "on_rbVertexColor_toggled\0"
    "on_rbTriangleColor_toggled\0"
    "on_butSetVColor_clicked\0on_butSetTcolor_clicked\0"
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
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       5,    1,   78,    2, 0x08 /* Private */,
       7,    1,   81,    2, 0x08 /* Private */,
       8,    1,   84,    2, 0x08 /* Private */,
       9,    1,   87,    2, 0x08 /* Private */,
      10,    1,   90,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x08 /* Private */,
      14,    1,   96,    2, 0x08 /* Private */,
      16,    1,   99,    2, 0x08 /* Private */,

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
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,    4,

       0        // eod
};

void TrimeshManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TrimeshManager *_t = static_cast<TrimeshManager *>(_o);
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
        case 9: _t->on_butSetWireframeColor_clicked(); break;
        case 10: _t->on_hsWireframeWidth_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_cbDrawTrimesh_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject TrimeshManager::staticMetaObject = {
    { &QDockWidget::staticMetaObject, qt_meta_stringdata_TrimeshManager.data,
      qt_meta_data_TrimeshManager,  qt_static_metacall, 0, 0}
};


const QMetaObject *TrimeshManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrimeshManager::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TrimeshManager.stringdata))
        return static_cast<void*>(const_cast< TrimeshManager*>(this));
    return QDockWidget::qt_metacast(_clname);
}

int TrimeshManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDockWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
