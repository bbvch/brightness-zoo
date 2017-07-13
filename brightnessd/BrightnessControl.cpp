/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BrightnessControl.h"

BrightnessControl::BrightnessControl(qint32 _reducedPower, Device &_device) :
  reducedPower{_reducedPower},
  device{_device}
{
}

void BrightnessControl::setBrightness(qint32 value)
{
  brightness = value;
  updateCalculated();
}

qint32 BrightnessControl::getBrightness() const
{
  return brightness;
}

void BrightnessControl::setPowersave(bool value)
{
  powersave = value;
  updateCalculated();
}

bool BrightnessControl::getPowersave() const
{
  return powersave;
}

void BrightnessControl::updateCalculated()
{
  //TODO sanity checks
  qint32 finalBrightness = brightness;
  if (powersave) {
    finalBrightness = finalBrightness * reducedPower / 100;
  }
  device.setPercentage(finalBrightness);
}
