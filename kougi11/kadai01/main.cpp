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
      // 完全に一致した場合、c の値は 0 になるはず
      // 完全に一致した画素を　255 として count に記録する
      if( c == 0 ) count.at<uchar>(j, i) = 255;
next_pixel:;
    }
  }

  // マッチング成功の位置を求め、箱で囲む（imageの画像に線を描画する）
  // 箱のサイズは、テンプレートのサイズ
  // 線分の描画は、次のように行う
  // cv::line(image, cv::Point(i,j), cv::Point(i+t_x_size,j+t_y_size), 0, 2);
  // 末尾のパラメータ 0 は画素値（黒で線を描画する）、2 は線の太さ

  display(image, "image");

  return 0;
}

