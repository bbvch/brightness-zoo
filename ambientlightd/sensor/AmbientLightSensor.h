/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef AMBIENTLIGHTSENSOR_H
#define AMBIENTLIGHTSENSOR_H

class AmbientLightSensor
{
public:
  virtual ~AmbientLightSensor() = default;

  virtual int read() const = 0;

};

#endif
