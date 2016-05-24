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

HEADERS += \
    Configuration.h

SOURCES += \
    Configuration.cpp \
    Configuration.test.cpp
