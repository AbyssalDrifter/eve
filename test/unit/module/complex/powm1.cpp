//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH ( "Check behavior of powm1 on wide"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              , tts::randoms(0.1, 10)
                              )
              )
<typename T>(T const& a0, T const& a1, T const& a2, T const& a3 )
{
//  auto ulp = 100.0;
  using z_t = eve::as_complex_t<T>;
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  using ce_t = eve::complex<e_t>;
  auto a = z_t(a0, a1);
  auto b = z_t(a2, a3);
  auto o = c_t(1);

  auto init_with_std = [=](auto i, auto)
  {
    return cv(std::pow( c_t(a0.get(i), a1.get(i)), c_t(a2.get(i), a3.get(i)))-o);
  };
  auto init_with_std1 = [=](auto i, auto)
  {
    return cv(std::pow( c_t(eve::abs(a0.get(i)), 0), c_t(a2.get(i), a3.get(i)))-o);
  };
  auto init_with_std2 = [=](auto i, auto)
  {
    return cv(std::pow( c_t(-eve::abs(a0.get(i)), 0), c_t(a2.get(i), a3.get(i)))-o);
  };
  auto init_with_std3 = [=](auto i, auto)
  {
    return cv(std::pow(c_t(a2.get(i), a3.get(i)),  c_t(eve::abs(a0.get(i)), 0))-o);
  };

  TTS_RELATIVE_EQUAL( eve::powm1(a, b) , z_t{init_with_std}, 0.5);
  TTS_ULP_EQUAL( eve::powm1(a, 2u), eve::dec(eve::sqr(a)), 300);
  TTS_ULP_EQUAL( eve::powm1(a, 3u), eve::dec(eve::sqr(a)*a),  300);
  TTS_ULP_EQUAL( eve::powm1(eve::abs(a0), b)   , z_t{init_with_std1}, 300);
  TTS_ULP_EQUAL( eve::powm1(-eve::abs(a0), b)   , z_t{init_with_std2}, 300);
  TTS_RELATIVE_EQUAL( eve::powm1(b, eve::abs(a0))   ,  z_t{init_with_std3}, 0.5);
  TTS_ULP_EQUAL( eve::powm1(a, 3u)   , eve::powm1(a, e_t(3)),  10);
  TTS_ULP_EQUAL( eve::powm1(a, 2u)   , eve::powm1(a, e_t(2)),  10);
  TTS_ULP_EQUAL( eve::powm1(a, -2)   , eve::powm1(a, e_t(-2)),  10);
  TTS_ULP_EQUAL( eve::powm1(ce_t(0, 0), ce_t(0, 0)), ce_t(0, 0), 10);
  TTS_ULP_EQUAL( eve::powm1(ce_t(1, 0), ce_t(0, 0)), ce_t(0, 0), 10);
  TTS_ULP_EQUAL( eve::powm1(ce_t(1, 3), ce_t(0, 0)), ce_t(0, 0), 10);

  using eve::as;
  auto inf = eve::inf(as<e_t>());
  auto minf = eve::minf(as<e_t>());
  auto nan = eve::nan(as<e_t>());

  TTS_ULP_EQUAL( eve::powm1(ce_t(inf, 0), ce_t(0, 0)), ce_t(0, 0), 10);
  TTS_ULP_EQUAL( eve::powm1(ce_t(minf, 0), ce_t(0, 0)), ce_t(0, 0), 10);
  TTS_ULP_EQUAL( eve::powm1(ce_t(nan, 0), ce_t(0, 0)), ce_t(0, 0), 10);
  TTS_ULP_EQUAL( eve::powm1(ce_t(nan, 1), ce_t(0, 0)), ce_t(0, 0), 10);
  TTS_ULP_EQUAL( eve::powm1(ce_t(0, 0),  ce_t(0, 0)), ce_t(0, 0), 10);
};

TTS_CASE_WITH( "Check behavior of powm1 on wide"
             , eve::test::simd::ieee_reals
             , tts::generate( tts::randoms(-10, 10)
                            , tts::randoms(-10, 10))
             )
  <typename T>(T const& a0, T const&  a1)
{
  using z_t = eve::as_complex_t<T>;

  TTS_RELATIVE_EQUAL(eve::domain::complex(eve::powm1)(a0, a1), eve::powm1(z_t(a0), z_t(a1)), 5.0e-3);
  TTS_RELATIVE_EQUAL(eve::domain::complex(eve::powm1)(a0, a1), eve::domain::complex(eve::powm1)(z_t(a0), z_t(a1)), 5.0e-3);
};
