/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ConfigurationReader.h"

#include <chrono>
#include <gtest/gtest.h>

class ConfigurationReader_Test :
    public testing::Test
{
public:
  QVariant read;
  QVariant defaultValue;
  ConfigurationReader::Reader readf = [&](QString, QVariant def){
    defaultValue = def;
    return read;
  };
  ConfigurationReader testee{readf};

};

std::ostream& operator <<(std::ostream &stream, std::chrono::seconds value)
{
  stream << value.count();
  return stream;
}

TEST_F(ConfigurationReader_Test, read_a_stored_unsigned_value)
{
  read = 42;

  ASSERT_EQ(42, testee.read("", 0));
}

TEST_F(ConfigurationReader_Test, return_the_default_value_when_the_read_value_can_not_be_converted_to_unsigned)
{
  read = "nix";

  ASSERT_EQ(11, testee.read("", 11));
}

TEST_F(ConfigurationReader_Test, forward_default_value_as_unsigned_to_reader)
{
  testee.read("", 1234);

  ASSERT_EQ(1234, defaultValue.toUInt());
}

TEST_F(ConfigurationReader_Test, read_stored_seconds)
{
  read = "0:01";
  ASSERT_EQ(std::chrono::seconds{1}.count(), testee.read("", std::chrono::seconds{0}).count());

  read = "0:12";
  ASSERT_EQ(std::chrono::seconds{12}.count(), testee.read("", std::chrono::seconds{0}).count());

  read = "1:23";
  ASSERT_EQ(std::chrono::seconds{83}.count(), testee.read("", std::chrono::seconds{0}).count());

  read = "12:34";
  ASSERT_EQ(std::chrono::seconds{754}.count(), testee.read("", std::chrono::seconds{0}).count());
}

TEST_F(ConfigurationReader_Test, return_the_default_value_when_the_read_value_can_not_be_converted_to_a_time)
{
  read = "nix";

  ASSERT_EQ(std::chrono::seconds{42}.count(), testee.read("", std::chrono::seconds{42}.count()));
}

TEST_F(ConfigurationReader_Test, forward_default_value_as_time_to_reader)
{
  testee.read("", std::chrono::seconds{1});
  ASSERT_EQ("0:01", defaultValue.toString().toStdString());

  testee.read("", std::chrono::seconds{12});
  ASSERT_EQ("0:12", defaultValue.toString().toStdString());

  testee.read("", std::chrono::seconds{83});
  ASSERT_EQ("1:23", defaultValue.toString().toStdString());

  testee.read("", std::chrono::seconds{754});
  ASSERT_EQ("12:34", defaultValue.toString().toStdString());
}

