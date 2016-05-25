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
#include <sysfs/RoValue.h>
#include <DbusNames.h>
#include <Configuration.h>

#include <QCoreApplication>
#include <QTimer>
#include <QCommandLineParser>
#include <iostream>

static QString parseCmdline(const QStringList &arguments) {
  QCommandLineParser parser;
  parser.addHelpOption();

  QCommandLineOption device{"device", "the root sysfs folder of the ambient light sensor", "path"};
  parser.addOption(device);

  QCommandLineOption single{"single", "read the sensor, write the brightness and exit"};
  parser.addOption(single);

  parser.process(arguments);

  if (!parser.isSet(device)) {
    parser.showHelp(-1);
    return {};
  }

  return parser.value(device);
}

static LinearConfiguration loadConfiguration()
{
  QSettingsConfig file;

  LinearConfiguration result;

  result.minAmbient = file.read("minLux", 1);
  result.minBrightness = file.read("minBrightness", 10);
  result.maxAmbient = file.read("maxLux", 25000);
  result.maxBrightness = file.read("maxBrightness", 100);

  return result;
}

int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName("brightness-zoo");
  QCoreApplication::setApplicationName("ambientlightd");

  QCoreApplication app(argc, argv);

  const auto device = parseCmdline(app.arguments());

  sysfs::RoValue sensor{device + "/in_illuminance_input"};
  LinearWithSaturation convert{loadConfiguration()};
  BrightnessProxy brightness{DbusNames::brightnessService(), DbusNames::brightnessPath(), QDBusConnection::sessionBus()};
  if (!brightness.isValid()) {
    std::cerr << "could not connect to service " << brightness.service().toStdString() << " path " << brightness.path().toStdString() << ":" << std::endl;
    std::cerr << brightness.lastError().message().toStdString() << std::endl;
    return -1;
  }

  AmbientLightD ambientLight{sensor, convert, brightness};

  QTimer::singleShot(0, &ambientLight, SLOT(check()));
  QTimer::singleShot(0, &app, SLOT(quit()));

  return app.exec();
}
