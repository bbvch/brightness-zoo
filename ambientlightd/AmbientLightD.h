/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef AMBIENTLIGHTD_H
#define AMBIENTLIGHTD_H

#include "convert/AmbientToBrightness.h"

#include <Brightness.h>
#include <sysfs/Reader.h>

#include <QObject>

class AmbientLightD :
    public QObject
{
  Q_OBJECT
public:
  AmbientLightD(sysfs::Reader &ambientLight, AmbientToBrightness &convert, Brightness &brightness, QObject *parent = 0);

public slots:
  void check();

private:
  sysfs::Reader &ambientLight;
  AmbientToBrightness &convert;
  Brightness &brightness;

};

#endif
