# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

include(../test.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

TARGET = common.test

HEADERS += \
    ConfigurationReader.h \

SOURCES += \
    ConfigurationReader.cpp \
    ConfigurationReader.test.cpp \
