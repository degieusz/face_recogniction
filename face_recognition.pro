#-------------------------------------------------
#
# Project created by QtCreator 2014-10-30T07:00:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = face_recognition
TEMPLATE = app


SOURCES += main.cpp\
				mainwindow.cpp \
    authenticator.cpp

HEADERS  += mainwindow.h \
    authenticator.h

FORMS    += mainwindow.ui
LIBS += `pkg-config opencv --libs`
