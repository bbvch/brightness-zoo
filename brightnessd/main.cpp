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
#include "Configuration.h"
#include "ProblemHandler.h"

#include <DbusNames.h>

#include <QCoreApplication>
#include <iostream>


int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName("brightness-zoo");
  QCoreApplication::setApplicationName("brightnessd");

  QCoreApplication app(argc, argv);

  const auto configuration = loadConfiguration(app.arguments());

  sysfs::WoValue brightnessFile{configuration.device + "/brightness"};
  sysfs::RoValue maxBrightnessFile{configuration.device + "/max_brightness"};
  SysfsDevice device{brightnessFile, maxBrightnessFile, [&configuration](){ return configuration.minimumBrightness; }};

  BrightnessControl control{[&configuration](){ return configuration.powersaveBrightnessPercentage; }, device};
  ProblemHandler problemHandler{configuration.verbose};

  QObject::connect(&device, SIGNAL(error(QString)), &problemHandler, SLOT(error(QString)));
  QObject::connect(&device, SIGNAL(info(QString)), &problemHandler, SLOT(info(QString)));
  QObject::connect(&control, SIGNAL(error(QString)), &problemHandler, SLOT(error(QString)));
  QObject::connect(&control, SIGNAL(info(QString)), &problemHandler, SLOT(info(QString)));

  new dbus::brightness::Power(control, &app);
  new dbus::brightness::PowerSave(control, &app);

  auto bus = configuration.bus;

  if (!bus.registerService(DbusNames::brightnessService())) {
      std::cerr << "Could not register service" << std::endl;
      return -4;
  }

  if (!bus.registerObject(DbusNames::brightnessPath(), &app)){
    std::cerr << "Could not register object" << std::endl;
    return -5;
  }

  return app.exec();
}
