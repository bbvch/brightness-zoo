# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

include(../test.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

TARGET = xactivityd.test

SOURCES += \
    ActivityNotifier.cpp \
    ActivityNotifier.test.cpp \

HEADERS += \
    ActivityNotifier.h \