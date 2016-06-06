/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef APDS9300_H
#define APDS9300_H

#include "AmbientLightSensor.h"
#include "I2c.h"

class Apds9300 :
    public AmbientLightSensor
{
public:
  Apds9300(I2c &i2c);

  int read() const override;

private:
  I2c &i2c;

};

#endif
