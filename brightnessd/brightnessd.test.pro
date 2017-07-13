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

HEADERS += \
    ../common/sysfs/Reader.mock.h \
    ../common/sysfs/Writer.mock.h \
    ../common/sysfs/Reader.h \
    ../common/sysfs/Writer.h \
    BrightnessControl.h \
    SysfsDevice.h \
    Device.mock.h \
    CheckedBlock.h \
    ValueCheck.h \
