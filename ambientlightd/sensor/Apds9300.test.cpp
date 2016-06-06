/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Apds9300.h"
#include "I2c.mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Apds9300_Test :
    public testing::Test
{
public:
  testing::NiceMock<I2c_Mock> i2c;
  Apds9300 testee{i2c};

};


TEST_F(Apds9300_Test, initialize_on_start)
{
  testing::StrictMock<I2c_Mock> i2c;

  EXPECT_CALL(i2c, write(0x52, 0xE0, 0x03));

  Apds9300 testee{i2c};
}

TEST_F(Apds9300_Test, uses_data_of_channel_0)
{
  ON_CALL(i2c, read(0x52, 0xec)).WillByDefault(testing::Return(0xfe));
  ON_CALL(i2c, read(0x52, 0xed)).WillByDefault(testing::Return(0xca));

  ASSERT_EQ(0xcafe, testee.read());
}

TEST_F(Apds9300_Test, read_the_lower_byte_bevore_the_upper_byte)
{
  testing::InSequence dummy;

  EXPECT_CALL(i2c, read(testing::_, 0xec));
  EXPECT_CALL(i2c, read(testing::_, 0xed));

  testee.read();
}
