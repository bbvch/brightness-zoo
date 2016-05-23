/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Device.h"

#include "sysfs/Writer.mock.h"
#include "sysfs/Reader.mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Device_Test:
    public testing::Test
{
public:
  testing::StrictMock<sysfs::Writer_Mock> brightness;
  testing::NiceMock<sysfs::Reader_Mock> maxBrightness;
  Device testee{brightness, maxBrightness};
};


TEST_F(Device_Test, setting_a_new_value_writes_it_to_the_file)
{
  EXPECT_CALL(brightness, write(testing::_));

  testee.setPercentage(55);
}

TEST_F(Device_Test, the_percentage_value_is_scaled_according_to_the_max_value_when_written)
{
  ON_CALL(maxBrightness, read()).WillByDefault(testing::Return(QString{"1000"}));

  EXPECT_CALL(brightness, write(QString{"550"}));

  testee.setPercentage(55);
}

TEST_F(Device_Test, the_value_is_rounded_when_written_to_the_device)
{
  ON_CALL(maxBrightness, read()).WillByDefault(testing::Return(QString{"10"}));
  EXPECT_CALL(brightness, write(QString{"1"}));
  testee.setPercentage(14);

  ON_CALL(maxBrightness, read()).WillByDefault(testing::Return(QString{"10"}));
  EXPECT_CALL(brightness, write(QString{"3"}));
  testee.setPercentage(25);
}
