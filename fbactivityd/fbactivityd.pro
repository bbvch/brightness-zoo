# (C) Copyright 2025
# Marc Brändli, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-2.0+

include(../settings.pri)

QT += core
QT -= gui
QT += dbus

CONFIG += console
CONFIG -= app_bundle

TARGET = fbactivityd

TEMPLATE = app

LIBS += -lpthread

SOURCES += \
    main.cpp \
    FramebufferIdle.cpp \
    InputDevice.cpp \

HEADERS += \
    FramebufferIdle.h \
    InputDevice.h \
