/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#include "DbusNames.h"

QString DbusNames::brightnessService()
{
  return "ch.bbv.brightness";
}

QString DbusNames::brightnessPath()
{
  return "/ch/bbv/brightness";
}
