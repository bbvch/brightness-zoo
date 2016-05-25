/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-2.0
 */

#include "ActivityNotifier.h"
#include "PowersaveProxy.h"
#include "Xidle.h"

#include <ConfigurationReader.h>
#include <DbusNames.h>

#include <QCoreApplication>
#include <QTimer>
#include <iostream>
#include <chrono>

static std::chrono::minutes activityTimeout()
{
  QSettingsReader configuration;

  uint value = configuration.read("activityTimeoutInMinutes", 2);
  return std::chrono::minutes{value};
}

int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName("brightness-zoo");
  QCoreApplication::setApplicationName("xactivityd");

  QCoreApplication app(argc, argv);

  PowersaveProxy powersave{DbusNames::brightnessService(), DbusNames::brightnessPath(), QDBusConnection::sessionBus()};
  if (!powersave.isValid()) {
    std::cerr << "could not connect to service " << powersave.service().toStdString() << " path " << powersave.path().toStdString() << ":" << std::endl;
    std::cerr << powersave.lastError().message().toStdString() << std::endl;
    return -1;
  }

  Xidle idle{};
  ActivityNotifier notifier{activityTimeout(), [&idle](){return idle();}};
  QTimer timer;

  QObject::connect(&timer, SIGNAL(timeout()), &notifier, SLOT(check()));
  QObject::connect(&notifier, SIGNAL(active()), &powersave, SLOT(setOff()));
  QObject::connect(&notifier, SIGNAL(inactive()), &powersave, SLOT(setOn()));

  timer.setInterval(333);
  timer.setSingleShot(false);
  timer.start();

  return app.exec();
}
