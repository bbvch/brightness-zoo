/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 * SPDX-License-Identifier:	GPL-2.0
 */

#ifndef POWERSAVEPROXY_H
#define POWERSAVEPROXY_H

#include <QObject>

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

class PowersaveProxy :
    public QDBusAbstractInterface
{
  Q_OBJECT

  Q_PROPERTY(bool on READ on WRITE setOn)

public:
  PowersaveProxy(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

  bool on() const;
  void setOn(bool value);

public slots:
  void setOn();
  void setOff();

};

#endif
