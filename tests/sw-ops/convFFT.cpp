/*
 * Copyright 2021
 * Author: Alejandro Rodriguez Figueroa <alejandrorf@estudiantec.cr>
 * Supervisor: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <complex>
#include <iostream>
#include <valarray>
#include "convolution.hpp"
#include <opencv2/opencv.hpp>

#define MRows 512
#define NCols 512

const double PI = 3.141592653589793238460;

typedef std::complex<float> Complex;
typedef std::valarray<Complex> CArray;

int main(int argc, char** argv) {
   if (argc != 2) {
     std::cerr << "Cannot open the file. No enough args" << std::endl;
     return -1;
   }
   cv::Mat img = cv::imread(argv[1], 0);
  //  const int MRows = img.rows;
  //  const int NCols = img.cols;
   Complex a[MRows][NCols] = {0};
   //CArray data(a, MRows);
   //Complex out_a[MRows][NCols] = {0};
   for (int i{0}; i < MRows; ++i) {
     for (int j{0}; j < NCols; ++j) {
       a[i][j] = img.at<uint8_t>(i, j);
     }
   }
  ama::sw::fft_2D<Complex, CArray, MRows, NCols>(a);


  // const Complex test[MRows];
  // CArray data(test, MRows);

  // for (int i{0}; i < MRows; ++i) {
  //   for (int j{0}; j < NCols; ++j) {
  //     const Complex test[j] = a[i][j];
  //   }
  //   CArray data(test, MRows);
  //   ama::sw::fft(data);
  //   for (int k{0}; k < NCols; ++k) {
  //   out_a[i][k] = data[k];
  //   }
  // }





//trabajo despues
  // for (int i{0}; i < MRows; ++i) {
  //   for (int j{0}; j < NCols; ++j) {
  //     const Complex test[i] = a[j][i];
  //     ama::sw::fft(data);
  //   }
  // }

  // forward fft
  // ama::sw::fft(data);

  //  std::cout << "fft" << std::endl;
  //   for (int i = 0; i < 8; ++i) {
  //     std::cout << data[i] << std::endl;
  //   }
  return 0;
}