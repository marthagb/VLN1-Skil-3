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
<<<<<<< HEAD
    updatecomputer.cpp
=======
    loadscientistsfromfiledialog.cpp \
    loadcomputersfromfile.cpp
>>>>>>> 028420ff1128d6beac3fa755fd6afad17ec66834

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
<<<<<<< HEAD
    updatecomputer.h
=======
    loadscientistsfromfiledialog.h \
    loadcomputersfromfile.h
>>>>>>> 028420ff1128d6beac3fa755fd6afad17ec66834

FORMS    += mainwindow.ui \
    addscientistdialog.ui \
    addcomputerdialog.ui \
    addassociationdialog.ui \
    updatescientist.ui \
    savescientiststofiledialog.ui \
    savecomputerstofiledialog.ui \
    saveassociationstofiledialog.ui \
<<<<<<< HEAD
    updatecomputer.ui
=======
    loadscientistsfromfiledialog.ui \
    loadcomputersfromfile.ui
>>>>>>> 028420ff1128d6beac3fa755fd6afad17ec66834

RESOURCES += \
    resources.qrc
