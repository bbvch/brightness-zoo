/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef LINEARWITHSATURATION_H
#define LINEARWITHSATURATION_H

#include "LinearConfiguration.h"
#include "AmbientToBrightness.h"

class LinearWithSaturation :
    public AmbientToBrightness
{
public:
  LinearWithSaturation(const LinearConfiguration &configuration);

  int brigthnessFromAmbient(int) const override;

private:
  class Point
  {
  public:
    int x;
    int y;
  };

  const Point min;
  const Point max;

};

#endif
