#-------------------------------------------------
#
# Project created by QtCreator 2022-04-10T14:59:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = image_tagging_1
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    exportchoosedialg.cpp \
    image.cpp \
    imagegraphicsview.cpp \
    imageitem.cpp \
    imagelistwidgetitem.cpp \
    imagescene.cpp \
    label.cpp \
        main.cpp \
        mainwindow.cpp \
    imagewidget.cpp \
    pixel.cpp \
    pointitem.cpp

HEADERS += \
    exportchoosedialg.h \
    image.h \
    imagegraphicsview.h \
    imageitem.h \
    imagelistwidgetitem.h \
    imagescene.h \
    label.h \
        mainwindow.h \
    imagewidget.h \
    pixel.h \
    pointitem.h

FORMS += \
        mainwindow.ui
INCLUDEPATH += D:/opencv/include\
D:/opencv/include/opencv2\
F:/python3.8/include\
D:/rapidjson/rapidjson/include\
D:/rapidjson/rapidjson/include/rapidjson
LIBS += D:/opencv/x64/mingw/lib/libopencv_*\
F:/python3.8/libs/python38.lib\
F:/python3.8/libs/python3.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    SaliencyRC.py \
    SaliencyTest.py \
    disjointSet.py \
    segmentGraph.py \
    segmentImage.py \
    utils.py
