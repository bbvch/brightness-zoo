/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef IIOSENSOR_H
#define IIOSENSOR_H

#include "AmbientLightSensor.h"

#include <sysfs/RoValue.h>
#include <QString>

class IioSensor :
    public AmbientLightSensor
{
public:
  IioSensor(QString device);

  int read() const override;

private:
  sysfs::RoValue sensor;

};


#endif
