/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESSPROXY_H
#define BRIGHTNESSPROXY_H

#include <Brightness.h>

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

class BrightnessProxy :
    public QDBusAbstractInterface,
    public Brightness
{
  Q_OBJECT

  Q_PROPERTY(qint32 percentage READ getBrightness WRITE setBrightness)

public:
  BrightnessProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

  void setBrightness(qint32) override;
  qint32 getBrightness() const override;

};

#endif
