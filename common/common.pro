# (C) Copyright 2025
# Marc Brändli, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

TEMPLATE = lib
CONFIG += staticlib
CONFIG -= app_bundle

QT += core
QT -= gui
QT += dbus

TARGET = common

HEADERS += \
    ActivityNotifier.h \
    Brightness.h \
    Configuration.h \
    ConfigurationReader.h \
    DbusCommandLine.h \
    DbusNames.h \
    PowersaveProxy.h \
    sysfs/Reader.h \
    sysfs/RoValue.h \
    sysfs/WoValue.h \
    sysfs/Writer.h \

SOURCES += \
    ActivityNotifier.cpp \
    Configuration.cpp \
    ConfigurationReader.cpp \
    DbusCommandLine.cpp \
    DbusNames.cpp \
    PowersaveProxy.cpp \
    sysfs/RoValue.cpp \
    sysfs/WoValue.cpp \