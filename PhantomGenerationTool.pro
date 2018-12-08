#-------------------------------------------------
#
# Project created by QtCreator 2018-07-08T23:44:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = PhantomGenerationTool
TEMPLATE = app

#include(D:\Qt\Qt5.10.0\5.10.0\Src\qtimageformats\src\3rdparty\libtiff.pri)
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    setdimension.cpp \
    mousetracker.cpp \
    saveimage.cpp

HEADERS += \
        mainwindow.h \
    setdimension.h \
    mousetracker.h \
    saveimage.h

FORMS += \
        mainwindow.ui \
  setdimension.ui \
   saveimage.ui
#INCLUDEPATH += C:\tiff-3.9.7\libtiff\libtiff
#LIBS += -L"C:\tiff-3.9.7\libtiff" -llibtiff
#INCLUDEPATH += C:\Program Files (x86)\GnuWin32\include
#LIBS += -L"C:\Program Files (x86)\GnuWin32\lib" -lzlib
#INCLUDEPATH +=D:\Qt\Qt5.10.0\5.10.0\Src\3rdparty\zlib
#include(D:\Qt\Qt5.10.0\5.10.0\Src\qtimageformats\src\3rdparty\libtiff.pri)

win32: LIBS += -LC:/tiff-4.0.9/libtiff/ -llibtiff_i
INCLUDEPATH += C:/tiff-4.0.9/libtiff
DEPENDPATH += C:/tiff-4.0.9/libtiff


