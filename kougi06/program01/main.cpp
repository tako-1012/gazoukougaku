#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


void display(cv::Mat image, std::string windowName = "Image") {
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
    cv::waitKey(1000 * 10);
    cv::destroyWindow(windowName);
}


int main(int argc, char* argv[]){
  
  cv::Mat src = cv::imread(argv[1], 0);

  display(src, "src");

  int x_size = src.cols;
  int y_size = src.rows;

  cv::Mat f_src, f_dst, dst;

  src.convertTo(f_src, CV_32FC1);
  dct(f_src, f_dst);
  f_dst.convertTo(dst, CV_8UC1);

  display(dst, "dst");

//  cv::imwrite("dst_image.jpg", dst);

  return 0;
}

