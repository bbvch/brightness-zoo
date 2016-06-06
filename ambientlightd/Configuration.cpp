/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Configuration.h"

#include <ConfigurationReader.h>
#include <DbusCommandLine.h>

#include <QCommandLineParser>

static Configuration defaultConfiguration()
{
  Configuration result;

  result.device = "";
  result.single = false;
  result.updateInterval = std::chrono::minutes{1};
  result.bus = QDBusConnection{""};

  result.minAmbient = 1;
  result.minBrightness = 10;
  result.maxAmbient = 25000;
  result.maxBrightness = 100;

  return result;
}

static void parseCmdline(const QStringList &arguments, Configuration &configuration)
{
  QCommandLineParser parser;
  parser.addHelpOption();

  QCommandLineOption device{"device", "the root sysfs folder of the ambient light sensor", "path"};
  parser.addOption(device);

  QCommandLineOption single{"single", "read the sensor, write the brightness and exit"};
  parser.addOption(single);

  DbusCommandLine dbus{-3};
  parser.addOptions(dbus.options());

  parser.process(arguments);

  if (!parser.isSet(device)) {
    parser.showHelp(-2);
    return;
  }

  configuration.device = parser.value(device);
  configuration.single = parser.isSet(single);
  configuration.bus = dbus.parse(parser);
}

static void loadConfigurationFile(Configuration &configuration)
{
  QSettingsReader file;

  configuration.minAmbient = file.read("minAmbient", configuration.minAmbient);
  configuration.minBrightness = file.read("minBrightness", configuration.minBrightness);
  configuration.maxAmbient = file.read("maxAmbient", configuration.maxAmbient);
  configuration.maxBrightness = file.read("maxBrightness", configuration.maxBrightness);

  configuration.updateInterval = file.read("updateInterval", configuration.updateInterval);
}

Configuration loadConfiguration(const QStringList &arguments)
{
  Configuration configuration = defaultConfiguration();

  loadConfigurationFile(configuration);
  parseCmdline(arguments, configuration);

  return configuration;
}
