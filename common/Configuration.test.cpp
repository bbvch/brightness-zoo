/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "Configuration.h"

#include <gtest/gtest.h>

class Configuration_Test :
    public testing::Test
{
public:
  QVariant read;
  Configuration::Reader readf = [&](QString, QVariant){return read;};
  Configuration testee{readf};

};

TEST_F(Configuration_Test, read_a_stored_unsigned_value)
{
  read = 42;

  ASSERT_EQ(42, testee.read("", 0));
}

TEST_F(Configuration_Test, return_the_default_value_when_the_read_value_can_not_be_converted_to_unsigned)
{
  read = "nix";

  ASSERT_EQ(11, testee.read("", 11));
}

