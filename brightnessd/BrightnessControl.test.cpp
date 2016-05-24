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

class BrightnessControl_Test:
    public testing::Test
{
public:
  testing::NiceMock<Device_Mock> device;
  BrightnessControl testee{25, device};

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
