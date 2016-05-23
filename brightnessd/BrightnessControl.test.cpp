/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BrightnessControl.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSignalSpy>

class BrightnessControl_Test:
    public testing::Test
{
public:
  BrightnessControl testee{};
  QSignalSpy brightnessSpy{&testee, SIGNAL(brightnessChanged(qint32))};

};


TEST_F(BrightnessControl_Test, forwards_brightness_in_normal_mode)
{
  testee.setBrightness(55);

  ASSERT_EQ(1, brightnessSpy.count());
  ASSERT_EQ(1, brightnessSpy[0].count());
  ASSERT_EQ(55, brightnessSpy[0][0]);
}

TEST_F(BrightnessControl_Test, uses_reduced_value_when_in_powersave_mode)
{
  testee.setPowersave(true);
  brightnessSpy.clear();

  testee.setBrightness(80);

  ASSERT_EQ(1, brightnessSpy.count());
  ASSERT_EQ(1, brightnessSpy[0].count());
  ASSERT_EQ(40, brightnessSpy[0][0]);
}

TEST_F(BrightnessControl_Test, set_reduced_value_when_switching_into_powersave_mode)
{
  testee.setBrightness(80);
  brightnessSpy.clear();

  testee.setPowersave(true);

  ASSERT_EQ(1, brightnessSpy.count());
  ASSERT_EQ(1, brightnessSpy[0].count());
  ASSERT_EQ(40, brightnessSpy[0][0]);
}
