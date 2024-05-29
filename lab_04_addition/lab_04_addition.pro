# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

TARGET = lab_04_addition

QT = core gui widgets

CONFIG += console

HEADERS = \
   $$PWD/gui/mainwindow.h \
   $$PWD/src/button/base_button.hpp \
   $$PWD/src/button/elevator_button/elevator_button.hpp \
   $$PWD/src/button/floor_button/floor_button.hpp \
   $$PWD/src/cabin/cabin.hpp \
   $$PWD/src/controller/controller.hpp \
   $$PWD/src/doors/doors.hpp \
   $$PWD/src/elevator/elevator.hpp \
   $$PWD/src/config.hpp

SOURCES = \
   $$PWD/gui/mainwindow.cpp \
   $$PWD/src/button/base_button.cpp \
   $$PWD/src/button/elevator_button/elevator_button.cpp \
   $$PWD/src/button/floor_button/floor_button.cpp \
   $$PWD/src/cabin/cabin.cpp \
   $$PWD/src/controller/controller.cpp \
   $$PWD/src/doors/doors.cpp \
   $$PWD/src/elevator/elevator.cpp \
   $$PWD/main.cpp

INCLUDEPATH = \
    $$PWD/gui/

FORMS = \
   gui/ui/mainwindow.ui

#DEFINES = 

