#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


int main(int argc, char* argv[]){

  cv::Mat img = cv::imread("circle.png", 0);

  int x_size = img.cols;
  int y_size = img.rows;
  int left = x_size - 1;
  int right = 0;
  int top = y_size - 1;
  int bottom = 0;
  int i, j;
  int count = 0;

  for( i=0 ; i<x_size ; i++ ){
    for( j=0 ; j<y_size ; j++ ){
      if( img.at<uchar>(j, i) == 0 ){
        if(i < left){
          left = i;
        }
        if(i > right){
          right = i;
        }
        if(j < top){
          top = j;
        }
        if(j > bottom){
          bottom = j;
        }
      }
      count++;
    }
  }
  double Gx, Gy;
  Gx = (left + right)/2.0;
  Gy = (top + bottom)/2.0;

  std::cout << "S=" << count << std::endl;
  std::cout << "lefttopx=" << left << std::endl;
  std::cout << "lefttopy=" << top << std::endl;
  std::cout << "rightbottomx=" << right << std::endl;
  std::cout << "rightbottomy=" << bottom << std::endl;
  std::cout << "Gx=" << Gx << std::endl;
  std::cout << "Gy=" << Gy<< std::endl;
    
  return 0;
}

