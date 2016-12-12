#-------------------------------------------------
#
# Project created by QtCreator 2016-12-12T11:59:33
#
#-------------------------------------------------

QT       += core gui

QT += core sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VLN1-Skil-3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    persons.cpp \
    computer.cpp \
    association.cpp \
    validation.cpp \
    datalayer.cpp \
    servicelayer.cpp

HEADERS  += mainwindow.h \
    persons.h \
    computer.h \
    association.h \
    validation.h \
    datalayer.h \
    servicelayer.h

FORMS    += mainwindow.ui
