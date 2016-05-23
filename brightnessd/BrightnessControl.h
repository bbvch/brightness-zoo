/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESSCONTROL_H
#define BRIGHTNESSCONTROL_H

#include "Brightness.h"
#include "Powersave.h"
#include "Device.h"

#include <QtGlobal>

class BrightnessControl :
    public Brightness,
    public Powersave
{
public:
  BrightnessControl(Device &device);

  void setBrightness(qint32) override;
  qint32 getBrightness() override;

  void setPowersave(bool) override;
  bool getPowersave() override;

private:
  qint32 brightness{100};
  bool powersave{false};
  Device &device;

  void updateCalculated();

};

#endif
