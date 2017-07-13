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
    ../common/sysfs/RoValue.cpp \
    ../common/sysfs/WoValue.cpp \
    dbus/Brightness.cpp \
    BrightnessControl.cpp \
    SysfsDevice.cpp \
    ../common/DbusNames.cpp \
    ../common/ConfigurationReader.cpp \
    ../common/DbusCommandLine.cpp \
    Configuration.cpp \

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
    ../common/ConfigurationReader.h \
    ../common/DbusCommandLine.h \
    Configuration.h \
