/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>
#include <opencv2/opencv.hpp>

#include "single_core.hpp"
#include "utils/image_stats.hpp"
#include "utils/printmatrix.hpp"

#define ANCHOR cv::Point(-1, -1)
#define BORDER_TYPE cv::BORDER_CONSTANT
#define DELTA 0
#define IMAGE_DEPTH CV_64F

static cv::Mat get_filter(const int kernel_size) {
  cv::Mat filter;
  double sigma;

  sigma = (kernel_size + 2) / 6;

  filter = cv::getGaussianKernel(kernel_size, sigma, IMAGE_DEPTH);
  return filter * filter.t();
}

template <typename T = uint8_t, bool norm = true>
static void CopyMatToArray(const cv::Mat &input, DataType *output,
                           const cv::Rect &roi) {
  for (int i{0}; i < roi.height; ++i) {
    for (int j{0}; j < roi.width; ++j) {
      float val = input.at<T>(i + roi.y, j + roi.x);
      output[i * roi.width + j] = norm ? (val / 256.f - 0.5f) : val;
    }
  }
}

template <typename T = uint8_t, bool norm = true>
static void CopyMatFromArray(const DataType *input, cv::Mat &output,
                             const cv::Rect &roi) {
  for (int i{0}; i < roi.height; ++i) {
    for (int j{0}; j < roi.width; ++j) {
      float val = input[i * roi.width + j];
      output.at<T>(roi.y + i, j + roi.x) = norm ? ((val + 0.5f) * 256.f) : val;
    }
  }
}

static void CvFilter(const cv::Mat &input, const cv::Mat &kernel,
                     cv::Mat &output) {
  cv::filter2D(input, output, IMAGE_DEPTH, kernel, ANCHOR, DELTA, BORDER_TYPE);
}

int main(int argc, char **argv) {
  const std::string kDefaultInputImage{"misc/lenna"};
  const std::string kDefaultOutputImage{"misc/lenna-output"};
  const bool kEnablePrinting = false;
  int ret = 0;
  DataType output_batch[kOutputSize][kOutputSize];
  DataType input_batch[kWindowSize][kWindowSize];
  DataType kernel[Q_K][Q_K];

  cv::Mat input_img, output_hw, output_sw, kernel_sw;

  /* Get the input image */
  if (argc < 2) {
    input_img = cv::imread(kDefaultInputImage, 0);
  } else {
    input_img = cv::imread(argv[1], 0);
  }

  /* Check it */
  if (input_img.empty()) {
    std::cerr << "Cannot open the image" << std::endl;
    return -1;
  }

  /* Copy the kernel */
  kernel_sw = get_filter(Q_K);
  CopyMatToArray<double, false>(kernel_sw, kernel[0], cv::Rect{0, 0, Q_K, Q_K});
  std::cout << "Kernel: " << std::endl;
  ama::utils::print_matrix<DataType, Q_K, Q_K>(kernel);

  cv::Mat input_img_pad{input_img.rows + 2, input_img.cols + 2,
                        input_img.type()};
  cv::Mat roi_input_img_pad =
      input_img_pad(cv::Rect{1, 1, input_img.cols, input_img.rows});
  input_img.copyTo(roi_input_img_pad);

  output_hw = cv::Mat::zeros(input_img.size(), input_img.type());
  std::cout << "Image size: " << output_hw.size() << std::endl;

  /* Send matrix */
  const int step_x = kOutputSize;
  const int step_y = kOutputSize;
  const int offset = Q_K / 2;

  for (int i{0}; i < (input_img.rows - Q_K + 2); i += step_y) {
    for (int j{0}; j < (input_img.cols - Q_K + 2); j += step_x) {
      /* Get the ROI and load the data */
      cv::Rect roi_in{j, i, kWindowSize, kWindowSize};
      CopyMatToArray(input_img_pad, input_batch[0], roi_in);

      /* Process matrix */
      if (kEnablePrinting) {
        ama::utils::print_matrix<DataType, kWindowSize, kWindowSize>(
            input_batch);
      }
      single_core_top_accel(input_batch, kernel, output_batch);
      if (kEnablePrinting) {
        ama::utils::print_matrix<DataType, kOutputSize, kOutputSize>(
            output_batch);
      }

      /* Get results */
      cv::Rect roi_out{j + offset - 1, i + offset - 1, step_x, step_y};
      CopyMatFromArray(output_batch[0], output_hw, roi_out);
    }
  }

  /* Compute the SW version */
  CvFilter(input_img, kernel_sw, output_sw);

  /* Print output matrices */
  if (argc < 3) {
    cv::imwrite(kDefaultOutputImage, output_hw);
    cv::imwrite(kDefaultOutputImage + "-sw.png", output_sw);
  } else {
    cv::imwrite(argv[2], output_hw);
    cv::imwrite(std::string{argv[2]} + "-sw.png", output_sw);
  }

  /* Extract frame differences and error */
  cv::Rect roi_out{offset, offset, input_img.cols - Q_K, input_img.rows - Q_K};

  cv::Mat output_chop_sw, output_chop_hw;
  output_sw(roi_out).convertTo(output_chop_sw, CV_64F);
  output_hw(roi_out).convertTo(output_chop_hw, CV_64F);

  cv::Mat abs_difference = (cv::abs(output_chop_sw - output_chop_hw) / 256.);
  auto mean_std = ama::utils::mean_std(abs_difference);

  std::cout << "Image RMSE: "
            << std::sqrt(ama::utils::mse(output_chop_sw, output_chop_hw)) / 256.
            << std::endl;
  std::cout << "Image PSNR: "
            << ama::utils::psnr(output_chop_sw, output_chop_hw) << std::endl;
  std::cout << "Image Mean: " << mean_std.first << std::endl;
  std::cout << "Image Std: " << mean_std.second << std::endl;
  /* 30% */
  std::cout << "Hist 500 bins 30%: "
            << ama::utils::histogram(abs_difference, 500, 0.30) << std::endl;

  /* Extract kernel differences */
  cv::Mat kernel_hw{kernel_sw.size(), kernel_sw.type()};
  CopyMatFromArray<double, false>(kernel[0], kernel_hw,
                                  cv::Rect{0, 0, Q_K, Q_K});

  abs_difference = cv::abs(kernel_sw - kernel_hw);
  mean_std = ama::utils::mean_std(abs_difference);

  std::cout << "Kernel RMSE: "
            << std::sqrt(ama::utils::mse(kernel_sw, kernel_hw)) << std::endl;
  std::cout << "Kernel PSNR: " << ama::utils::psnr(kernel_sw, kernel_hw)
            << std::endl;
  std::cout << "Kernel Mean: " << mean_std.first << std::endl;
  std::cout << "Kernel Std: " << mean_std.second << std::endl;
  std::cout << abs_difference << std::endl;

  /* Co-sim patch */
  single_core_top_accel(input_batch, kernel, output_batch);

  return ret;
}
