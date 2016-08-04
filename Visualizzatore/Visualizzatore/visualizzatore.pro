QT += core gui opengl xml widgets
LIBS += -L/Users/lucapitzalis/librerie/gmp-6.1.0/BUILD/lib -lgmp
LIBS += -L/Users/lucapitzalis/librerie/mpfr-3.1.3/BUILD/lib -lmpfr
LIBS += -L/Users/lucapitzalis/librerie/boost_1_59_0/BUILD/lib -lboost_system-mt-s
LIBS += -L/Users/lucapitzalis/librerie/boost_1_59_0/BUILD/lib -lboost_thread-mt-s
LIBS += -L/Users/lucapitzalis/librerie/CGAL-4.8/BUILD/lib -lCGAL
INCLUDEPATH += /Users/lucapitzalis/librerie/boost_1_59_0/BUILD/include
INCLUDEPATH += /Users/lucapitzalis/librerie/CGAL-4.8/BUILD/include
LIBS += -L/Users/bardOZ/Desktop/CGAL/gmp-6.1.0/BUILD/lib -lgmp
LIBS += -L/Users/bardOZ/Desktop/CGAL/mpfr-3.1.3/BUILD/lib -lmpfr
LIBS += -L/Users/bardOZ/Desktop/CGAL/boost_1_59_0/BUILD/lib -lboost_system-mt-s
LIBS += -L/Users/bardOZ/Desktop/CGAL/boost_1_59_0/BUILD/lib -lboost_thread-mt-s
LIBS += -L/Users/bardOZ/Desktop/CGAL/CGAL-4.8/BUILD/lib -lCGAL
INCLUDEPATH += /Users/bardOZ/Desktop/CGAL/boost_1_59_0/BUILD/include
INCLUDEPATH += /Users/bardOZ/Desktop/CGAL/CGAL-4.8/BUILD/include


#LIBS += -lCGAL

HEADERS += \
    lib/common/point.h \
    lib/timer.h \
    common.h \
    GUI/glcanvas.h \
    GUI/mainwindow.h \
    lib/trimesh/drawable_trimesh.h \
    lib/trimesh/load_save_trimesh.h \
    lib/trimesh/trimesh.h \
    lib/common/drawable_object.h \
    GUI/managers/trimesh_manager.h \
    lib/common/bounding_box.h \
    lib/common/comparators.h \
    GUI/managers/window_manager.h \
    GUI/objects/cylinder.h \
    GUI/objects/drawable_axis.h \
    GUI/objects/sphere.h \
    GUI/objects/drawable_bbox.h \
    GUI/objects/grid_cell.h \
    GUI/objects/grid.h \
    GUI/objects/drawable_grid.h \
    lib/common/importobj.h \
    lib/hexmesh/load_save.h \
    lib/hexmesh/mesh.h

SOURCES += \
    common.cpp \
    main.cpp \
    GUI/glcanvas.cpp \
    GUI/mainwindow.cpp \
    lib/trimesh/drawable_trimesh.cpp \
    lib/trimesh/load_save_trimesh.cpp \
    GUI/managers/trimesh_manager.cpp \
    GUI/managers/window_manager.cpp \
    GUI/objects/drawable_axis.cpp \
    GUI/objects/drawable_bbox.cpp \
    GUI/objects/grid.cpp \
    GUI/objects/grid_cell.cpp \
    GUI/objects/drawable_grid.cpp \
    lib/hexmesh/load_save.cpp


QMAKE_CXXFLAGS += -std=c++11

FORMS += \
    GUI/mainwindow.ui \
    GUI/managers/trimesh_manager.ui \
    GUI/managers/window_manager.ui


macx {
    ##_BOOST_PATH = /usr/local/Cellar/boost/1.60.0_1
    ##INCLUDEPATH += "$${_BOOST_PATH}/include/"
    ##LIBS += -L$${_BOOST_PATH}/lib
    ## Use only one of these:
    ##LIBS += -lboost_chrono-mt -lboost_system # using dynamic lib (not sure if you need that "-mt" at the end or not)
}

