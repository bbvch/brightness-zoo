/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "SysfsDevice.h"

#include "sysfs/Writer.mock.h"
#include "sysfs/Reader.mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSignalSpy>

using namespace testing;

class SysfsDevice_Test:
    public Test
{
public:
  NiceMock<sysfs::Writer_Mock> brightness;
  NiceMock<sysfs::Reader_Mock> maxBrightness;
  SysfsDevice testee{brightness, maxBrightness, [this](){ return minimum; }};

  qint32 minimum{};
  QSignalSpy error_spy{&testee, SIGNAL(error(QString))};
  QSignalSpy info_spy{&testee, SIGNAL(info(QString))};

  void SetUp() override
  {
    ASSERT_TRUE(error_spy.isValid());
    ASSERT_TRUE(info_spy.isValid());
  }
};


TEST_F(SysfsDevice_Test, an_error_is_logged_when_the_minimum_value_is_to_low)
{
  ON_CALL(maxBrightness, read())
      .WillByDefault(Return(QString{"42"}));
  minimum = -1;

  testee.setPercentage({});

  ASSERT_EQ(1, error_spy.count());
  ASSERT_EQ("minimum value (-1) is out of range (0-42)", error_spy.at(0).at(0).toString().toStdString());
}

TEST_F(SysfsDevice_Test, setting_a_new_value_writes_it_to_the_file)
{
  ON_CALL(maxBrightness, read())
      .WillByDefault(Return(QString{"100"}));

  EXPECT_CALL(brightness, write(_));

  testee.setPercentage({});
}

TEST_F(SysfsDevice_Test, an_info_is_written_when_setting_a_new_value)
{
  ON_CALL(maxBrightness, read())
      .WillByDefault(Return(QString{"55"}));
  minimum = 10;

  testee.setPercentage(60);

  ASSERT_EQ(1, info_spy.count());
  ASSERT_EQ("set brightness value (37) based on percentage (60), minimum brightness (10) and maximum brightness (55)", info_spy.at(0).at(0).toString().toStdString());
}

TEST_F(SysfsDevice_Test, the_percentage_value_is_scaled_according_to_the_max_value_when_written)
{
  ON_CALL(maxBrightness, read()).WillByDefault(Return(QString{"1000"}));

  EXPECT_CALL(brightness, write(QString{"550"}));

  testee.setPercentage(55);
}

TEST_F(SysfsDevice_Test, the_percentage_value_is_scaled_according_to_the_min_and_max_value_when_written)
{
  ON_CALL(maxBrightness, read()).WillByDefault(Return(QString{"100"}));
  minimum = 50;

  EXPECT_CALL(brightness, write(QString{"75"}));

  testee.setPercentage(50);
}

TEST_F(SysfsDevice_Test, can_set_the_minimum_value_to_the_maximum_value)
{
  ON_CALL(maxBrightness, read()).WillByDefault(Return(QString{"77"}));
  minimum = 77;

  EXPECT_CALL(brightness, write(QString{"77"}));

  testee.setPercentage(50);
}

TEST_F(SysfsDevice_Test, an_error_is_logged_when_the_maximum_value_is_to_low)
{
  ON_CALL(maxBrightness, read())
      .WillByDefault(Return(QString{"-1"}));

  testee.setPercentage({});

  ASSERT_EQ(1, error_spy.count());
  ASSERT_EQ("maximum value (-1) is invalid (<0)", error_spy.at(0).at(0).toString().toStdString());
}

TEST_F(SysfsDevice_Test, no_brightness_value_is_written_when_the_maximum_value_is_to_low)
{
  ON_CALL(maxBrightness, read())
      .WillByDefault(Return(QString{"-1"}));

  EXPECT_CALL(brightness, write(_))
      .Times(0);

  testee.setPercentage({});
}

TEST_F(SysfsDevice_Test, an_error_is_logged_when_the_minimal_value_is_bigger_than_the_maximal_value)
{
  ON_CALL(maxBrightness, read())
      .WillByDefault(Return(QString{"15"}));
  minimum = 120;

  testee.setPercentage({});

  ASSERT_EQ(1, error_spy.count());
  ASSERT_EQ("minimum value (120) is out of range (0-15)", error_spy.at(0).at(0).toString().toStdString());
}

TEST_F(SysfsDevice_Test, no_brightness_value_is_written_when_the_minimal_value_is_bigger_than_the_maximal_value)
{
  ON_CALL(maxBrightness, read())
      .WillByDefault(Return(QString{"15"}));
  minimum = 120;

  EXPECT_CALL(brightness, write(_))
      .Times(0);

  testee.setPercentage({});
}

TEST_F(SysfsDevice_Test, an_error_is_logged_when_the_brightness_percentage_is_too_low)
{

  testee.setPercentage(-1);

  ASSERT_EQ(1, error_spy.count());
  ASSERT_EQ("brightness percentage (-1) is out of range (0-100)", error_spy.at(0).at(0).toString().toStdString());
}

TEST_F(SysfsDevice_Test, no_brightness_value_is_written_when_the_brightness_percentage_is_too_low)
{

  EXPECT_CALL(brightness, write(_))
      .Times(0);

  testee.setPercentage(-1);
}

TEST_F(SysfsDevice_Test, an_error_is_logged_when_the_brightness_percentage_is_too_high)
{

  testee.setPercentage(101);

  ASSERT_EQ(1, error_spy.count());
  ASSERT_EQ("brightness percentage (101) is out of range (0-100)", error_spy.at(0).at(0).toString().toStdString());
}

TEST_F(SysfsDevice_Test, no_brightness_value_is_written_when_the_brightness_percentage_is_too_high)
{

  EXPECT_CALL(brightness, write(_))
      .Times(0);

  testee.setPercentage(101);
}

TEST_F(SysfsDevice_Test, the_value_is_rounded_when_written_to_the_device)
{
  ON_CALL(maxBrightness, read())
      .WillByDefault(Return(QString{"10"}));
  EXPECT_CALL(brightness, write(QString{"1"}));
  testee.setPercentage(14);

  ON_CALL(maxBrightness, read()).WillByDefault(Return(QString{"10"}));
  EXPECT_CALL(brightness, write(QString{"3"}));
  testee.setPercentage(25);
}

TEST_F(SysfsDevice_Test, an_error_is_logged_when_the_calculated_value_is_to_low)
{
  ON_CALL(maxBrightness, read())
      .WillByDefault(Return("2000000000"));

  testee.setPercentage(100);

  ASSERT_EQ(1, error_spy.count());
  ASSERT_EQ("calculated brightness value (-18634628) is out of range (0-2000000000)", error_spy.at(0).at(0).toString().toStdString());
}

TEST_F(SysfsDevice_Test, no_brightness_value_is_written_when_the_calculated_value_is_to_low)
{
  ON_CALL(maxBrightness, read())
      .WillByDefault(Return("2000000000"));

  EXPECT_CALL(brightness, write(_))
      .Times(0);

  testee.setPercentage(100);
}
