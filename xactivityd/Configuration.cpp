/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#include "Configuration.h"

#include <QCoreApplication>
#include <QSettings>

std::chrono::minutes activityTimeout()
{
  QSettings settings{QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName()};

  const uint DefaultTimeout = 2;
  bool ok;
  uint value = settings.value("activityTimeoutInMinutes", DefaultTimeout).toUInt(&ok);

  if (!ok) {
    value = DefaultTimeout;
  }

  return std::chrono::minutes{value};
}
