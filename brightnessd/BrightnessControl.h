/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESSCONTROL_H
#define BRIGHTNESSCONTROL_H

#include <QObject>

class BrightnessControl : public QObject
{
  Q_OBJECT
public:
  explicit BrightnessControl(QObject *parent = 0);

signals:
  void brightnessChanged(qint32 value);

public slots:
  void setBrightness(qint32 value);
  void setPowersave(bool value);

private:
  qint32 brightness{100};
  bool powersave{false};

};

#endif
