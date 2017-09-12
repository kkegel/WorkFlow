#-------------------------------------------------
#
# Project created by QtCreator 2017-08-22T14:15:26
#
#-------------------------------------------------

QT       += core gui


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectManagement
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
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
    systemfilereader.cpp \
    filemanager.cpp \
    projectfilereader.cpp \
    systemfilewriter.cpp \
    projectfilewriter.cpp \
    datahandler.cpp \
    projectitem.cpp \
    project.cpp \
    filedatahandler.cpp \
    state.cpp \
    process.cpp \
    projectstate.cpp \
    processstate.cpp \
    projectmanager.cpp \
    datecontainer.cpp \
    multiscalingbox.cpp \
    datelib.cpp \
    createprojectdialog.cpp \
    processdialog.cpp

HEADERS += \
        mainwindow.h \
    systemfilereader.h \
    filemanager.h \
    projectfilereader.h \
    systemfilewriter.h \
    projectfilewriter.h \
    datahandler.h \
    projectitem.h \
    project.h \
    filedatahandler.h \
    state.h \
    projectstate.h \
    processstate.h \
    projectmanager.h \
    datecontainer.h \
    multiscalingbox.h \
    datelib.h \
    createprojectdialog.h \
    processdialog.h \
    process_.h

FORMS += \
        mainwindow.ui \
    createprojectdialog.ui \
    processdialog.ui
