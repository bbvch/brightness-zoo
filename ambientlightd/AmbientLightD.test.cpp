/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "AmbientLightD.h"

#include <Brightness.mock.h>
#include <sysfs/Reader.mock.h>
#include "convert/AmbientToBrightness.mock.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class AmbientLightD_Test :
    public testing::Test
{
public:
  testing::NiceMock<sysfs::Reader_Mock> ambientLight;
  testing::NiceMock<AmbientToBrightness_Mock> convert;
  testing::NiceMock<Brightness_Mock> brightness;
  AmbientLightD testee{ambientLight, convert, brightness};

};

TEST_F(AmbientLightD_Test, set_brightness_on_request)
{
  EXPECT_CALL(brightness, setBrightness(testing::_));

  testee.check();
}

TEST_F(AmbientLightD_Test, use_ambient_light_from_sensor)
{
  ON_CALL(ambientLight, read()).WillByDefault(testing::Return(QString{"1234"}));

  EXPECT_CALL(convert, brigthnessFromLux(1234));

  testee.check();
}

TEST_F(AmbientLightD_Test, use_brightness_from_convertion)
{
  ON_CALL(convert, brigthnessFromLux(testing::_)).WillByDefault(testing::Return(57));

  EXPECT_CALL(brightness, setBrightness(57));

  testee.check();
}
