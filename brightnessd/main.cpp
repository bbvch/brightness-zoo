/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "dbus/Brightness.h"
#include "sysfs/WoValue.h"
#include "sysfs/RoValue.h"
#include "SysfsDevice.h"
#include "BrightnessControl.h"

#include <ConfigurationReader.h>
#include <DbusNames.h>
#include <DbusCommandLine.h>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <iostream>


class Configuration
{
public:
  QString device;
  QDBusConnection bus{""};
};

static Configuration parseCmdline(const QStringList &arguments)
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

  Configuration configuration;
  configuration.device = parser.value(device);
  configuration.bus = dbus.parse(parser);

  return configuration;
}

static unsigned powersaveBrightnessPercentage()
{
  QSettingsReader configuration;
  return configuration.read("powersaveBrightnessPercentage", 50);
}

int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName("brightness-zoo");
  QCoreApplication::setApplicationName("brightnessd");

  QCoreApplication app(argc, argv);

  const auto configuration = parseCmdline(app.arguments());

  sysfs::WoValue brightnessFile{configuration.device + "/brightness"};
  sysfs::RoValue maxBrightnessFile{configuration.device + "/max_brightness"};
  SysfsDevice device{brightnessFile, maxBrightnessFile};

  BrightnessControl control{powersaveBrightnessPercentage(), device};

  new dbus::brightness::Power(control, &app);
  new dbus::brightness::PowerSave(control, &app);

  auto bus = configuration.bus;

  if (!bus.registerService(DbusNames::brightnessService())) {
      std::cerr << "Could not register service" << std::endl;
      return -4;
  }

  if(!bus.registerObject(DbusNames::brightnessPath(), &app)){
    std::cerr << "Could not register object" << std::endl;
    return -5;
  }

  return app.exec();
}
