#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


int main(int argc, char* argv[]){

  cv::Mat img = cv::imread("circle.png");

  int x_size = img.cols;
  int y_size = img.rows ;
  int i, j;
  int count = 0;

  for( i=0 ; i<x_size ; i++ ){
    for( j=0 ; j<y_size ; j++ ){
      if( img.at<uchar>(j, i) == 0 ) count++;
    }
  }

  std::cout << "S=" << count << std::endl;
    
  return 0;
}

