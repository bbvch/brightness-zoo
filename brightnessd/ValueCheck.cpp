/*
 * (C) Copyright 2017
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "ValueCheck.h"


Result inRange(int32_t minimum, int32_t value, int32_t maximum, const std::__cxx11::string &name)
{
  const auto ok = (minimum <= value) && (value <= maximum);

  const auto message = ok ? "" : name + " (" + std::to_string(value)+") is out of range (" + std::to_string(minimum) + "-" + std::to_string(maximum) + ")";

  return {ok, message};
}

Result greater(int32_t value, int32_t minimum, const std::__cxx11::string &name)
{
  const auto ok = (minimum <= value);

  const auto message = ok ? "" : name + " (" + std::to_string(value)+") is invalid (<" + std::to_string(minimum) + ")";

  return {ok, message};
}
