#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


void display(cv::Mat image) {
    std::string windowName = "Image";
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
    cv::waitKey(1000 * 10);
    cv::destroyWindow(windowName);
}

int main(int argc, char* argv[]){
  
  cv::Mat img = cv::imread("Mandrill.jpg");

 if ( img.empty() ) {
    return -1;
  }

  int x_size = img.cols;
  int y_size = img.rows;

  cv::Mat gray = cv::Mat::zeros(y_size, x_size, CV_8UC1);  // 8bit, unsigned, Channel=1

  int i, j;
  for( j=0 ; j<y_size ; j++){
    for( i=0 ; i<x_size ; i++){
      cv::Vec3b pixel = img.at<cv::Vec3b>(j,i);
      int b = pixel[0];
      int g = pixel[1];
      int r = pixel[2];
      gray.at<uchar>(j,i) = (0.299 * r + 0.587 * g + 0.114 * b);
    }
  }

  display(gray);

  return 0;
}

