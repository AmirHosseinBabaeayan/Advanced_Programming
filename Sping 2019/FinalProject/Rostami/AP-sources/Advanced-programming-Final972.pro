#-------------------------------------------------
#
# Project created by QtCreator 2019-07-10T23:40:20
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Advanced-programming-Final972
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

CONFIG += c++11

SOURCES += stepbystepdfa.cpp \
    dfawindow.cpp \
    enterpage.cpp \
    graphviewturing.cpp \
    stepbystepturing.cpp \
    turing.cpp \
    turingwindow.cpp
SOURCES += dfa.cpp
SOURCES += edge.cpp
SOURCES += main.cpp
SOURCES += node.cpp
SOURCES += graphviewdfa.cpp

HEADERS += dfa.h
HEADERS += dfawindow.h
HEADERS += edge.h
HEADERS += enterpage.h
HEADERS += graphviewturing.h
HEADERS += stepbystepturing.h
HEADERS += node.h
HEADERS += turing.h
HEADERS += turingwindow.h
HEADERS += graphviewdfa.h
HEADERS += stepbystepdfa.h


FORMS += \
        enterpage.ui \
        dfawindow.ui \
        turingwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES +=  resources.qrc
