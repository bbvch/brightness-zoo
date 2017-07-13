/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>
#include <QStringList>
#include <QDBusConnection>

class Configuration
{
public:
  QString device;
  qint32 powersaveBrightnessPercentage;
  qint32 minimumBrightness;
  QDBusConnection bus{""};
};

Configuration loadConfiguration(const QStringList &arguments);

#endif
