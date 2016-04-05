/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../AS2_base/GUI/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[352];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 25), // "add_window_widget_to_dock"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 26), // "add_trimesh_widget_to_dock"
QT_MOC_LITERAL(4, 65, 15), // "set_full_screen"
QT_MOC_LITERAL(5, 81, 20), // "set_background_color"
QT_MOC_LITERAL(6, 102, 12), // "load_trimesh"
QT_MOC_LITERAL(7, 115, 11), // "const char*"
QT_MOC_LITERAL(8, 127, 16), // "set_flat_shading"
QT_MOC_LITERAL(9, 144, 18), // "set_smooth_shading"
QT_MOC_LITERAL(10, 163, 18), // "set_points_shading"
QT_MOC_LITERAL(11, 182, 13), // "set_draw_mesh"
QT_MOC_LITERAL(12, 196, 13), // "set_wireframe"
QT_MOC_LITERAL(13, 210, 19), // "set_wireframe_width"
QT_MOC_LITERAL(14, 230, 23), // "set_enable_vertex_color"
QT_MOC_LITERAL(15, 254, 25), // "set_enable_triangle_color"
QT_MOC_LITERAL(16, 280, 16), // "set_vertex_color"
QT_MOC_LITERAL(17, 297, 18), // "set_triangle_color"
QT_MOC_LITERAL(18, 316, 19), // "set_wireframe_color"
QT_MOC_LITERAL(19, 336, 15) // "set_enable_grid"

    },
    "MainWindow\0add_window_widget_to_dock\0"
    "\0add_trimesh_widget_to_dock\0set_full_screen\0"
    "set_background_color\0load_trimesh\0"
    "const char*\0set_flat_shading\0"
    "set_smooth_shading\0set_points_shading\0"
    "set_draw_mesh\0set_wireframe\0"
    "set_wireframe_width\0set_enable_vertex_color\0"
    "set_enable_triangle_color\0set_vertex_color\0"
    "set_triangle_color\0set_wireframe_color\0"
    "set_enable_grid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x08 /* Private */,
       3,    0,  100,    2, 0x08 /* Private */,
       4,    1,  101,    2, 0x08 /* Private */,
       5,    1,  104,    2, 0x08 /* Private */,
       6,    1,  107,    2, 0x08 /* Private */,
       8,    0,  110,    2, 0x08 /* Private */,
       9,    0,  111,    2, 0x08 /* Private */,
      10,    0,  112,    2, 0x08 /* Private */,
      11,    1,  113,    2, 0x08 /* Private */,
      12,    1,  116,    2, 0x08 /* Private */,
      13,    1,  119,    2, 0x08 /* Private */,
      14,    0,  122,    2, 0x08 /* Private */,
      15,    0,  123,    2, 0x08 /* Private */,
      16,    1,  124,    2, 0x08 /* Private */,
      17,    1,  127,    2, 0x08 /* Private */,
      18,    1,  130,    2, 0x08 /* Private */,
      19,    0,  133,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void, QMetaType::QColor,    2,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->add_window_widget_to_dock(); break;
        case 1: _t->add_trimesh_widget_to_dock(); break;
        case 2: _t->set_full_screen((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->set_background_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 4: _t->load_trimesh((*reinterpret_cast< const char*(*)>(_a[1]))); break;
        case 5: _t->set_flat_shading(); break;
        case 6: _t->set_smooth_shading(); break;
        case 7: _t->set_points_shading(); break;
        case 8: _t->set_draw_mesh((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->set_wireframe((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->set_wireframe_width((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->set_enable_vertex_color(); break;
        case 12: _t->set_enable_triangle_color(); break;
        case 13: _t->set_vertex_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 14: _t->set_triangle_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 15: _t->set_wireframe_color((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 16: _t->set_enable_grid(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
