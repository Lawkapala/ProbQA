// Probabilistic Question-Answering system
// @2017 Sarge Rogatch
// This software is distributed under GNU AGPLv3 license. See file LICENSE in repository root for details.

#pragma once

namespace ProbQA {

// This class is not thread-safe.
//TODO: refactor to get a possibility to fetch 4 bits at once
template <typename taId> class GapTracker {
  std::vector<taId> _gaps;
  SRPlat::SRBitArray _isGap; // remove R after refactorring
public:
  explicit GapTracker() : _isGap(0, false) { }

  bool IsGap(const taId at) const { return _isGap.GetOne(SRPlat::SRCast::ToUint64(at)); }

  // Get |iQuad|th 4 adjacent bits denoting gaps.
  uint8_t GetQuad(const taId iQuad) const { return _isGap.GetQuad(iQuad); }

  void Release(const taId at) {
    assert(!_isGap.GetOne(SRPlat::SRCast::ToUint64(at)));
    _isGap.SetOne(SRPlat::SRCast::ToUint64(at));
    _gaps.push_back(at);
  }

  bool HasGaps() const { return _gaps.size() >= 1; }

  // If there is no gap to acquire, returns length+1 meaning the client must increase his arrays.
  taId Acquire() {
    if (_gaps.size() <= 0) {
      taId answer = _isGap.Size();
      _isGap.Add(1);
      return answer;
    }
    taId answer = _gaps.back();
    _gaps.pop_back();
    _isGap.ClearOne(SRPlat::SRCast::ToUint64(answer));
    return answer;
  }

  // Grow to the specified length setting the new items as not gaps.
  void GrowTo(const taId newLength) {
    assert(newLength >= taId(_isGap.Size()));
    _isGap.GrowTo(SRPlat::SRCast::ToUint64(newLength));
  }

  // Client access to the gaps vector, e.g. to sort it and then make compaction.
  std::vector<taId>& Gaps() { return _gaps; }

  void Compact(const taId newLength) {
    assert(newLength <= taId(_isGap.Size()));
    _isGap.ClearRange(0, SRPlat::SRCast::ToUint64(newLength));
    _isGap.ReduceTo(newLength);
    _gaps.clear();
  }
};

} // namespace ProbQA
