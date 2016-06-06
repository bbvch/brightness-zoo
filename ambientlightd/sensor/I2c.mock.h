/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef I2C_MOCK_H
#define I2C_MOCK_H

#include "I2c.h"

#include <gmock/gmock.h>

class I2c_Mock :
    public I2c
{
public:
  MOCK_METHOD2(read, uint8_t(uint8_t,uint8_t));
  MOCK_METHOD3(write, void(uint8_t,uint8_t,uint8_t));

};

#endif
