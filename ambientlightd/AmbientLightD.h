/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef AMBIENTLIGHTD_H
#define AMBIENTLIGHTD_H

#include "convert/AmbientToBrightness.h"
#include "sensor/AmbientLightSensor.h"

#include <Brightness.h>

#include <QObject>

class AmbientLightD :
    public QObject
{
  Q_OBJECT
public:
  AmbientLightD(AmbientLightSensor &ambientLight, AmbientToBrightness &convert, Brightness &brightness, QObject *parent = 0);

public slots:
  void check();

private:
  AmbientLightSensor &ambientLight;
  AmbientToBrightness &convert;
  Brightness &brightness;

};

#endif
