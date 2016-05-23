# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

QT += core
QT -= gui
QT += dbus

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TARGET = brightnessd

TEMPLATE = app

SOURCES += main.cpp \
    sysfs/RoValue.cpp \
    sysfs/WoValue.cpp \
    dbus/Brightness.cpp \
    BrightnessControl.cpp \
    SysfsDevice.cpp

HEADERS += \
    Device.h \
    sysfs/Reader.h \
    sysfs/Writer.h \
    sysfs/RoValue.h \
    sysfs/WoValue.h \
    dbus/Brightness.h \
    BrightnessControl.h \
    Brightness.h \
    Powersave.h \
    SysfsDevice.h
