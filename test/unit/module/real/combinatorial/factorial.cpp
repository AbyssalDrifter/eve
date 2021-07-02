//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/factorial.hpp>
#include <eve/logical.hpp>
#include <cmath>



//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::factorial"
              , eve::test::simd::unsigned_integers)
<typename T>(eve::as<T>)
{
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::factorial(T())                       , d_t);
  TTS_EXPR_IS( eve::factorial(v_t())                     , double );
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST_TYPES( "Check corner-cases behavior of eve::factorial on wide"
        , eve::test::simd::unsigned_integers

         )
  <typename T>(eve::as<T>)
{
  using eve::as;
  using d_t = eve::wide<double, eve::cardinal_t<T>>;
  TTS_EQUAL(eve::factorial(T(10)) , d_t(3628800));
  TTS_EQUAL(eve::factorial(T( 5)) , d_t(120));
  TTS_EQUAL(eve::factorial(T(0))  , d_t(1));
  TTS_EQUAL(eve::factorial(T(1))  , d_t(1));
};
