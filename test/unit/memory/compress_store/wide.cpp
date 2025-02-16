//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "compress_store_test.hpp"
#include <eve/module/core.hpp>

TTS_CASE_WITH( "Check compress store behavior"
        , eve::test::simd::all_types
        , tts::generate(tts::ramp(1))
        )
<typename T> (T data)
{
#if defined(SPY_SIMD_IS_ARM_FIXED_SVE)
  // FIX-ME: 1493 compress test issues
  smaller_test_v<eve::logical<T>>(data);
  return;
#endif
  all_tests_for_v<eve::logical<T>>(data);
};
