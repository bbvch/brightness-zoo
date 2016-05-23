/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef DEVICE_H
#define DEVICE_H

#include <QtGlobal>

class Device
{
public:
  virtual ~Device() = default;

  virtual void setPercentage(qint32 percentage) = 0;

};

#endif
