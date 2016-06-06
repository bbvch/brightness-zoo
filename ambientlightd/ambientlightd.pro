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

TARGET = ambientlightd

INSTALLS += target
target.path = /usr/bin

TEMPLATE = app

INCLUDEPATH += ../common/

SOURCES += main.cpp \
    AmbientLightD.cpp \
    convert/LinearWithSaturation.cpp \
    ../common/sysfs/RoValue.cpp \
    BrightnessProxy.cpp \
    ../common/DbusNames.cpp \
    ../common/ConfigurationReader.cpp \
    Configuration.cpp \
    ../common/DbusCommandLine.cpp \
    sensor/IioSensor.cpp

HEADERS += \
    AmbientLightD.h \
    convert/LinearWithSaturation.h \
    convert/LinearConfiguration.h \
    convert/AmbientToBrightness.h \
    ../common/sysfs/Reader.h \
    ../common/sysfs/RoValue.h \
    BrightnessProxy.h \
    ../common/DbusNames.h \
    ../common/Brightness.h \
    ../common/ConfigurationReader.h \
    Configuration.h \
    ../common/DbusCommandLine.h \
    sensor/AmbientLightSensor.h \
    sensor/AmbientLightSensor.mock.h \
    sensor/IioSensor.h
