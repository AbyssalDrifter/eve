#include <eve/function/sqrt.hpp>
#include <eve/wide.hpp>

using wide_ft = eve::wide<float, eve::fixed<4>>;

int main()
{
  wide_ft pf = {-1.0f, 2.0f, -3.0f, -32768.0f};

  std::cout << "---- simd" << '\n'
            << "<- pf =                            " << pf << '\n'
            << "-> eve::sqrt(pf) =                  " << eve::sqrt(pf) << '\n'; 


  float        xf = -32768.0f;

  std::cout << "---- scalar" << '\n'
            << "<- xf =                            " << xf << '\n'
            << "-> eve::sqrt(xf) =                  " << eve::sqrt(xf) << '\n'; 
  return 0;
}
