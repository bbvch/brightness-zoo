/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <functional>
#include <QVariant>
#include <QString>
#include <QSettings>

class Configuration
{
public:
  typedef std::function<QVariant(QString key, QVariant defaultValue)> Reader;

  Configuration(Reader reader);

  unsigned read(QString key, unsigned defaultValue) const;

private:
  Reader reader;

};

class QSettingsConfig :
    public Configuration
{
public:
  QSettingsConfig();

private:
  QSettings settings;

};

#endif
