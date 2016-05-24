# (C) Copyright 2016
# Urs Fässler, bbv Software Services, http://bbv.ch
#
# SPDX-License-Identifier:	GPL-3.0+

Feature: Set brightness depending on the current ambient light
  As a user
  I want to be able to have an adequate brightness
  In order to see the screen in the night and in direct sunlight

@wip
Scenario Outline: Set the brightness depending on the ambient light
  Given I start dummy-brightnessd
  And I have a directory "device"
  And I have a file "device/in_illuminance_input" with the content "<lux>"

  When I run ambientlightd with the device "device"

  Then I expect the property "percentage" of brightnessd to be <brightness>

  Examples:
    | lux    | brightness |
    |  25000 |        100 |
    |      1 |         10 |
    | 100000 |        100 |
    |  10000 |         46 |
    |   1000 |         14 |
    |      0 |         10 |

