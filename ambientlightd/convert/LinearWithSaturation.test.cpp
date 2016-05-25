/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "LinearWithSaturation.h"

#include <Brightness.mock.h>
#include <sysfs/Reader.mock.h>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(LinearWithSaturation_Test, produce_sane_value_for_insane_ambient_parameter)
{
  LinearConfiguration configuration;
  configuration.minAmbient = 1000;
  configuration.maxAmbient = 1000;
  configuration.minBrightness = 10;
  configuration.maxBrightness = 90;
  LinearWithSaturation testee{configuration};

  ASSERT_EQ(10, testee.brigthnessFromLux(500));
  ASSERT_EQ(50, testee.brigthnessFromLux(1000));
  ASSERT_EQ(90, testee.brigthnessFromLux(1500));
}

TEST(LinearWithSaturation_Test, produce_sane_value_for_insane_brightness_parameter)
{
  LinearConfiguration configuration;
  configuration.minAmbient = 1;
  configuration.maxAmbient = 1000;
  configuration.minBrightness = 50;
  configuration.maxBrightness = 50;
  LinearWithSaturation testee{configuration};

  ASSERT_EQ(50, testee.brigthnessFromLux(500));
  ASSERT_EQ(50, testee.brigthnessFromLux(1000));
  ASSERT_EQ(50, testee.brigthnessFromLux(1500));
}

TEST(LinearWithSaturation_Test, convert_ambient_value_linear_to_configuration)
{
  LinearConfiguration configuration;
  configuration.minAmbient = 1;
  configuration.maxAmbient = 1000;
  configuration.minBrightness = 10;
  configuration.maxBrightness = 100;
  LinearWithSaturation testee{configuration};

  ASSERT_EQ(10, testee.brigthnessFromLux(1));
  ASSERT_EQ(55, testee.brigthnessFromLux(500));
  ASSERT_EQ(100, testee.brigthnessFromLux(1000));
}

TEST(LinearWithSaturation_Test, works_as_expected_for_inverse_linearity)
{
  LinearConfiguration configuration;
  configuration.minAmbient = 1;
  configuration.maxAmbient = 1000;
  configuration.minBrightness = 100;
  configuration.maxBrightness = 10;
  LinearWithSaturation testee{configuration};

  ASSERT_EQ(100, testee.brigthnessFromLux(1));
  ASSERT_EQ(55, testee.brigthnessFromLux(500));
  ASSERT_EQ(10, testee.brigthnessFromLux(1000));
}

TEST(LinearWithSaturation_Test, use_min_max_value_for_out_of_range_lux_values)
{
  LinearConfiguration configuration;
  configuration.minAmbient = 10;
  configuration.maxAmbient = 1000;
  configuration.minBrightness = 10;
  configuration.maxBrightness = 90;
  LinearWithSaturation testee{configuration};

  ASSERT_EQ(10, testee.brigthnessFromLux(-1));
  ASSERT_EQ(10, testee.brigthnessFromLux(0));
  ASSERT_EQ(10, testee.brigthnessFromLux(1));

  ASSERT_EQ(90, testee.brigthnessFromLux(2000));
  ASSERT_EQ(90, testee.brigthnessFromLux(10000));
  ASSERT_EQ(90, testee.brigthnessFromLux(1000000));
}

