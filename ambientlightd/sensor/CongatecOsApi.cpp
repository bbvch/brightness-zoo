/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "CongatecOsApi.h"

#include <Cgos.h>

#include <stdexcept>


void error(const std::string &message)
{
  throw std::runtime_error("error with congatec os api: " + message);
}

CongatecOsApi::CongatecOsApi() :
  instance{open()},
  primary{*this, CGOS_I2C_TYPE_PRIMARY}
{
}

CongatecOsApi::~CongatecOsApi()
{
  CgosBoardClose(instance);
  CgosLibUninitialize();
}

I2c &CongatecOsApi::primaryI2c()
{
  return primary;
}

unsigned long CongatecOsApi::open()
{
  if (!CgosLibInitialize()) {
    if (!CgosLibInstall(1)) {
      error("could not install library");
    }

    if (!CgosLibInitialize()) {
      error("could not initialize library");
    }
  }

  HCGOS instance;

  if (!CgosBoardOpen(0, 0, 0, &instance)) {
    error("could not open board");
  }

  return instance;
}


CongatecI2c::CongatecI2c(CongatecOsApi &_api, unsigned long type) :
  api{_api},
  bus(getBus(_api, type))
{
}

uint8_t CongatecI2c::read(uint8_t address, uint8_t reg)
{
  uint8_t data;

  if (!CgosI2CReadRegister(api.instance, bus, address, reg, &data))
  {
    error("could not read I2C register");
  }

  return data;
}

void CongatecI2c::write(uint8_t address, uint8_t reg, uint8_t data)
{
  if (!CgosI2CWriteRegister(api.instance, bus, address, reg, data))
  {
    error("could not write I2C register");
  }
}

unsigned long CongatecI2c::getBus(CongatecOsApi &api, unsigned long type)
{
  const auto count = CgosI2CCount(api.instance);
  for (unsigned long bus = 0; bus < count; bus++) {
    if (CgosI2CType(api.instance, bus) == type)
    {
      return bus;
    }
  }

  error("bus not found: " + std::to_string(type));
}
