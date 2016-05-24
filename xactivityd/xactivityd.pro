# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+
# SPDX-License-Identifier:	GPL-2.0

QT += core
QT -= gui
QT += dbus

CONFIG += c++11

TARGET = xactivityd
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

LIBS += -lX11 -lXss -lXext

INCLUDEPATH += ../common/

SOURCES += main.cpp \
    Xidle.cpp \
    idletime.c \
    ActivityNotifier.cpp \
    PowersaveProxy.cpp \
    ../common/Configuration.cpp

HEADERS += \
    idletime.h \
    Xidle.h \
    ActivityNotifier.h \
    PowersaveProxy.h \
    ../common/Configuration.h
