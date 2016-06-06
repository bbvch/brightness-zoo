/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef AMBIENTTOBRIGHTNESS_H
#define AMBIENTTOBRIGHTNESS_H

class AmbientToBrightness
{
public:
  virtual ~AmbientToBrightness() = default;

  virtual int brigthnessFromAmbient(int) const = 0;

};

#endif
