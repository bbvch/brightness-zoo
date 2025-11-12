# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	MIT

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = \
    common/common.pro \
    common/common.test.pro \
    ambientlightd/ambientlightd.pro \
    ambientlightd/ambientlightd.test.pro \
    brightnessd/brightnessd.pro \
    brightnessd/brightnessd.test.pro \
    xactivityd/xactivityd.pro \
    checkbrightness/checkbrightness.pro \
    fbactivityd/fbactivityd.pro \