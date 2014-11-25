#-------------------------------------------------
#
# Project created by QtCreator 2014-11-25T09:11:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = traing_gui
TEMPLATE = app
INCLUDEPATH += $$PWD/src

SOURCES += main.cpp\
        mainwindow.cpp \
    add_user.cpp \
    del_user.cpp \
    src/config.cpp \
    src/login_manager.cpp \
    src/recognizer.cpp \
    src/trainer.cpp \
    authorized.cpp

HEADERS  += mainwindow.h \
    add_user.h \
    del_user.h \
    src/config.h\
    src/login_manager.h\
    src/recognizer.h\
    src/trainer.h\
    authorized.h

FORMS    += mainwindow.ui \
    add_user.ui \
    del_user.ui \
    authorized.ui

LIBS += `pkg-config opencv --libs`
LIBS += \
	-lboost_system \
	-lboost_thread \
	-lboost_filesystem \
