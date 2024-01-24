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


#define FILTER_SIZE 5                       // フィルタのサイズ
#define FILTER_SIZE2 (FILTER_SIZE / 2)      // フィルタの中心を除いたサイズの半分

int filter[FILTER_SIZE][FILTER_SIZE] = {
  {1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1},
};


int main(int argc, char* argv[]){
  
  cv::Mat src = cv::imread(argv[1], 0);

  display(src, "src");

  int x_size = src.cols;
  int y_size = src.rows;

  cv::Mat dst = cv::Mat::zeros(y_size, x_size, CV_8UC1);
  
  int i, j;
  for( j=FILTER_SIZE2 ; j<y_size-FILTER_SIZE2 ; j++){
    for( i=FILTER_SIZE2 ; i<x_size-FILTER_SIZE2 ; i++){
      // 画素(i,j)に対するフィルタ処理
      int m, n, pixel = 0;
      for( n=-FILTER_SIZE2 ; n<=FILTER_SIZE2 ; n++ ){
        for( m=-FILTER_SIZE2 ; m<=FILTER_SIZE2 ; m++ ){
          pixel += (int)src.at<uchar>(j+n,i+m) * filter[m+FILTER_SIZE2][n+FILTER_SIZE2];
        }
      }
      // フィルタの値を 1/25 倍にする
      pixel /= 25;
      // 飽和処理
      if( pixel < 0 ) pixel = 0;
      else if( pixel > 255 ) pixel = 255;
      // ピクセル値を dst に入れる
      dst.at<uchar>(j,i) = pixel;
    }
  }

  display(dst, "dst");

  cv::imwrite("dst_image.jpg", dst);

  return 0;
}

