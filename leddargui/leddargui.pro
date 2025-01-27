#-------------------------------------------------
#
# Project created by QtCreator 2017-11-10T21:06:40
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia
QT       += widgets
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

TARGET = leddargui
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
LIBS += -ggdb
INCLUDEPATH += /usr/local/include
LIBS += -L/usr/local/lib -lstdc++ -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_objdetect
INCLUDEPATH += ../LeddarLibs/
LIBS += -L../LeddarLibs/ -lLeddar -lLeddarC -lLeddarTech
DEPENDPATH += ../LeddarLibs
LIBS += -Wl,-rpath=../LeddarLibs/
INCLUDEPATH += googletest/include gtest
#LIBS += -Wl,-rpath='${ORIGIN}/../'

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    usernotifier.cpp \
    capturethread.cpp \
    unittestsuite.cpp \
    googletest/src/gtest-all.cc \
    QtBehaviorTestSuite.cpp \
    leddarthread.cpp \
    objectdetectthread.cpp

HEADERS += \
    mainwindow.h \
    LeddarProperties.h \
    LeddarC.h \
    usernotifier.h \
    capturethread.h \
    QtBehaviorTestSuite.h \
    leddarthread.h \
    objectdetectthread.h \
    globalconstants.h

FORMS += \
    mainwindow.ui
