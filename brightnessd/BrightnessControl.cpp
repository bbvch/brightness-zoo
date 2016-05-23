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
  if (powersave) {
    value = value / 2;
  }
  brightnessChanged(value);
}

void BrightnessControl::setPowersave(bool value)
{
  powersave = value;
  qint32 finalBrightness = brightness;
  if (powersave) {
    finalBrightness = finalBrightness / 2;
  }
  brightnessChanged(finalBrightness);
}
