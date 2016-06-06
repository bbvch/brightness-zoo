/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef AMBIENTLIGHTSENSOR_MOCK_H
#define AMBIENTLIGHTSENSOR_MOCK_H

#include "AmbientLightSensor.h"

#include <gmock/gmock.h>

class AmbientLightSensor_Mock :
    public AmbientLightSensor
{
public:
  MOCK_CONST_METHOD0(read, int());

};

#endif
