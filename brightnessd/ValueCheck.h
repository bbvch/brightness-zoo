/*
 * (C) Copyright 2017
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#pragma once

#include "CheckedBlock.h"


Result inRange(int32_t minimum, int32_t value, int32_t maximum, const std::string &name);
Result greater(int32_t value, int32_t minimum, const std::string &name);
