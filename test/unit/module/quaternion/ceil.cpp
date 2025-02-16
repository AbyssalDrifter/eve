//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/quaternion.hpp>

TTS_CASE_WITH ( "Check behavior of ceil on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate(tts::randoms(-1000.0, +1000.0), tts::randoms(-1000.0, +1000.0))
              )
<typename T>(T const& a0, T const& a1 )
{
  for(auto e : a0)
    for(auto f : a1)
    {
      TTS_EQUAL( eve::ceil(eve::quaternion(e, f, e, f)), eve::quaternion(eve::ceil(e), eve::ceil(f), eve::ceil(e), eve::ceil(f)));
    }
};

TTS_CASE_WITH ( "Check behavior of ceil on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(-1000.0, +1000.0), tts::randoms(-1000.0, +1000.0))
              )
<typename T>(T const& a0, T const& a1 )
{
  using z_t = eve::as_quaternion_t<T>;
  TTS_EQUAL( eve::ceil(z_t{a0,a1,a0,a1 }),z_t(eve::ceil(a0), eve::ceil(a1), eve::ceil(a0), eve::ceil(a1)) );
  auto zz = z_t{a0,a1,a0, a1};
  TTS_EQUAL( eve::ceil[a0 > 0](zz), eve::if_else(a0 > 0, eve::ceil(zz), zz));

};
