/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "AmbientLightD.h"

AmbientLightD::AmbientLightD(sysfs::Reader &_ambientLight, AmbientToBrightness &_convert, Brightness &_brightness, QObject *parent) :
  QObject{parent},
  ambientLight{_ambientLight},
  convert{_convert},
  brightness{_brightness}
{
}

void AmbientLightD::check()
{
  const auto lux = ambientLight.read().toInt();
  const auto brightness = convert.brigthnessFromLux(lux);
  this->brightness.setBrightness(brightness);
}
