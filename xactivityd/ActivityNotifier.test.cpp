/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ActivityNotifier.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QSignalSpy>

class ActivityNotifier_Test:
    public testing::Test
{
public:
  const std::chrono::minutes timeout{5};
  std::chrono::milliseconds idleSince{0};
  ActivityNotifier testee{timeout, [&](){return idleSince;}};

  QSignalSpy activitySpy{&testee, SIGNAL(active())};
  QSignalSpy inactivitySpy{&testee, SIGNAL(inactive())};
};


TEST_F(ActivityNotifier_Test, notifies_on_initial_activity)
{
  idleSince = std::chrono::minutes{0};

  testee.check();

  ASSERT_EQ(1, activitySpy.count());
  ASSERT_EQ(0, inactivitySpy.count());
}

TEST_F(ActivityNotifier_Test, notifies_on_initial_inactivity)
{
  idleSince = std::chrono::minutes{10};

  testee.check();

  ASSERT_EQ(1, inactivitySpy.count());
  ASSERT_EQ(0, activitySpy.count());
}

TEST_F(ActivityNotifier_Test, notifies_when_activity_timout_run_out)
{
  idleSince = std::chrono::minutes{0};
  testee.check();
  activitySpy.clear();
  inactivitySpy.clear();

  idleSince = std::chrono::minutes{10};
  testee.check();

  ASSERT_EQ(1, inactivitySpy.count());
  ASSERT_EQ(0, activitySpy.count());
}

TEST_F(ActivityNotifier_Test, notifies_when_activity_is_detected_again)
{
  idleSince = std::chrono::minutes{10};
  testee.check();
  activitySpy.clear();
  inactivitySpy.clear();

  idleSince = std::chrono::minutes{0};
  testee.check();

  ASSERT_EQ(1, activitySpy.count());
  ASSERT_EQ(0, inactivitySpy.count());
}

TEST_F(ActivityNotifier_Test, does_not_notify_activity_twice)
{
  idleSince = std::chrono::minutes{0};
  testee.check();
  activitySpy.clear();
  inactivitySpy.clear();

  idleSince = std::chrono::minutes{0};
  testee.check();

  ASSERT_EQ(0, inactivitySpy.count());
  ASSERT_EQ(0, activitySpy.count());
}

TEST_F(ActivityNotifier_Test, does_not_notify_inactivity_twice)
{
  idleSince = std::chrono::minutes{10};
  testee.check();
  activitySpy.clear();
  inactivitySpy.clear();

  idleSince = std::chrono::minutes{10};
  testee.check();

  ASSERT_EQ(0, activitySpy.count());
  ASSERT_EQ(0, inactivitySpy.count());
}
