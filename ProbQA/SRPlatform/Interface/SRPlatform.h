// Probabilistic Question-Answering system
// @2017 Sarge Rogatch
// This software is distributed under GNU AGPLv3 license. See file LICENSE in repository root for details.

#pragma once

#ifdef SRPLATFORM_EXPORTS
#define SRPLATFORM_API __declspec(dllexport)
#else
#define SRPLATFORM_API __declspec(dllimport)
#endif // SRPLATFORM_EXPORTS

#pragma warning( push )
#pragma warning( disable : 4251 ) // needs to have dll-interface to be used by clients of class
class SRPLATFORM_API std::exception_ptr;
template struct SRPLATFORM_API std::atomic<int32_t>;
template struct SRPLATFORM_API std::atomic<size_t>;
class SRPLATFORM_API std::thread;
template SRPLATFORM_API class std::allocator<std::thread>;

namespace SRPlat {
  class SRBaseSubtask;
}

template class SRPLATFORM_API std::allocator<SRPlat::SRBaseSubtask*>;
template class SRPLATFORM_API std::deque<SRPlat::SRBaseSubtask*>;
template class SRPLATFORM_API std::queue<SRPlat::SRBaseSubtask*>;
#pragma warning( pop )

//// IS_CPU_X86_32 , IS_CPU_X86_64
#ifdef _MSC_VER
  #if _M_IX86
    static_assert(sizeof(void*) == 4, "Double-checking for CPU bit-width detection");
    #define IS_CPU_X86_32 1
    #define IS_CPU_X86_64 0
  #elif _M_X64
    static_assert(sizeof(void*) == 8, "Double-checking for CPU bit-width detection");
    #define IS_CPU_X86_32 0
    #define IS_CPU_X86_64 1
  #else
    #error This CPU is not supported yet.
  #endif /* CPU selection under MSVC++ compiler */
#else
  #error This compiler is not supported yet.
#endif /* Compiler selection */

#if IS_CPU_X86_32
inline int _rdrand64_step(unsigned __int64* val) {
  uint32_t *p = SRCast::Ptr<uint32_t>(val);
  return _rdrand32_step(p) & _rdrand32_step(p+1);
}
#endif /* IS_CPU_X86_32 */
