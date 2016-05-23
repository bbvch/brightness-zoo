/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Device.h"

Device::Device(sysfs::Writer &_brightness, sysfs::Reader &_maxBrightness) :
  brightness{_brightness},
  maxBrightness{_maxBrightness}
{
}

void Device::setPercentage(qint32 percentage)
{
  auto max = maxBrightness.read().toInt();
  auto value = (percentage * max + 50) / 100;
  brightness.write(QString::number(value));
}
