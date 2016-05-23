/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BrightnessControl.h"

BrightnessControl::BrightnessControl(QObject *parent) : QObject(parent)
{

}

void BrightnessControl::setBrightness(qint32 value)
{
  brightness = value;
  updateCalculated();
}

qint32 BrightnessControl::getBrightness()
{
  return brightness;
}

void BrightnessControl::setPowersave(bool value)
{
  powersave = value;
  updateCalculated();
}

bool BrightnessControl::getPowersave()
{
  return powersave;
}

void BrightnessControl::updateCalculated()
{
  qint32 finalBrightness = brightness;
  if (powersave) {
    finalBrightness = finalBrightness / 2;
  }
  brightnessChanged(finalBrightness);
}
