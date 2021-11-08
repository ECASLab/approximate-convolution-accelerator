#include <iostream>
#include <opencv2/opencv.hpp>

/*
 * Please, check the meson.build.
 * Notice that you may need to add another <project>_src list
 * and another new executable(<project>, ...)
 * Take this file as an example. Also, take into account the "open"
 * ones presented in the meson.build
 */

int main(int argc, char** argv) {
  if (argc != 2) {
    std::cerr << "Cannot open the file. No enough args" << std::endl;
    return -1;
  }
  cv::Mat img = cv::imread(argv[1]);
  cv::imshow("Img", img);
  cv::waitKey(0);
  return 0;
}
