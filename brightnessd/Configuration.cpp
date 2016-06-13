/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Configuration.h"

#include <DbusCommandLine.h>
#include <ConfigurationReader.h>

#include <QCommandLineParser>

static Configuration defaultConfiguration()
{
  Configuration result;

  result.device = "";
  result.bus = QDBusConnection{""};
  result.powersaveBrightnessPercentage = 50;
  result.minimumBrightness = 0;

  return result;
}

static void parseCmdline(const QStringList &arguments, Configuration &configuration)
{
  QCommandLineParser parser;
  parser.addHelpOption();

  QCommandLineOption device{"device", "the root sysfs folder of the brightness device", "path"};
  parser.addOption(device);

  DbusCommandLine dbus{-3};
  parser.addOptions(dbus.options());

  parser.process(arguments);

  if (!parser.isSet(device)) {
    parser.showHelp(-2);
  }

  configuration.device = parser.value(device);
  configuration.bus = dbus.parse(parser);
}

static void loadConfigurationFile(Configuration &configuration)
{
  QSettingsReader file;

  configuration.powersaveBrightnessPercentage = file.read("powersaveBrightnessPercentage", configuration.powersaveBrightnessPercentage);
  configuration.minimumBrightness = file.read("minimumBrightness", configuration.minimumBrightness);
}

Configuration loadConfiguration(const QStringList &arguments)
{
  Configuration configuration = defaultConfiguration();

  loadConfigurationFile(configuration);
  parseCmdline(arguments, configuration);

  return configuration;
}
