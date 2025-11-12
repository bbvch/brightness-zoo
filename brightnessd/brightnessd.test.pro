# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

include(../test.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

TARGET = brightnessd.test

SOURCES += \
    BrightnessControl.test.cpp \
    BrightnessControl.cpp \
    SysfsDevice.cpp \
    SysfsDevice.test.cpp \
    CheckedBlock.cpp \
    ValueCheck.cpp \
    print.cpp \

HEADERS += \
    BrightnessControl.h \
    SysfsDevice.h \
    Device.mock.h \
    CheckedBlock.h \
    ValueCheck.h \
    print.h \
