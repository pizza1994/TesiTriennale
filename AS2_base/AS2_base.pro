QT += core gui opengl xml widgets

TARGET   = AS2_base
TEMPLATE = app

# Download LibQGLViewer and follow the compiling
# instructions to get it working on your system.
# See:
#
# http://www.libqglviewer.com/compilation.html
#

# library linking for MacOS
macx {
    LIB_NAME = QGLViewer.framework/QGLViewer
    LIB_DIR = /Library/Frameworks
    INCLUDE_DIR = $${LIB_DIR}/QGLViewer.framework/Headers
    LIBS += -F$${LIB_DIR} -framework QGLViewer
    INCLUDEPATH *= $${INCLUDE_DIR}
    DEPENDPATH  *= $${INCLUDE_DIR}
}


# library linking for Linux (double check the path!)
#unix:!macx{ LIBS += /usr/lib/libQGLViewer.so }

HEADERS  += vec3.h
HEADERS  += bbox.h
HEADERS  += drawable_object.h
HEADERS  += trimesh/drawable_trimesh.h
HEADERS  += trimesh/load_save_trimesh.h
HEADERS  += trimesh/trimesh.h
HEADERS  += GUI/mainwindow.h
HEADERS  += GUI/glcanvas.h
HEADERS  += GUI/trimesh_manager.h
HEADERS  += GUI/window_manager.h

SOURCES += main.cpp
SOURCES += trimesh/drawable_trimesh.cpp
SOURCES += trimesh/load_save_trimesh.cpp
SOURCES += GUI/mainwindow.cpp
SOURCES += GUI/glcanvas.cpp
SOURCES += GUI/trimesh_manager.cpp
SOURCES += GUI/window_manager.cpp


FORMS += GUI/mainwindow.ui
FORMS += GUI/trimesh_manager.ui
FORMS += GUI/window_manager.ui
