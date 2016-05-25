/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#include "ConfigurationReader.h"

#include <QCoreApplication>
#include <QSettings>

ConfigurationReader::ConfigurationReader(ConfigurationReader::Reader _reader) :
  reader{_reader}
{
}

unsigned ConfigurationReader::read(QString key, unsigned defaultValue) const
{
  bool ok;
  unsigned value = reader(key, defaultValue).toUInt(&ok);
  if (!ok) {
    value = defaultValue;
  }
  return value;
}

QSettingsReader::QSettingsReader() :
  ConfigurationReader{[&](QString key, QVariant defaultValue){
    return settings.value(key, defaultValue);
  }},
  settings{QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName()}
{
}
