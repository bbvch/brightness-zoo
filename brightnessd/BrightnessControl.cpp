/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BrightnessControl.h"

#include "CheckedBlock.h"
#include "ValueCheck.h"
#include "print.h"

BrightnessControl::BrightnessControl(std::function<qint32()> _reducedPower, Device &_device) :
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
  const qint32 reduced = reducedPower();

  execute([reduced](){
    return inRange(0, reduced, 100, "powersave brightness percentage");
  }).then([reduced, this](){
    qint32 finalBrightness = brightness;
    if (powersave) {
      finalBrightness = finalBrightness * reduced / 100;
    }

    info(setText(
           {"brightness percentage", toString(finalBrightness)},
           {"brightness", toString(brightness)},
           {"powersave brightness percentage", toString(reduced)},
           {"powersave", toString(powersave)}));
    device.setPercentage(finalBrightness);

    return Ok();
  }).thenOnError([this](const std::string &message){
    error(QString::fromStdString(message));
  });
}
