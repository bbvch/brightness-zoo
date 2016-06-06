/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "IioSensor.h"


IioSensor::IioSensor(QString device) :
  sensor{device + "/in_illuminance_input"}
{
}

int IioSensor::read() const
{
  return sensor.read().toInt();
}
