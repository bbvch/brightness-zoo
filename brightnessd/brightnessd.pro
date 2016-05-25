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

INSTALLS += target
target.path = /usr/bin

TEMPLATE = app

INCLUDEPATH += ../common/

SOURCES += main.cpp \
    ../common/sysfs/RoValue.cpp \
    ../common/sysfs/WoValue.cpp \
    dbus/Brightness.cpp \
    BrightnessControl.cpp \
    SysfsDevice.cpp \
    ../common/DbusNames.cpp \
    ../common/ConfigurationReader.cpp

HEADERS += \
    Device.h \
    ../common/sysfs/Reader.h \
    ../common/sysfs/Writer.h \
    ../common/sysfs/RoValue.h \
    ../common/sysfs/WoValue.h \
    dbus/Brightness.h \
    BrightnessControl.h \
    ../common/Brightness.h \
    Powersave.h \
    SysfsDevice.h \
    ../common/DbusNames.h \
    ../common/ConfigurationReader.h
