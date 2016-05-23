/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef DEVICE_H
#define DEVICE_H

#include "sysfs/Writer.h"
#include "sysfs/Reader.h"

#include <QObject>

class Device : public QObject
{
  Q_OBJECT
public:
  Device(sysfs::Writer &brightness, sysfs::Reader &maxBrightness);

signals:

public slots:
  void setPercentage(qint32 percentage);

private:
  sysfs::Writer &brightness;
  sysfs::Reader &maxBrightness;

};

#endif
