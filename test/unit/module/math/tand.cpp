//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of tand", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::tand(T()), T);
  TTS_EXPR_IS(eve::tand(v_t()), v_t);
};

//==================================================================================================
// tand  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of tand on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-45, 45),
                            tts::randoms(-90, 90),
                            tts::randoms(-5000, 5000)))
<typename T>(T const& a0, T const& a1, T const& a2)
{
  using eve::tand;
  using eve::detail::map;

  using eve::deginrad;
  using v_t = eve::element_type_t<T>;
  auto ref  = [](auto e) -> v_t
  {
    auto d = eve::cosd(e);
    return d ? eve::sind(e) / d : eve::nan(eve::as(e));
  };
  TTS_ULP_EQUAL(eve::quarter_circle(tand)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(tand)(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(eve::half_circle(tand)(a1), map(ref, a1), 50);
  TTS_ULP_EQUAL(tand(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(tand(a1), map(ref, a1), 2);
  TTS_ULP_EQUAL(tand(a2), map(ref, a2), 2);
};


//==================================================================================================
// Tests for masked tand
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::tand)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::tand[mask](a0),
            eve::if_else(mask, eve::tand(a0), a0));
};
