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
#include <QTime>

ConfigurationReader::ConfigurationReader(ConfigurationReader::Reader _reader) :
  reader{_reader}
{
}

qint32 ConfigurationReader::read(QString key, qint32 defaultValue) const
{
  //TODO check for nearly correct value
  bool ok;
  qint32 value = reader(key, defaultValue).toInt(&ok);
  if (!ok) {
    value = defaultValue;
  }
  return value;
}

std::chrono::seconds ConfigurationReader::read(QString key, std::chrono::seconds defaultValue) const
{
  const auto defaultString = QTime::fromMSecsSinceStartOfDay(defaultValue.count() * 1000).toString("m:ss");
  const QString raw = reader(key, defaultString).toString();
  const QTime time = QTime::fromString(raw, "m:ss");
  if (time.isValid()) {
    return std::chrono::seconds{time.msecsSinceStartOfDay() / 1000};
  } else {
    return defaultValue;
  }
}

QSettingsReader::QSettingsReader() :
  ConfigurationReader{[&](QString key, QVariant defaultValue){
    return settings.value(key, defaultValue);
  }},
  settings{QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName()}
{
}
