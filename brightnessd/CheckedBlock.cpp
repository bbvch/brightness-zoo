/*
 * (C) Copyright 2017
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#include "CheckedBlock.h"

Then::Then(const Result &result_) :
  result{result_}
{
}

Then Then::then(const Function &function) const
{
  if (!std::get<0>(result)) {
    return { result };
  } else {
    return { function() };
  }
}

void Then::thenOnError(const ErrorHandler &function) const
{
  if (!std::get<0>(result)) {
    function(std::get<1>(result));
  }
}

Then execute(const Function &function)
{
  const auto res = function();
  if (!std::get<0>(res)) {
    return {res};
  }

  return { Ok() };
}

Result Ok()
{
  return {true, {}};
}
