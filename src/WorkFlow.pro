QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WorkFlow
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        source/main/main.cpp \
        source/ui/mainwindow.cpp \
        source/files/systemfilereader.cpp \
        source/files/filemanager.cpp \
        source/files/projectfilereader.cpp \
        source/files/systemfilewriter.cpp \
        source/files/projectfilewriter.cpp \
        source/core/datahandler.cpp \
        source/core/projectitem.cpp \
        source/core/project.cpp \
        source/files/filedatahandler.cpp \
        source/core/state.cpp \
        source/core/process.cpp \
        source/core/projectstate.cpp \
        source/core/processstate.cpp \
        source/core/projectmanager.cpp \
        source/container/datecontainer.cpp \
        source/ui/multiscalingbox.cpp \
        source/includes/datelib.cpp \
        source/dialogs/createprojectdialog.cpp \
        source/dialogs/processdialog.cpp \
        source/dialogs/userdialog.cpp \
        source/dialogs/annotationsdialog.cpp \
        source/dialogs/storedialog.cpp

HEADERS += \
        header/mainwindow.h \
        header/systemfilereader.h \
        header/filemanager.h \
        header/projectfilereader.h \
        header/systemfilewriter.h \
        header/projectfilewriter.h \
        header/datahandler.h \
        header/projectitem.h \
        header/project.h \
        header/filedatahandler.h \
        header/state.h \
        header/projectstate.h \
        header/processstate.h \
        header/projectmanager.h \
        header/datecontainer.h \
        header/multiscalingbox.h \
        header/datelib.h \
        header/createprojectdialog.h \
        header/processdialog.h \
        header/process_.h \
        header/commander.h \
        header/userindex.h \
        header/annotationsdialog.h \
        header/userdialog.h \
        header/storedialog.h

FORMS += \
        ui/mainwindow.ui \
        ui/createprojectdialog.ui \
        ui/processdialog.ui \
        ui/annotationsdialog.ui \
        ui/userdialog.ui \
        ui/storedialog.ui

RC_FILE += res/myapp.rc

ICON = res/icon.icns
