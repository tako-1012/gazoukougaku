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

int main(void){
  
  cv::Mat image = cv::imread("image.png", 0);
  cv::Mat temp = cv::imread("template.png", 0);

  display(image, "src");

  int x_size = image.cols;
  int y_size = image.rows;
  int t_x_size = temp.cols;
  int t_y_size = temp.rows;

  int max_count = 0;
  cv::Mat count = cv::Mat::zeros(y_size, x_size, CV_8UC1);

  int i, j;
  for( j=0 ; j<y_size-t_y_size ; j++ ){
    for( i=0 ; i<x_size-t_x_size ; i++ ){
      // テンプレート比較をする
      int m, n, c = 0;
      for( n=0 ; n<t_y_size ; n++ ){
        for( m=0 ; m<t_x_size ; m++ ){
          if( image.at<uchar>(j+n, i+m) == temp.at<uchar>(n, m) ) c++;
        }
      }
      // 一致した画素数を記録する
      // 0～255の値になるようにする
      c /= (t_x_size * t_y_size / 256 + 0.5);
      if( c < 0 ) c = 0;
      else if( c > 255 ) c = 255;
      count.at<uchar>(j, i) = c;
    }
  }

  display(count, "count");

  return 0;
}

