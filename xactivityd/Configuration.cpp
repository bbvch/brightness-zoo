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

  result.activityTimeout = std::chrono::minutes{2};
  result.bus = QDBusConnection{""};

  return result;
}

static void parseCmdline(const QStringList &arguments, Configuration &configuration)
{
  QCommandLineParser parser;
  parser.addHelpOption();

  DbusCommandLine dbus{-3};
  parser.addOptions(dbus.options());

  parser.process(arguments);

  configuration.bus = dbus.parse(parser);
}

static void loadConfigurationFile(Configuration &configuration)
{
  QSettingsReader file;

  configuration.activityTimeout = file.read("activityTimeout", configuration.activityTimeout);
}

Configuration loadConfiguration(const QStringList &arguments)
{
  Configuration configuration = defaultConfiguration();

  loadConfigurationFile(configuration);
  parseCmdline(arguments, configuration);

  return configuration;
}
