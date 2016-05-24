/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#ifndef DBUS_BRIGHTNESS_H
#define DBUS_BRIGHTNESS_H

#include <Brightness.h>
#include <Powersave.h>
#include <DbusNames.h>

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
  Q_CLASSINFO("D-Bus Interface", DbusName_PowerInterface)

  Q_PROPERTY(qint32 percentage READ getPercentage WRITE setPercentage)

public:
  Power(Brightness &brightness, QObject *parent);

private:
  Brightness &brightness;

  qint32 getPercentage() const;
  void setPercentage(qint32 value);

};

class PowerSave :
    public QDBusAbstractAdaptor
{
  Q_OBJECT
  Q_CLASSINFO("D-Bus Interface", DbusName_PowersaveInterface)

  Q_PROPERTY(bool on READ getOn WRITE setOn)

public:
  PowerSave(Powersave &powersave, QObject *parent);

private:
  Powersave &powersave;

  bool getOn() const;
  void setOn(bool value);

};


}
}

#endif
