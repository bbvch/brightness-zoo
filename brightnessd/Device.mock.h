/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef DEVICE_MOCK_H
#define DEVICE_MOCK_H

#include "Device.h"

#include <gmock/gmock.h>

class Device_Mock :
    public Device
{
  public:
    MOCK_METHOD1(setPercentage, void(qint32));
};

#endif
