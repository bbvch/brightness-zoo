/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#pragma once

#include "Brightness.h"
#include "Powersave.h"
#include "Device.h"

#include <QObject>
#include <functional>

class BrightnessControl :
    public QObject,
    public Brightness,
    public Powersave
{
  Q_OBJECT

public:
  BrightnessControl(std::function<qint32()> reducedPower, Device &device);

  void setBrightness(qint32) override;
  qint32 getBrightness() const override;

  void setPowersave(bool) override;
  bool getPowersave() const override;

signals:
  void error(QString message);

private:
  std::function<qint32()> reducedPower;
  qint32 brightness{100};
  bool powersave{false};
  Device &device;

  void updateCalculated();

};
