/*
 * (C) Copyright 2016-2025
 * Adapted for Framebuffer use
 *
 * SPDX-License-Identifier: GPL-2.0
 */

#include "ActivityNotifier.h"
#include "PowersaveProxy.h"
#include "FramebufferIdle.h"
#include "Configuration.h"

#include "DbusNames.h"

#include <QCoreApplication>
#include <QTimer>
#include <iostream>
#include <chrono>

int main(int argc, char *argv[])
{
  QCoreApplication::setOrganizationName("brightness-zoo");
  QCoreApplication::setApplicationName("fbactivityd");

  QCoreApplication app(argc, argv);

  const auto configuration = loadConfiguration(app.arguments());

  PowersaveProxy powersave{DbusNames::brightnessService(), DbusNames::brightnessPath(), configuration.bus};
  if (!powersave.isValid()) {
    std::cerr << "could not connect to service " << powersave.service().toStdString() 
              << " path " << powersave.path().toStdString() << ":" << std::endl;
    std::cerr << powersave.lastError().message().toStdString() << std::endl;
    return -2;
  }

  try {
    FramebufferIdle idle{};
    idle.start();  // Start monitoring input devices
    
    ActivityNotifier notifier{configuration.activityTimeout, [&idle](){return idle();}};
    QTimer timer;

    QObject::connect(&timer, SIGNAL(timeout()), &notifier, SLOT(check()));
    QObject::connect(&notifier, SIGNAL(active()), &powersave, SLOT(setOff()));
    QObject::connect(&notifier, SIGNAL(inactive()), &powersave, SLOT(setOn()));

    timer.setInterval(333);
    timer.setSingleShot(false);
    timer.start();

    std::cout << "Framebuffer activity monitor started successfully" << std::endl;
    
    return app.exec();
    
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return -1;
  }
}