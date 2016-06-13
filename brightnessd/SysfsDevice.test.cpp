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

class SysfsDevice_Test:
    public testing::Test
{
public:
  testing::StrictMock<sysfs::Writer_Mock> brightness;
  testing::NiceMock<sysfs::Reader_Mock> maxBrightness;
  SysfsDevice testee{brightness, maxBrightness};
};


TEST_F(SysfsDevice_Test, setting_a_new_value_writes_it_to_the_file)
{
  EXPECT_CALL(brightness, write(testing::_));

  testee.setPercentage(55);
}

TEST_F(SysfsDevice_Test, the_percentage_value_is_scaled_according_to_the_max_value_when_written)
{
  ON_CALL(maxBrightness, read()).WillByDefault(testing::Return(QString{"1000"}));

  EXPECT_CALL(brightness, write(QString{"550"}));

  testee.setPercentage(55);
}

TEST_F(SysfsDevice_Test, the_percentage_value_is_scaled_according_to_the_min_and_max_value_when_written)
{
  ON_CALL(maxBrightness, read()).WillByDefault(testing::Return(QString{"100"}));
  testee.setMinimumValue(50);

  EXPECT_CALL(brightness, write(QString{"75"}));

  testee.setPercentage(50);
}

TEST_F(SysfsDevice_Test, the_maximal_value_is_used_when_the_minimal_value_is_bigger_than_the_maximal_value)
{
  ON_CALL(maxBrightness, read()).WillByDefault(testing::Return(QString{"15"}));
  testee.setMinimumValue(120);

  EXPECT_CALL(brightness, write(QString{"15"})).Times(3);

  testee.setPercentage(0);
  testee.setPercentage(50);
  testee.setPercentage(100);
}

TEST_F(SysfsDevice_Test, the_value_is_rounded_when_written_to_the_device)
{
  ON_CALL(maxBrightness, read()).WillByDefault(testing::Return(QString{"10"}));
  EXPECT_CALL(brightness, write(QString{"1"}));
  testee.setPercentage(14);

  ON_CALL(maxBrightness, read()).WillByDefault(testing::Return(QString{"10"}));
  EXPECT_CALL(brightness, write(QString{"3"}));
  testee.setPercentage(25);
}
