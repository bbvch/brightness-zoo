/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "AmbientLightD.h"
#include "convert/LinearConfiguration.h"
#include "convert/LinearWithSaturation.h"
#include "BrightnessProxy.h"
#include "Configuration.h"
#include <sysfs/RoValue.h>
#include <DbusNames.h>

#include <QCoreApplication>
#include <QTimer>
#include <iostream>
#include <chrono>


int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName("brightness-zoo");
  QCoreApplication::setApplicationName("ambientlightd");

  QCoreApplication app(argc, argv);

  const auto configuration = loadConfiguration(app.arguments());

  sysfs::RoValue sensor{configuration.device + "/in_illuminance_input"};
  LinearWithSaturation convert{configuration};

  BrightnessProxy brightness{DbusNames::brightnessService(), DbusNames::brightnessPath(), configuration.bus};
  if (!brightness.isValid()) {
    std::cerr << "could not connect to service " << brightness.service().toStdString() << " path " << brightness.path().toStdString() << ":" << std::endl;
    std::cerr << brightness.lastError().message().toStdString() << std::endl;
    return -4;
  }

  AmbientLightD ambientLight{sensor, convert, brightness};

  ambientLight.check();

  if (configuration.single) {
    return 0;
  }

  QTimer timer;

  QObject::connect(&timer, SIGNAL(timeout()), &ambientLight, SLOT(check()));

  auto const updateInMilliseconds = std::chrono::milliseconds{configuration.updateInterval}.count();
  timer.setInterval(updateInMilliseconds);
  timer.setSingleShot(false);
  timer.start();

  return app.exec();
}
