/*
 * (C) Copyright 2017
 * Urs Fässler, bbv Software Services, http://bbv.ch
 *
 * SPDX-License-Identifier:	GPL-3.0+
 */

#pragma once

#include <tuple>
#include <functional>
#include <string>

typedef std::tuple<bool, std::string> Result;
typedef std::function<Result()> Function;
typedef std::function<void(const std::string &error)> ErrorHandler;

class Then
{
public:
  Then(const Result &);

  Then then(const Function &) const;
  void thenOnError(const ErrorHandler &) const;

private:
  const Result result;

};


Then execute(const Function &);
Result Ok();
