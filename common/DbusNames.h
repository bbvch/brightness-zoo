/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef DBUSNAMES_H
#define DBUSNAMES_H

#define DbusName_PowerInterface "ch.bbv.brightness.power"
#define DbusName_PowersaveInterface "ch.bbv.brightness.powersave"

#include <QString>

class DbusNames
{
public:
  static QString brightnessService();
  static QString brightnessPath();

};

#endif
