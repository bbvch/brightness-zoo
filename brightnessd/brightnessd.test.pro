# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle

QT += testlib

TARGET = brightnessd.test

INSTALLS += target
target.path = /usr/bin

LIBS += -lgtest -lgmock -lgtest_main

INCLUDEPATH += ../common/

SOURCES += \
    BrightnessControl.test.cpp \
    BrightnessControl.cpp \
    SysfsDevice.cpp \
    SysfsDevice.test.cpp

HEADERS += \
    ../common/sysfs/Reader.mock.h \
    ../common/sysfs/Writer.mock.h \
    ../common/sysfs/Reader.h \
    ../common/sysfs/Writer.h \
    BrightnessControl.h \
    SysfsDevice.h \
    Device.mock.h
