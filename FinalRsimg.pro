#-------------------------------------------------
#
# Project created by QtCreator 2018-06-06T23:33:16
#
#-------------------------------------------------

QT       += core gui
QT       += charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FinalRsimg
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
        mainwindow.cpp \
    rsimage.cpp \
    dialogimg.cpp \
    dialogimgs.cpp \
    dialogroll.cpp

HEADERS += \
        mainwindow.h \
    rsimage.h \
    dialogimg.h \
    dialogimgs.h \
    dialogroll.h

FORMS += \
        mainwindow.ui \
    dialogimg.ui \
    dialogimgs.ui \
    dialogroll.ui

target.path = $$[QT_INSTALL_EXAMPLES]/charts/barchart
INSTALLS += target


