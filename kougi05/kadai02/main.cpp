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

#define BLOCK_SIZE 8

int main(int argc, char* argv[]){
  
  cv::Mat src = cv::imread(argv[1], 0);

  display(src, "src");

  int x_size = src.cols;
  int y_size = src.rows;

  cv::Mat dst = cv::Mat::zeros(y_size, x_size, CV_8UC1);
  
  for(int j=0 ; j<y_size ; j+=BLOCK_SIZE){
    for(int i=0 ; i<x_size ; i+=BLOCK_SIZE){
      // 画素(i,j)に対するフィルタ処理
      int pixel_sum = 0;
      int count = 0;
      for(int n=0 ; n<BLOCK_SIZE && j+n<y_size ; n++ ){
        for(int m=0 ; m<BLOCK_SIZE && i+m<x_size ; m++ ){
          pixel_sum += (int)src.at<uchar>(j+n,i+m);
          count++;
        }
      }
      // ブロック内のピクセルの平均値を計算
      int pixel_avg = pixel_sum / count;
      // ブロック内のすべてのピクセルを平均値に置き換える
      for(int n=0 ; n<BLOCK_SIZE && j+n<y_size ; n++ ){
        for(int m=0 ; m<BLOCK_SIZE && i+m<x_size ; m++ ){
          dst.at<uchar>(j+n,i+m) = pixel_avg;
        }
      }
    }
  }

  display(dst, "dst");

  cv::imwrite("dst_image.jpg", dst);

  return 0;
}
