/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef AMBIENTTOBRIGHTNESS_MOCK_H
#define AMBIENTTOBRIGHTNESS_MOCK_H

#include "AmbientToBrightness.h"

#include <gmock/gmock.h>

class AmbientToBrightness_Mock :
    public AmbientToBrightness
{
public:
  MOCK_CONST_METHOD1(brigthnessFromLux, int(int));

};

#endif
