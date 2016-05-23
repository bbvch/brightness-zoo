/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H

#include <QObject>
#include <QtDBus>

namespace dbus
{
namespace brightness
{


class Power :
    public QDBusAbstractAdaptor
{
  Q_OBJECT
  Q_CLASSINFO("D-Bus Interface", "ch.bbv.brightness.power")

  Q_PROPERTY(qint32 percentage READ getPercentage WRITE setPercentage NOTIFY percentageChanged)

public:
  Power(QObject *parent);

signals:
  void percentageChanged(qint32 value);

private:
  qint32 percentage = 0;

  qint32 getPercentage() const;
  void setPercentage(qint32 value);

};

class PowerSave :
    public QDBusAbstractAdaptor
{
  Q_OBJECT
  Q_CLASSINFO("D-Bus Interface", "ch.bbv.brightness.powersave")

  Q_PROPERTY(bool on READ getOn WRITE setOn NOTIFY onChanged)

public:
  PowerSave(QObject *parent);

signals:
  void onChanged(bool value);

private:
  bool on = 0;

  bool getOn() const;
  void setOn(bool value);

};


}
}

#endif
