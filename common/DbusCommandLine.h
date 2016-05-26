/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef DBUSCOMMANDLINE_H
#define DBUSCOMMANDLINE_H

#include <QList>
#include <QCommandLineOption>
#include <QCommandLineParser>
#include <QDBusConnection>

class DbusCommandLine
{
public:
  DbusCommandLine(int errorCode = -1);

  QList<QCommandLineOption> options() const;

  QDBusConnection parse(const QCommandLineParser &parser) const;

private:
  QCommandLineOption session{"session", "use the session bus instead of the system bus"};
  int errorCode;

};

#endif
