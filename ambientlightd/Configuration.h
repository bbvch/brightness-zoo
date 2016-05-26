/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "convert/LinearConfiguration.h"

#include <QString>
#include <QStringList>
#include <chrono>
#include <QDBusConnection>

class Configuration :
    public LinearConfiguration
{
public:
  std::chrono::seconds updateInterval;
  QString device;
  bool single;
  QDBusConnection bus{""};
};

Configuration loadConfiguration(const QStringList &arguments);

#endif
