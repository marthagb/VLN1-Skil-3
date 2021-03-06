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
    servicelayer.cpp \
    addscientistdialog.cpp \
    addcomputerdialog.cpp \
    addassociationdialog.cpp \
    updatescientist.cpp \
    savescientiststofiledialog.cpp \
    savecomputerstofiledialog.cpp \
    saveassociationstofiledialog.cpp \
    updatecomputer.cpp \
    loadscientistsfromfiledialog.cpp \
    loadcomputersfromfile.cpp \
    scientistsinformationwindowdialog.cpp

HEADERS  += mainwindow.h \
    persons.h \
    computer.h \
    association.h \
    validation.h \
    datalayer.h \
    servicelayer.h \
    addscientistdialog.h \
    addcomputerdialog.h \
    addassociationdialog.h \
    updatescientist.h \
    savescientiststofiledialog.h \
    savecomputerstofiledialog.h \
    saveassociationstofiledialog.h \
    updatecomputer.h \
    loadscientistsfromfiledialog.h \
    loadcomputersfromfile.h \
    scientistsinformationwindowdialog.h

FORMS    += mainwindow.ui \
    addscientistdialog.ui \
    addcomputerdialog.ui \
    addassociationdialog.ui \
    updatescientist.ui \
    savescientiststofiledialog.ui \
    savecomputerstofiledialog.ui \
    saveassociationstofiledialog.ui \
    updatecomputer.ui \
    loadscientistsfromfiledialog.ui \
    loadcomputersfromfile.ui \
    scientistsinformationwindowdialog.ui

RESOURCES += \
    resources.qrc
