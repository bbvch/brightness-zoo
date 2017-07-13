# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Reduce the brightness of the backlight when set to powersave mode
  As a manufacturer
  I want to reduce the display brightness
  In order to increase the display lifetime

Scenario Outline: Use the powersave mode
  Given I write "powersaveBrightnessPercentage=<reduced>" to the brightnessd configuration file
  And I have a directory "test"
  And I have a file "test/max_brightness" with the content "100"
  And I have a file "test/brightness" with the content ""
  And I start brightnessd with the device "test"

  When I set the D-Bus property "percentage" to <original> of the interface "ch.bbv.brightness.power" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"
  And I set the D-Bus property "on" to true of the interface "ch.bbv.brightness.powersave" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"

  Then I expect the file "test/brightness" to have the content "<actual>"

  Examples:
    | original | reduced | actual |
    |      100 |      50 |     50 |
    |      100 |      25 |     25 |
    |        7 |      50 |      3 |
    |       42 |      50 |     21 |
    |       42 |      75 |     31 |

Scenario Outline: Behave sanely when an invalid situation is detected
  Given I write "powersaveBrightnessPercentage=<reduced>" to the brightnessd configuration file
  And I have a directory "test"
  And I have a file "test/max_brightness" with the content "100"
  And I have a file "test/brightness" with the content ""
  And I start brightnessd with the device "test"

  When I set the D-Bus property "on" to true of the interface "ch.bbv.brightness.powersave" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"

  Then brightnessd exits with the error code -6
  And I expect the string "<error message>" on stderr from brightnessd
  And I expect the file "test/brightness" to have the content ""

  Examples:
    | reduced | error message                                                     |
    |     101 | powersave brightness percentage (101) is out of range (0-100)     |
    |  100000 | powersave brightness percentage (100000) is out of range (0-100)  |
    |      -1 | powersave brightness percentage (-1) is out of range (0-100)      |
    | -100000 | powersave brightness percentage (-100000) is out of range (0-100) |

