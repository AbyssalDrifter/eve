//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/complex.hpp>

TTS_CASE_WITH( "Check behavior of real on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              , tts::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_EQUAL( eve::real(c_t(e, f)), e );
      c_t c;
      eve::real(c) = e;
      eve::imag(c) = f;
      TTS_EQUAL( c_t(e, f), c );

    }
  }
};

TTS_CASE_WITH( "Check behavior of real on wide"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              , tts::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using z_t = eve::wide<eve::complex<e_t>, typename T::cardinal_type>;

  TTS_EQUAL( eve::real(z_t{a0,a1}), a0 );
  z_t c;
  eve::real(c) = a0;
  eve::imag(c) = a1;
  TTS_EQUAL( z_t(a0, a1), c );
};
