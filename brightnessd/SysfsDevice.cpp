/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "SysfsDevice.h"

#include "CheckedBlock.h"
#include "ValueCheck.h"
#include "print.h"


SysfsDevice::SysfsDevice(sysfs::Writer &_brightness, sysfs::Reader &_maxBrightness, std::function<qint32()> _minimum) :
  brightness{_brightness},
  maxBrightness{_maxBrightness},
  minimum{_minimum}
{
}

void SysfsDevice::setPercentage(qint32 percentage)
{
  struct Context
  {
    const qint32 minimum;
    const qint32 maximum;
    const qint32 percentage;
    qint32 value{};
  };

  const auto maximum = maxBrightness.read().toInt();
  Context context{minimum(), maximum, percentage};

  execute([&context](){
    return inRange(0, context.percentage, 100, "brightness percentage");
  }).then([&context](){
    return greater(context.maximum, 0, "maximum value");
  }).then([&context](){
    return inRange(0, context.minimum, context.maximum, "minimum value");
  }).then([&context](){
    const auto normalized = context.maximum-context.minimum;
    const auto by_percent = (context.percentage * normalized + 50) / 100;
    context.value = by_percent + context.minimum;
    return inRange(context.minimum, context.value, context.maximum, "calculated brightness value");
  }).then([this, &context](){
    info(setText(
           {"brightness value", toString(context.value)},
           {"percentage", toString(context.percentage)},
           {"minimum brightness", toString(context.minimum)},
           {"maximum brightness", toString(context.maximum)}));

    brightness.write(QString::number(context.value));
    return Ok();
  }).thenOnError([this](const std::string &message){
    error(QString::fromStdString(message));
  });
}
