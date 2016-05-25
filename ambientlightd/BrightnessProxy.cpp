/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BrightnessProxy.h"

#include <DbusNames.h>

BrightnessProxy::BrightnessProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent) :
  QDBusAbstractInterface(service, path, DbusName_PowerInterface, connection, parent)
{
}

void BrightnessProxy::setBrightness(qint32 value)
{
  setProperty("percentage", QVariant::fromValue(value));
}

qint32 BrightnessProxy::getBrightness() const
{
  return qvariant_cast<qint32>(property("percentage"));
}
