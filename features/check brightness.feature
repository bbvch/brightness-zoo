# (C) Copyright 2017
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Check if the written brightness value is correct
  As a system administrator
  I want to supervise the actual brightness with respect to the requested brightness
  In order start an action when they do not match


Scenario Outline: actual and requested brightness are equal
  Given I have a directory "/sys/test/backlight"
  And I have a file "/sys/test/backlight/brightness" with the content "<expected>"
  And I have a file "/sys/test/backlight/actual_brightness" with the content "<actual>"

  When I run checkbrightness with the device "/sys/test/backlight" and argument "--command=false"

  Then I expect no output on stderr from checkbrightness
  And I expect no output on stdout from checkbrightness
  And checkbrightness exits with the error code 0

  Examples:
    | expected | actual |
    |        0 |      0 |
    |       27 |     27 |
    |      100 |    100 |
    |    65432 |  65432 |


Scenario Outline: notify when the actual and requested brightness don't match
  Given I have a directory "/sys/test/backlight"
  And I have a file "/sys/test/backlight/brightness" with the content "<expected>"
  And I have a file "/sys/test/backlight/actual_brightness" with the content "<actual>"

  When I run checkbrightness with the device "/sys/test/backlight" and argument "--command=sh -c "echo -n problem > command""

  Then I expect the string "Read brightness <actual>, expected <expected>" on stdout from checkbrightness
  And I expect no output on stderr from checkbrightness
  And I expect the file "command" to have the content "problem"
  And checkbrightness exits with the error code 0

  Examples:
    | expected | actual |
    |       15 |      3 |
    |        3 |     15 |
    |        0 |      7 |
    |        7 |      0 |
    |       99 |    100 |


Scenario: notify when the command can not be executed
  Given I have a directory "/sys/test/backlight"
  And I have a file "/sys/test/backlight/brightness" with the content "15"
  And I have a file "/sys/test/backlight/actual_brightness" with the content "3"

  When I run checkbrightness with the device "/sys/test/backlight" and argument "--command=false"

  Then I expect the string "Read brightness 3, expected 15" on stdout from checkbrightness
  And I expect the string "command execution failed: false" on stderr from checkbrightness
  And checkbrightness exits with the error code 1

