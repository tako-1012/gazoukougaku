#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

void display(cv::Mat image, std::string windowName = "Image") {
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
    cv::waitKey(1000 * 100);
    cv::destroyWindow(windowName);
}

int main(int argc, char* argv[]){
  
  if( argc != 3 ){
    std::cout << argv[0] << " : <file> <theta>" << std::endl;
    exit(0);
  }

  cv::Mat src = cv::imread(argv[1], 0);

  int size_x = 30;
  int size_y = 30;
  int sigma = 4;
  float theta = atoi(argv[2]) * M_PI / 180.0;
  float lm = 8, gm = 0.02, ps = 0;

  cv::Mat gabor, dst;
  gabor = cv::getGaborKernel(cv::Size(size_x,size_y), sigma, theta, lm, gm, ps, CV_32F);

  cv::filter2D(src, dst, -1, gabor);

  display(dst);

  return 0;
}

