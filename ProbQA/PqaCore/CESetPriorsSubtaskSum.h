// Probabilistic Question-Answering system
// @2017 Sarge Rogatch
// This software is distributed under GNU AGPLv3 license. See file LICENSE in repository root for details.

#pragma once

#include "../PqaCore/CESetPriorsTask.fwd.h"

namespace ProbQA {

template<typename taNumber> class CESetPriorsSubtaskSum : public SRPlat::SRStandardSubtask {
public: // types
  typedef CESetPriorsTask<taNumber> TTask;

public:
  taNumber _sumPriors;

public: // methods
  using SRPlat::SRStandardSubtask::SRStandardSubtask;
  virtual void Run() override final;
};

} // namespace ProbQA
