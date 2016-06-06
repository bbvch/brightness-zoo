/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CONGATECOSAPI_H
#define CONGATECOSAPI_H

#include "I2c.h"

class CongatecOsApi;

class CongatecI2c :
    public I2c
{
public:

  CongatecI2c(CongatecOsApi &_api, unsigned long type);

  uint8_t read(uint8_t address, uint8_t reg) override;
  void write(uint8_t address, uint8_t reg, uint8_t data) override;

private:
  CongatecOsApi &api;
  const unsigned long bus;

  static unsigned long getBus(CongatecOsApi &api, unsigned long type);

};

class CongatecOsApi
{
public:
  CongatecOsApi();
  virtual ~CongatecOsApi();

  I2c &primaryI2c();

private:
  const unsigned long instance;
  CongatecI2c primary;

  static unsigned long open();

  friend CongatecI2c;
};



#endif
