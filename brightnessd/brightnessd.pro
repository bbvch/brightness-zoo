# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

include(../settings.pri)

QT += core
QT -= gui
QT += dbus

CONFIG += console
CONFIG -= app_bundle

TARGET = brightnessd

TEMPLATE = app

SOURCES += main.cpp \
    dbus/Brightness.cpp \
    BrightnessControl.cpp \
    SysfsDevice.cpp \
    Configuration.cpp \
    CheckedBlock.cpp \
    ValueCheck.cpp \
    ProblemHandler.cpp \
    print.cpp \

HEADERS += \
    Device.h \
    dbus/Brightness.h \
    BrightnessControl.h \
    Powersave.h \
    SysfsDevice.h \
    Configuration.h \
    CheckedBlock.h \
    ValueCheck.h \
    ProblemHandler.h \
    print.h \
