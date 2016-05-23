# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Set brightness value via D-Bus
  As a service
  I want to set the brightness over D-Bus
  In order to easily control the brightness of the display

Scenario Outline: Set the brightness to a specific value
  Given I have a directory "<device>"
  And I have a file "<device>/max_brightness" with the content "<max brightness>"
  And I have a file "<device>/brightness" with the content ""
  And I start brightnessd with the device "<device>"

  When I set the D-Bus property "percentage" to <percentage> of the interface "ch.bbv.brightness.power" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"

  Then I expect the file "<device>/brightness" to have the content "<brightness>"

  Examples:
    | percentage | max brightness | brightness | device              |
    |         42 |            100 |         42 | /sys/test/backlight |
    |         42 |            100 |         42 | test                |
    |         42 |             15 |          6 | /sys/test/backlight |
    |         45 |             10 |          5 | /sys/test/backlight |

