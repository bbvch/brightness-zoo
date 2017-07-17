/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "BrightnessControl.h"
#include "Device.mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSignalSpy>

using namespace testing;


class BrightnessControl_Test:
    public Test
{
public:
  NiceMock<Device_Mock> device;
  BrightnessControl testee{[this](){ return reducedPower; }, device};

  qint32 reducedPower{25};
  QSignalSpy error_spy{&testee, SIGNAL(error(QString))};
  QSignalSpy info_spy{&testee, SIGNAL(info(QString))};

  void SetUp() override
  {
    ASSERT_TRUE(error_spy.isValid());
    ASSERT_TRUE(info_spy.isValid());
  }

};


TEST_F(BrightnessControl_Test, forwards_brightness_in_normal_mode)
{
  EXPECT_CALL(device, setPercentage(55));

  testee.setBrightness(55);
}

TEST_F(BrightnessControl_Test, uses_reduced_value_when_in_powersave_mode)
{
  testee.setPowersave(true);

  EXPECT_CALL(device, setPercentage(20));

  testee.setBrightness(80);
}

TEST_F(BrightnessControl_Test, set_reduced_value_when_switching_into_powersave_mode)
{
  testee.setBrightness(80);

  EXPECT_CALL(device, setPercentage(20));

  testee.setPowersave(true);
}

TEST_F(BrightnessControl_Test, write_info_when_powersave_is_changed)
{
  reducedPower = 50;
  testee.setBrightness(80);
  info_spy.clear();

  testee.setPowersave(true);

  ASSERT_EQ(1, info_spy.count());
  ASSERT_EQ("set brightness percentage (40) based on brightness (80), powersave brightness percentage (50) and powersave (on)", info_spy.at(0).at(0).toString().toStdString());
}

TEST_F(BrightnessControl_Test, write_info_when_brightness_is_changed)
{
  reducedPower = 75;
  testee.setPowersave(false);
  info_spy.clear();

  testee.setBrightness(60);

  ASSERT_EQ(1, info_spy.count());
  ASSERT_EQ("set brightness percentage (60) based on brightness (60), powersave brightness percentage (75) and powersave (off)", info_spy.at(0).at(0).toString().toStdString());
}

TEST_F(BrightnessControl_Test, an_error_is_logged_when_the_brightness_percentage_is_too_low)
{

  reducedPower = -1;
  testee.setPowersave(true);

  ASSERT_EQ(1, error_spy.count());
  ASSERT_EQ("powersave brightness percentage (-1) is out of range (0-100)", error_spy.at(0).at(0).toString().toStdString());
}

TEST_F(BrightnessControl_Test, no_brightness_value_is_written_when_the_brightness_percentage_is_too_low)
{

  EXPECT_CALL(device, setPercentage(_))
      .Times(0);

  reducedPower = -1;
  testee.setPowersave(true);
}

TEST_F(BrightnessControl_Test, an_error_is_logged_when_the_brightness_percentage_is_too_high)
{

  reducedPower = 101;
  testee.setPowersave(true);

  ASSERT_EQ(1, error_spy.count());
  ASSERT_EQ("powersave brightness percentage (101) is out of range (0-100)", error_spy.at(0).at(0).toString().toStdString());
}

TEST_F(BrightnessControl_Test, no_brightness_value_is_written_when_the_brightness_percentage_is_too_high)
{

  EXPECT_CALL(device, setPercentage(_))
      .Times(0);

  reducedPower = 101;
  testee.setPowersave(true);
}
