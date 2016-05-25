# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle

QT += testlib

TARGET = common.test

LIBS += -lgtest -lgmock -lgtest_main

HEADERS += \
    ConfigurationReader.h

SOURCES += \
    ConfigurationReader.cpp \
    ConfigurationReader.test.cpp
