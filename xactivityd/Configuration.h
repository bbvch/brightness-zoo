/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QStringList>
#include <QDBusConnection>
#include <chrono>

class Configuration
{
public:
  std::chrono::seconds activityTimeout;
  QDBusConnection bus{""};
};

Configuration loadConfiguration(const QStringList &arguments);

#endif
