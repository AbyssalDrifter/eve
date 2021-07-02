//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/traits/as_integer.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/bit_notor.hpp>
#include <eve/function/bit_cast.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of bit_notor"
        , eve::test::simd::all_types
        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::bit_notor(T(), T()  ) , T);
  TTS_EXPR_IS( eve::bit_notor(T(), v_t()) , T);
  TTS_EXPR_IS( eve::bit_notor(v_t(), v_t()) , v_t);

  using si_t = eve::as_integer_t<T, signed>;
  using ui_t = eve::as_integer_t<T, unsigned>;

  TTS_EXPR_IS( eve::bit_notor(T(), si_t()) , T);
  TTS_EXPR_IS( eve::bit_notor(T(), ui_t()) , T);

  using ssi_t = eve::as_integer_t<v_t, signed>;
  using sui_t = eve::as_integer_t<v_t, unsigned>;
  TTS_EXPR_IS( eve::bit_notor(T(), ssi_t()) , T);
  TTS_EXPR_IS( eve::bit_notor(T(), sui_t()) , T);
};

//==================================================================================================
//  bit_notor tests
//==================================================================================================
EVE_TEST( "Check behavior of bit_notor on integral types"
            , eve::test::simd::integers
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>( T const& a0, T const& a1)
{
  using eve::bit_notor;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( bit_notor(a0, a1), map([](auto e, auto f) -> v_t { return ~e | f; }, a0, a1));
};

EVE_TEST( "Check behavior of bit_notor on floating types"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::as;
  using eve::bit_notor;
  using eve::bit_cast;
  using eve::detail::map;
  using i_t = eve::as_integer_t<eve::element_type_t<T>, signed>;
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL( bit_notor(a0, a1), map([](auto e, auto f) -> v_t
                                       { return  bit_cast(~bit_cast(e, as(i_t()))
                                                          | bit_cast(f, as(i_t())), as(v_t())); }
                                     , a0, a1));
};
