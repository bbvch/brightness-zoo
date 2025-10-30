#
# Framebuffer Activity Daemon
#

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
    ../common/PowersaveProxy.cpp \
    ../common/ActivityNotifier.cpp \
    ../common/Configuration.cpp \
    ../common/ConfigurationReader.cpp \
    ../common/DbusNames.cpp \
    ../common/DbusCommandLine.cpp

HEADERS += \
    FramebufferIdle.h \
    ../common/PowersaveProxy.h \
    ../common/ActivityNotifier.h \
    ../common/Configuration.h \
    ../common/ConfigurationReader.h \
    ../common/DbusNames.h \
    ../common/DbusCommandLine.h
