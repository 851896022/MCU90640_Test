#-------------------------------------------------
#
# Project created by QtCreator 2019-04-05T11:02:59
#
#-------------------------------------------------

QT       += core gui  serialport multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MCU90640_Test
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


SOURCES += \
        main.cpp \
        windows.cpp \
    add.cpp \
    global.cpp \
    qlog.cpp \
    topbar.cpp

HEADERS += \
        windows.h \
    add.h \
    global.h \
    qlog.h \
    topbar.h

FORMS += \
        windows.ui \
    add.ui \
    topbar.ui

RESOURCES += \
    image.qrc
win32:RC_FILE   = main.rc
