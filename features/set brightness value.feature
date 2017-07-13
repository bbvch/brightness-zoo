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


Scenario Outline: print information to standard output in verbose mode when changing percentage
  Given I have a directory "/test"
  And I write "minimumBrightness=<minimum>" to the brightnessd configuration file
  And I have a file "/test/max_brightness" with the content "<max brightness>"
  And I have a file "/test/brightness" with the content ""
  And I start brightnessd with the device "/test" and argument "--verbose"

  When I set the D-Bus property "percentage" to <percentage> of the interface "ch.bbv.brightness.power" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"
  And I stop brightnessd

  Then I expect the string "set brightness value (<brightness>) based on percentage (<percentage>), minimum brightness (<minimum>) and maximum brightness (<max brightness>)" on stdout from brightnessd

  Examples:
    | percentage | max brightness | minimum | brightness |
    |         10 |            100 |       0 |         10 |
    |         42 |            100 |      15 |         51 |
    |         50 |             15 |       9 |         12 |
    |         90 |             10 |       4 |          9 |


Scenario: does not print information to standard output when not in verbose mode
  Given I have a directory "/test"
  And I write "minimumBrightness=<minimum>" to the brightnessd configuration file
  And I have a file "/test/max_brightness" with the content "<max brightness>"
  And I have a file "/test/brightness" with the content ""
  And I start brightnessd with the device "/test"

  When I set the D-Bus property "percentage" to 50 of the interface "ch.bbv.brightness.power" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"
  And I stop brightnessd

  Then I expect not output on stdout from brightnessd


Scenario Outline: Set a minimal brightness
  Given I write "minimumBrightness=<minimum>" to the brightnessd configuration file
  And I have a directory "test"
  And I have a file "test/max_brightness" with the content "<max brightness>"
  And I have a file "test/brightness" with the content ""
  And I start brightnessd with the device "test"

  When I set the D-Bus property "percentage" to <percentage> of the interface "ch.bbv.brightness.power" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"

  Then I expect the file "test/brightness" to have the content "<brightness>"

  Examples:
    | percentage | max brightness | minimum | brightness |
    |          0 |            100 |       0 |          0 |
    |         50 |            100 |       0 |         50 |
    |          0 |            101 |       1 |          1 |
    |         50 |            101 |       1 |         51 |
    |          0 |             15 |       5 |          5 |
    |         10 |             15 |       5 |          6 |
    |         20 |             15 |       5 |          7 |
    |         30 |             15 |       5 |          8 |
    |         40 |             15 |       5 |          9 |
    |         50 |             15 |       5 |         10 |
    |         60 |             15 |       5 |         11 |
    |         70 |             15 |       5 |         12 |
    |         80 |             15 |       5 |         13 |
    |         90 |             15 |       5 |         14 |
    |        100 |             15 |       5 |         15 |

Scenario Outline: Behave sanely when an invalid situation is detected
  Given I write "minimumBrightness=<minimum>" to the brightnessd configuration file
  And I have a directory "test"
  And I have a file "test/max_brightness" with the content "<max brightness>"
  And I have a file "test/brightness" with the content ""
  And I start brightnessd with the device "test"

  When I set the D-Bus property "percentage" to <percentage> of the interface "ch.bbv.brightness.power" with the path "/ch/bbv/brightness" of the service "ch.bbv.brightnessd"

  Then brightnessd exits with the error code -6  
  And I expect the string "<error message>" on stderr from brightnessd
  And I expect the file "test/brightness" to have the content ""

  Examples:
    | percentage | max brightness | minimum | error message                                       |
    |          0 |              3 |      10 | minimum value (10) is out of range (0-3)            |
    |        120 |            100 |      10 | brightness percentage (120) is out of range (0-100) |
    |        -20 |            100 |      10 | brightness percentage (-20) is out of range (0-100) |
    |         10 |             -1 |       0 | maximum value (-1) is invalid                       |
    |        100 |             15 |      -5 | minimum value (-5) is out of range (0-15)           |
    |        100 |     2000000000 |      15 | calculated brightness value (-18634628) is out of range (15-2000000000) |

