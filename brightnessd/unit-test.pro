# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle

QT += testlib

LIBS += -lgtest -lgmock -lgtest_main

SOURCES += \
    BrightnessControl.test.cpp \
    BrightnessControl.cpp \
    SysfsDevice.cpp \
    SysfsDevice.test.cpp

HEADERS += \
    sysfs/Reader.mock.h \
    sysfs/Writer.mock.h \
    sysfs/Reader.h \
    sysfs/Writer.h \
    BrightnessControl.h \
    SysfsDevice.h \
    Device.mock.h
