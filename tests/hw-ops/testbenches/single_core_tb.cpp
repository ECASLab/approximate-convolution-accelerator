/*
 * Copyright 2021
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#include <iostream>
#include <opencv2/opencv.hpp>

#include "single_core.hpp"
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

template<typename T = uint8_t, bool norm = true>
static void CopyMatToArray(const cv::Mat &input, DataType *output,
                    const cv::Rect &roi) {
  for (int i{0}; i < roi.height; ++i) {
    for (int j{0}; j < roi.width; ++j) {
      float val = input.at<T>(i + roi.y, j + roi.x);
      output[i * roi.width + j] = norm ? (val / 256.f - 0.5f) : val;
    }
  }
}

template<typename T = uint8_t>
static void CopyMatFromArray(const DataType *input, cv::Mat &output,
                      const cv::Rect &roi) {
  for (int i{0}; i < roi.height; ++i) {
    for (int j{0}; j < roi.width; ++j) {
      float val = input[i * roi.width + j];
      output.at<T>(roi.y + i, j + roi.x) = (val + 0.5f) * 256.f;
    }
  }
}

static void CvFilter(const cv::Mat & input,
                           const cv::Mat & kernel,
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

  cv::Mat input_img, output_img, output_sw, kernel_gauss;

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
  kernel_gauss = get_filter(Q_K);
  CopyMatToArray<double, false>(kernel_gauss, kernel[0], cv::Rect{0, 0, Q_K, Q_K});
  std::cout << "Kernel: " << std::endl;
  ama::utils::print_matrix<DataType, Q_K, Q_K>(kernel);

  cv::Mat input_img_pad{input_img.rows + 2, input_img.cols + 2,
                        input_img.type()};
  cv::Mat roi_input_img_pad =
      input_img_pad(cv::Rect{1, 1, input_img.cols, input_img.rows});
  input_img.copyTo(roi_input_img_pad);

  output_img = cv::Mat::zeros(input_img.size(), input_img.type());
  std::cout << "Image size: " << output_img.size() << std::endl;

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
      CopyMatFromArray(output_batch[0], output_img, roi_out);
    }
  }

  std::cout << "Finished" << std::endl;

  /* Compute the SW version */
  CvFilter(input_img, kernel_gauss, output_sw);

  /* Print output matrices */
  if (argc < 3) {
    cv::imwrite(kDefaultOutputImage, output_img);
    cv::imwrite(kDefaultOutputImage + "-sw.png", output_sw);
  } else {
    cv::imwrite(argv[2], output_img);
    cv::imwrite(std::string{argv[2]} + "-sw.png", output_sw);
  }

  /* Co-sim patch */
  single_core_top_accel(input_batch, kernel, output_batch);

  return ret;
}
