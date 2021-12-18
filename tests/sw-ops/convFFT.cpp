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

#define K 7
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

   Complex a[MRows][NCols] = {0};

   for (int i{0}; i < MRows; ++i) {
     for (int j{0}; j < NCols; ++j) {
       a[i][j] = img.at<uint8_t>(i, j);
     }
   }

  float c[K][K];
  #if K == 5
    ama::utils::add_kernel5<float, K>(c);
  #elif K == 7
    ama::utils::add_kernel7<float, K>(c);
  #elif K == 3
    ama::utils::add_kernel3<float, K>(c);
  #else
  #error "Cannot proceed with the given kernel"
  #endif

  ama::sw::fft_conv_2D<float, MRows, NCols, K>(a, c);

  cv::Mat a_img(MRows , NCols, CV_8U, a);
  for (int i{0}; i < MRows; ++i) {
    for (int j{0}; j < NCols; ++j) {
      a_img.at<uint8_t>(i, j) = a[i][j].real();
    }
  }

  cv::imshow("a_img", a_img);
  cv::imshow("img", img);
  cv::waitKey(0);

  return 0;
}