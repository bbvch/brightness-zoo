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

#include <QCoreApplication>
#include <QCommandLineParser>
#include <iostream>

static QString parseCmdline(const QStringList &arguments) {
  QCommandLineParser parser;
  parser.addHelpOption();

  QCommandLineOption device{"device", "the root sysfs folder of the brightness device", "path"};
  parser.addOption(device);

  parser.process(arguments);

  if (!parser.isSet(device)) {
    parser.showHelp(-2);
    return {};
  }

  return parser.value(device);
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

  const auto root = parseCmdline(app.arguments());

  auto bus = QDBusConnection::sessionBus();

  if (!bus.isConnected()) {
    std::cerr << "bus not connected" << std::endl;
    return -3;
  }

  if(!bus.registerService(DbusNames::brightnessService())) {
      std::cerr << "Could not register service" << std::endl;
      return -4;
  }

  sysfs::WoValue brightnessFile{root + "/brightness"};
  sysfs::RoValue maxBrightnessFile{root + "/max_brightness"};
  SysfsDevice device{brightnessFile, maxBrightnessFile};

  BrightnessControl control{powersaveBrightnessPercentage(), device};

  new dbus::brightness::Power(control, &app);
  new dbus::brightness::PowerSave(control, &app);

  if(!bus.registerObject(DbusNames::brightnessPath(), &app)){
    std::cerr << "Could not register object" << std::endl;
    return -5;
  }

  return app.exec();
}
