# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

include(../test.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

TARGET = ambientlightd.test

SOURCES += \
    AmbientLightD.cpp \
    AmbientLightD.test.cpp \
    convert/LinearWithSaturation.cpp \
    convert/LinearWithSaturation.test.cpp \
    sensor/Apds9300.test.cpp \
    sensor/Apds9300.cpp

HEADERS += \
    ../common/Brightness.h \
    ../common/Brightness.mock.h \
    ../common/sysfs/Reader.h \
    ../common/sysfs/Reader.mock.h \
    AmbientLightD.h \
    convert/LinearWithSaturation.h \
    convert/AmbientToBrightness.h \
    convert/AmbientToBrightness.mock.h \
    convert/LinearConfiguration.h \
    sensor/AmbientLightSensor.h \
    sensor/AmbientLightSensor.mock.h \
    sensor/I2c.mock.h \
    sensor/Apds9300.h

