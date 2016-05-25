/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef CONFIGURATIONREADER_H
#define CONFIGURATIONREADER_H

#include <functional>
#include <QVariant>
#include <QString>
#include <QSettings>

class ConfigurationReader
{
public:
  typedef std::function<QVariant(QString key, QVariant defaultValue)> Reader;

  ConfigurationReader(Reader reader);

  unsigned read(QString key, unsigned defaultValue) const;

private:
  Reader reader;

};

class QSettingsReader :
    public ConfigurationReader
{
public:
  QSettingsReader();

private:
  QSettings settings;

};

#endif
