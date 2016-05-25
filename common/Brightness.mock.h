/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESS_MOCK_H
#define BRIGHTNESS_MOCK_H

#include "Brightness.h"

#include <gmock/gmock.h>

class Brightness_Mock :
    public Brightness
{
  public:
    MOCK_METHOD1(setBrightness, void(qint32));
    MOCK_CONST_METHOD0(getBrightness, qint32());
};

#endif
