//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include <eve/module/core.hpp>
#include "producers.hpp"

#include <cmath>

TTS_CASE_TPL("Random check for eve::abs", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;

  if constexpr(eve::floating_value<e_t>)
  {
    auto std_abs = [](auto e) { return (e < 0) ? -e : e; };
    EVE_ULP_RANGE_CHECK( T, eve::uniform_prng<e_t>(-1,1),  std_abs, eve::abs );
  }
  else if constexpr(eve::signed_value<e_t>)
  {
    auto vmin = eve::valmin(eve::as<e_t>());
    auto vmax = eve::valmax(eve::as<e_t>());

    auto std_abs = [](auto e)
    {
      e_t z = (e < 0) ? -e : e;
      return z < 0 ? eve::valmax(eve::as(e)) : z;
    };

    EVE_ULP_RANGE_CHECK ( T, eve::uniform_prng<e_t>( eve::inc(vmin), vmax ), std_abs, eve::abs );
    EVE_ULP_RANGE_CHECK ( T, eve::uniform_prng<e_t>( vmin, vmax ), std_abs, eve::saturated(eve::abs) );
  }
  else
  {
    auto vmin = eve::valmin(eve::as<e_t>());
    auto vmax = eve::valmax(eve::as<e_t>());

    auto std_abs = [](auto e) { return e; };
    EVE_ULP_RANGE_CHECK ( T, eve::uniform_prng<e_t>(vmin,vmax), std_abs, eve::abs );
  }
};
