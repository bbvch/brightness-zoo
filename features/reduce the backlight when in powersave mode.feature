# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Reduce the brightness of the backlight when set into powersave mode
  As a manufacturer
  I want to reduce the display brightness
  In order to increase the display lifetime

Scenario Outline: Use the powersave mode
  Given I have a directory "test"
  And I have a file "test/max_brightness" with the content "100"
  And I have a file "test/brightness" with the content ""
  And I start brightnessd with the device "test"

  When I set the D-Bus property "percentage" to <percentage> of the interface "ch.bbv.brightness.power" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"
  And I set the D-Bus property "on" to true of the interface "ch.bbv.brightness.powersave" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"

  Then I expect the file "test/brightness" to have the content "<reduced brightness>"

  Examples:
    | percentage | reduced brightness |
    |        100 |                 50 |
    |          7 |                  3 |
    |         42 |                 21 |

