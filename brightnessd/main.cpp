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

#include <Configuration.h>
#include <DbusNames.h>

#include <QCoreApplication>
#include <QCommandLineParser>
#include <iostream>

static QString parseCmdline(const QStringList &arguments) {
  QCommandLineParser parser;
  QCommandLineOption device{"device", "the root sysfs folder of the brightness device", "path"};
  parser.addOption(device);

  if (!parser.parse(arguments)) {
    std::cerr << "could not parse options: " + parser.errorText().toStdString() << std::endl;
    return {};
  }

  return parser.value(device);
}

static unsigned powersaveBrightnessPercentage()
{
  QSettingsConfig configuration;
  return configuration.read("powersaveBrightnessPercentage", 50);
}

int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName("brightness-zoo");
  QCoreApplication::setApplicationName("brightnessd");

  QCoreApplication app(argc, argv);

  const auto root = parseCmdline(app.arguments());
  if (root == "") {
    //TODO print error message
    return -1;
  }

  auto bus = QDBusConnection::sessionBus();

  if (!bus.isConnected()) {
    std::cerr << "bus not connected" << std::endl;
    return -1;
  }

  if(!bus.registerService(DbusNames::brightnessService()))
  {
      std::cerr << "Could not register service" << std::endl;
      return -1;
  }

  sysfs::WoValue brightnessFile{root + "/brightness"};
  sysfs::RoValue maxBrightnessFile{root + "/max_brightness"};
  SysfsDevice device{brightnessFile, maxBrightnessFile};

  BrightnessControl control{powersaveBrightnessPercentage(), device};

  new dbus::brightness::Power(control, &app);
  new dbus::brightness::PowerSave(control, &app);

  if(!bus.registerObject(DbusNames::brightnessPath(), &app)){
    std::cerr << "Could not register object" << std::endl;
    return -1;
  }

  return app.exec();
}
