/*
 * Copyright 2022
 * Author: Luis G. Leon-Vega <lleon95@estudiantec.cr>
 */

#pragma once

#include <opencv2/opencv.hpp>
#include <tuple>

namespace ama {
namespace utils {

double mse(const cv::Mat golden, const cv::Mat sample) {
  assert(!golden.empty());
  assert(!sample.empty());

  /* Take the first one as golden data */
  cv::Mat golden_float, sample_float;
  golden.convertTo(golden_float, CV_64F);
  sample.convertTo(sample_float, CV_64F);

  /* Compute differences */
  cv::Mat diff = golden_float - sample_float;
  cv::Mat squared = diff.mul(diff);

  /* Full reduce */
  cv::Mat col_sum, singleton;
  cv::reduce(squared, col_sum, 0, 0, CV_64F);
  cv::reduce(col_sum, singleton, 1, 0, CV_64F);

  return singleton.at<double>(0, 0) / (golden.rows * golden.cols);
}

std::pair<double, double> mean_std(const cv::Mat matrix) {
  assert(!matrix.empty());

  /* Take the first one as golden data */
  cv::Mat matrix_float;
  matrix.convertTo(matrix_float, CV_64F);

  /* Full reduce */
  cv::Mat mean_mat, std_mat;
  cv::meanStdDev(matrix_float, mean_mat, std_mat);

  return std::pair<double, double>(mean_mat.at<double>(0, 0),
                                   std_mat.at<double>(0, 0));
}

std::pair<double, double> min_max(const cv::Mat &matrix) {
  /* Find the max of the golden */
  double min_val, max_val;
  cv::Point min_loc, max_loc;
  cv::minMaxLoc(matrix, &min_val, &max_val, &min_loc, &max_loc);
  return std::pair<double, double>{min_val, max_val};
}

double psnr(const cv::Mat golden, const cv::Mat sample) {
  assert(!golden.empty());
  assert(!sample.empty());

  /* Compute the MSE */
  double mse_ = mse(golden, sample);

  /* Compute the max */
  cv::Mat golden_float;
  golden.convertTo(golden_float, CV_64F);

  /* Find the max of the golden */
  auto min_max_ = min_max(golden_float);
  double max_ = min_max_.second;

  return (20 * std::log10(max_) - 10 * std::log10(mse_));
}

}  // namespace utils
}  // namespace ama
