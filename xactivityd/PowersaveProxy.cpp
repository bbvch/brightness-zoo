/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#include "PowersaveProxy.h"

PowersaveProxy::PowersaveProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent) :
  QDBusAbstractInterface(service, path, "ch.bbv.brightness.powersave", connection, parent)
{
}

bool PowersaveProxy::on() const
{
  return qvariant_cast< bool >(property("on"));
}

void PowersaveProxy::setOn(bool value)
{
  setProperty("on", QVariant::fromValue(value));
}

void PowersaveProxy::setOn()
{
  setOn(true);
}

void PowersaveProxy::setOff()
{
  setOn(false);
}

