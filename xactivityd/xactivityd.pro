# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+
# SPDX-License-Identifier:	GPL-2.0

QT += core
QT -= gui
QT += dbus

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TARGET = xactivityd

INSTALLS += target
target.path = /usr/bin

TEMPLATE = app

LIBS += -lX11 -lXss -lXext

INCLUDEPATH += ../common/

SOURCES += main.cpp \
    Xidle.cpp \
    idletime.c \
    ActivityNotifier.cpp \
    PowersaveProxy.cpp \
    ../common/ConfigurationReader.cpp \
    ../common/DbusNames.cpp \
    ../common/DbusCommandLine.cpp \
    Configuration.cpp

HEADERS += \
    idletime.h \
    Xidle.h \
    ActivityNotifier.h \
    PowersaveProxy.h \
    ../common/ConfigurationReader.h \
    ../common/DbusNames.h \
    ../common/DbusCommandLine.h \
    Configuration.h
