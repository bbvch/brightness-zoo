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

#include <QObject>

class BrightnessControl :
    public QObject,
    public Brightness,
    public Powersave
{
  Q_OBJECT
public:
  explicit BrightnessControl(QObject *parent = 0);

  void setBrightness(qint32) override;
  qint32 getBrightness() override;

  void setPowersave(bool) override;
  bool getPowersave() override;

signals:
  void brightnessChanged(qint32 value);

private:
  qint32 brightness{100};
  bool powersave{false};

  void updateCalculated();

};

#endif
