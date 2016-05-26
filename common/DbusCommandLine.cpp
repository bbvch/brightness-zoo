/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#include "DbusCommandLine.h"

#include <iostream>

DbusCommandLine::DbusCommandLine(int _errorCode) :
  errorCode{_errorCode}
{
}

QList<QCommandLineOption> DbusCommandLine::options() const
{
  return {session};
}

QDBusConnection DbusCommandLine::parse(const QCommandLineParser &parser) const
{
  auto bus = parser.isSet(session) ? QDBusConnection::sessionBus() : QDBusConnection::systemBus();

  if (!bus.isConnected()) {
    std::cerr << "bus not connected" << std::endl;
    QCoreApplication::exit(errorCode);
  }

  return bus;
}
