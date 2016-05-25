/*
 * (C) Copyright 2016
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "LinearWithSaturation.h"

LinearWithSaturation::LinearWithSaturation(const LinearConfiguration &configuration) :
  min{configuration.minAmbient, configuration.minBrightness},
  max{configuration.maxAmbient, configuration.maxBrightness}
{
}

static int roundDiv(int dividend, int divisor)
{
  if (dividend > 0) {
    dividend += divisor/2;
  } else {
    dividend -= divisor/2;
  }
  return dividend / divisor;
}

/*
 *          max.x
 *  max.y __|______
 *         /
 *        /
 *       /
 * _____/__ min.y
 *     |
 *     min.x
 */
int LinearWithSaturation::brigthnessFromLux(int x) const
{
  if (x < min.x) {
    return min.y;
  }
  if (x > max.x) {
    return max.y;
  }
  if (max.x == min.x) {
    return roundDiv(min.y + max.y, 2);
  }
  const auto normX = x - min.x;
  const auto normY = roundDiv(normX * (max.y - min.y), max.x - min.x);
  return normY + min.y;
}
