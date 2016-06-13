/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "SysfsDevice.h"

SysfsDevice::SysfsDevice(sysfs::Writer &_brightness, sysfs::Reader &_maxBrightness) :
  brightness{_brightness},
  maxBrightness{_maxBrightness}
{
}

void SysfsDevice::setMinimumValue(uint value)
{
  minimum = value;
}

void SysfsDevice::setPercentage(qint32 percentage)
{
  auto max = maxBrightness.read().toUInt();
  auto value = calcValue(max, percentage);
  brightness.write(QString::number(value));
}

uint SysfsDevice::calcValue(uint max, qint32 percentage) const
{
  if (minimum >= max) {
    return max;
  } else {
    return (percentage * (max-minimum) + 50) / 100 + minimum;
  }
}

