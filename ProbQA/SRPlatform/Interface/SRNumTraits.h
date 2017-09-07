// Probabilistic Question-Answering system
// @2017 Sarge Rogatch
// This software is distributed under GNU AGPLv3 license. See file LICENSE in repository root for details.

#pragma once

namespace SRPlat {

template<typename taNumber> struct SRNumTraits;

template<> struct SRNumTraits<double> {
  static constexpr uint16_t _cnMantissaBits = 52;
  static constexpr uint16_t _cMantissaOffs = 0;
  static constexpr uint16_t _cnExponentBits = 11;
  static constexpr uint16_t _cExponentOffs = _cnMantissaBits;
  static constexpr uint16_t _cSignOffs = _cExponentOffs + _cnExponentBits;

  static constexpr int16_t _cExponent0Down = 1023;
  static constexpr uint64_t _cExponent0Up = uint64_t(_cExponent0Down) << _cExponentOffs;
  static constexpr uint16_t _cExponentMaskDown = 0x7ff;
  static constexpr uint64_t _cExponentMaskUp = uint64_t(_cExponentMaskDown) << _cExponentOffs;
};

} // namespace SRPlat