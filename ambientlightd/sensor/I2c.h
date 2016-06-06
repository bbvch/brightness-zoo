/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef I2C_H
#define I2C_H

#include <cstdint>

class I2c
{
public:
  virtual ~I2c() = default;

  virtual uint8_t read(uint8_t address, uint8_t reg) = 0;
  virtual void write(uint8_t address, uint8_t reg, uint8_t data) = 0;

};

#endif
