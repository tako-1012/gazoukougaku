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

  int max_count = 1 << 30;
  cv::Mat count = cv::Mat::zeros(y_size, x_size, CV_8UC1);

  int i, j;
  for( j=0 ; j<y_size-t_y_size ; j++ ){
    for( i=0 ; i<x_size-t_x_size ; i++ ){
      // テンプレート比較をする
      int m, n, c = 0;
      for( n=0 ; n<t_y_size ; n++ ){
        for( m=0 ; m<t_x_size ; m++ ){
          c += abs( image.at<uchar>(j+n, i+m) - temp.at<uchar>(n, m) );
          if( c > max_count ) goto next_pixel;
        }
      }
      // 閾値以下であった点を記録する
      max_count = c;
      count.at<uchar>(j, i) = 255;
next_pixel:;
    }
  }

  display(count, "count");

  return 0;
}

