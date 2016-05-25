/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <QtGlobal>

class Brightness
{
public:
  virtual ~Brightness() = default;

  virtual void setBrightness(qint32) = 0;
  virtual qint32 getBrightness() const = 0;

};

#endif
