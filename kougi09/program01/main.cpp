#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


void display(cv::Mat image, std::string windowName = "Image") {
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
    cv::waitKey(1000 * 100);
    cv::destroyWindow(windowName);
}

int main(int argc, char* argv[]){

  cv::Mat img = cv::imread("road.jpg", 0);

  display(img);

  int x_size = img.cols;
  int y_size = img.rows ;
  int i, j;

  cv::Mat output = cv::Mat::zeros(y_size, x_size, CV_8UC1);

  for( i=0 ; i<x_size ; i++ ){
    for( j=0 ; j<y_size ; j++ ){
      if( img.at<uchar>(j, i) > 160 ){
        output.at<uchar>(j, i) = 255;
      };
    }
  }

  display(output);
    
  return 0;
}

