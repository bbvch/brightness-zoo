/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef SYSFSDEVICE_H
#define SYSFSDEVICE_H

#include "Device.h"
#include <sysfs/Writer.h>
#include <sysfs/Reader.h>

#include <QObject>
#include <functional>

class SysfsDevice :
    public QObject,
    public Device
{
  Q_OBJECT
public:
  SysfsDevice(sysfs::Writer &brightness, sysfs::Reader &maxBrightness, std::function<qint32()> minimum);

signals:
  void error(QString);
  void info(QString);

public slots:
  void setPercentage(qint32);

private:
  sysfs::Writer &brightness;
  sysfs::Reader &maxBrightness;
  std::function<qint32()> minimum;

};

#endif
