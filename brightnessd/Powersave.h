/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef POWERSAVE_H
#define POWERSAVE_H

class Powersave
{
public:
  virtual ~Powersave() = default;

  virtual void setPowersave(bool) = 0;
  virtual bool getPowersave() const = 0;

};

#endif