### PER INCLUDERE QGLVIEWEVER ###
unix {
    #LIBS += /usr/lib/libQGLViewer.so  # Linux (double check the path!)
    #LIBS += /usr/lib/x86_64-linux-gnu/libGLU.so
  CONFIG -= debug debug_and_release
  CONFIG *= release

  isEmpty( PREFIX ) {
        # Try same INCLUDE_DIR and LIB_DIR parameters than for the make install.
        PREFIX=/usr
  }

  # LIB_NAME
  LIB_NAME = libQGLViewer*.so*
  macx|darwin-g++ {
        LIB_NAME = libQGLViewer.$${QMAKE_EXTENSION_SHLIB}
  }
  hpux {
        LIB_NAME = libQGLViewer*.sl*
  }

  !isEmpty( QGLVIEWER_STATIC ) {
        LIB_NAME = libQGLViewer*.a
  }

  # LIB_DIR
  isEmpty( LIB_DIR ) {
        LIB_DIR = $${PREFIX}/lib
  }

  !exists( $${LIB_DIR}/$${LIB_NAME} ) {
        exists( ../../QGLViewer/$${LIB_NAME} ) {
          #message( The library was found in ../../QGLViewer which will be set as the LIB_DIR )
          LIB_DIR = ../../QGLViewer
        }
  }

  !exists( $${LIB_DIR}/$${LIB_NAME} ) {
        exists( ../../QGLViewer-build-desktop/$${LIB_NAME} ) {
          #message( The library was found in ../../QGLViewer-build-desktop which will be set as the LIB_DIR )
          LIB_DIR = ../../QGLViewer-build-desktop
        }
  }

  macx|darwin-g++ {
        !exists( $${LIB_DIR}/$${LIB_NAME} ) {
          # DYLIB was not found, try to find Framework instead
          LIB_NAME = QGLViewer.framework/QGLViewer
          LIB_DIR = ~/Library/Frameworks
          # qmake does not handle tilde
          LIB_DIR = $$system(cd $${LIB_DIR};pwd)

          !exists( $${LIB_DIR}/$${LIB_NAME} ) {
                exists( ../../QGLViewer/$${LIB_NAME} ) {
                  #message( The framework was found in ../../QGLViewer which will be set as the LIB_DIR )
                  LIB_DIR = ../../QGLViewer
                }
          }

          !exists( $${LIB_DIR}/$${LIB_NAME} ) {
                exists( ../../QGLViewer-build-desktop/$${LIB_NAME} ) {
                  #message( The framework was found in ../../QGLViewer-build-desktop which will be set as the LIB_DIR )
                  LIB_DIR = ../../QGLViewer-build-desktop
                }
          }
        }
  }

  !exists( $${LIB_DIR}/$${LIB_NAME} ) {
        message( Unable to find $${LIB_NAME} in $${LIB_DIR}. Make sure you have built it. )
        message( If you have you should run qmake LIB_DIR=/path/to/QGLViewer/$${LIB_NAME} )
  }

  # The actual directory where the library/framework was found
  LIB_DIR_ABSOLUTE_PATH = $$system(cd $${LIB_DIR};pwd)

  # INCLUDE_DIR
  isEmpty( INCLUDE_DIR ) {
        INCLUDE_DIR = $${PREFIX}/include
  }

  macx|darwin-g++ {
          !exists( $${INCLUDE_DIR}/QGLViewer/qglviewer.h ) {
                  INCLUDE_DIR=$${LIB_DIR}/QGLViewer.framework
                  exists( $${LIB_DIR}/QGLViewer.framework/Headers/QGLViewer/qglviewer.h ) {
                         INCLUDE_DIR = $${LIB_DIR}/QGLViewer.framework/Headers
                  }
          }
  }

  !exists( $${INCLUDE_DIR}/QGLViewer/qglviewer.h ) {
        exists( ../../QGLViewer/qglviewer.h ) {
          # message( libQGLViewer header files were not installed in standard $${INCLUDE_DIR} directory )
          # message( Headers were found in ../.. which will be set as the INCLUDE_DIR )
          INCLUDE_DIR = ../..
        }
  }

  !exists( $${INCLUDE_DIR}/QGLViewer/qglviewer.h ) {
        message( Unable to find QGLViewer/qglviewer.h in $${INCLUDE_DIR} )
        message( Use qmake INCLUDE_DIR=/path/to/QGLViewerDir )
  }


  macx|darwin-g++ {
        # On Mac, the lib path can be specified in the executable using install_name_tool
        contains( LIB_NAME, ".*QGLViewer.framework.*" ) {
          # If framework was not found in a standard directory
          !contains( LIB_DIR, ".*/Library/Frameworks/*$" ) {
                QMAKE_LFLAGS += -F$${LIB_DIR}
                !plugin:QMAKE_POST_LINK=install_name_tool -change QGLViewer.framework/Versions/2/QGLViewer $${LIB_DIR_ABSOLUTE_PATH}/QGLViewer.framework/Versions/2/QGLViewer $${TARGET}.app/Contents/MacOS/$${TARGET}
          }
          LIBS += -F$${LIB_DIR} -framework QGLViewer
        } else {
                !plugin:QMAKE_POST_LINK=install_name_tool -change libQGLViewer.2.dylib $${LIB_DIR_ABSOLUTE_PATH}/libQGLViewer.2.dylib $${TARGET}.app/Contents/MacOS/$${TARGET}
                LIBS *= -L$${LIB_DIR} -lQGLViewer
        }
  } else {
        isEmpty(QMAKE_LFLAGS_RPATH) {
          !plugin:QMAKE_LFLAGS += -Wl,-rpath,$${LIB_DIR_ABSOLUTE_PATH}
        } else {
          !plugin:QMAKE_RPATHDIR *= $${LIB_DIR_ABSOLUTE_PATH}
        }
        LIBS *= -L$${LIB_DIR} -lQGLViewer
  }

  # Paths were correctly detected
  INCLUDEPATH *= $${INCLUDE_DIR}
  DEPENDPATH  *= $${INCLUDE_DIR}

  !isEmpty( QGLVIEWER_STATIC ) {
        LIBS *= $${LIB_DIR}/$${LIB_NAME}
  }

  # Remove debugging options in release mode makes files much smaller
  release:QMAKE_CFLAGS_RELEASE -= -g
  release:QMAKE_CXXFLAGS_RELEASE -= -g

  # Intermediate files are created in an hidden folder
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}

macx|darwin-g++ {
  #ICON = $${INCLUDEPATH}/QGLViewer/qglviewer.icns
}

win32 {
   !designer {
      exists( ../qglviewer.rc ) {
             RC_FILE = ../qglviewer.rc
          }
      exists( ../examples/qglviewer.rc ) {
             RC_FILE = ../examples/qglviewer.rc
          }
   }
}
