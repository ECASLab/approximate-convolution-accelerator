#include <complex>
#include <iostream>
#include <valarray>
#include "convolution.hpp"

const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

int main() {
  const Complex test[] = {1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0};
  CArray data(test, 8);

  // forward fft
  ama::sw::fft(data);

  std::cout << "fft" << std::endl;
  for (int i = 0; i < 8; ++i) {
    std::cout << data[i] << std::endl;
  }
  return 0;
}