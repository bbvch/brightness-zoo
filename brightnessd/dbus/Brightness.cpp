/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Brightness.h"

namespace dbus
{
namespace brightness
{


Power::Power(Brightness &_brightness, QObject *parent) :
  QDBusAbstractAdaptor(parent),
  brightness{_brightness}
{
}

qint32 Power::getPercentage() const
{
  return brightness.getBrightness();
}

void Power::setPercentage(qint32 value)
{
  brightness.setBrightness(value);
}


PowerSave::PowerSave(Powersave &_powersave, QObject *parent) :
  QDBusAbstractAdaptor(parent),
  powersave{_powersave}
{
}

bool PowerSave::getOn() const
{
  return powersave.getPowersave();
}

void PowerSave::setOn(bool value)
{
  powersave.setPowersave(value);
}

}
}
