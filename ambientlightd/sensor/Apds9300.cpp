/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Apds9300.h"

Apds9300::Apds9300(I2c &_i2c) :
  i2c{_i2c}
{
  i2c.write(0x52, 0xe0, 0x03);
}

int Apds9300::read() const
{
  uint16_t low = i2c.read(0x52, 0xec);
  uint16_t high = i2c.read(0x52, 0xed);
  uint16_t value = (high << 8) | low;
  return value;
}
