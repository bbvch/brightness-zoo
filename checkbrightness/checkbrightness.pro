# (C) Copyright 2017
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

include(../settings.pri)

QT += core
QT -= gui

CONFIG += console
CONFIG -= app_bundle

TARGET = checkbrightness

TEMPLATE = app

SOURCES += \
    ../common/sysfs/RoValue.cpp \
    main.cpp

HEADERS += \
    ../common/sysfs/Reader.h \
    ../common/sysfs/RoValue.h \
