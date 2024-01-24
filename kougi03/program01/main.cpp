#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


void make_histgram(cv::Mat img, int hist[])
{
  int x_size = img.cols;
  int y_size = img.rows ;
  int i, j;
  for( i=0 ; i<256 ; i++ ){
    hist[i] = 0;
  }

  for( i=0 ; i<x_size ; i++ ){
    for( j=0 ; j<y_size ; j++ ){
      hist[img.at<uchar>(j, i)]++;
    }
  }
}

int main(int argc, char* argv[]){
  
    cv::Mat img = cv::imread("Mandrill_gray.png");

    if ( img.empty() ) {
        return -1;
    }

    int hist[256];
    make_histgram(img, hist);

    int i;
    for( i=0 ; i<256 ; i++ ){
      std::cout << i << " : " << hist[i] << std::endl;
    }
    
    return 0;
}

