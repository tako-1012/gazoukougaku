#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char* argv[]){
  
    cv::Mat img = cv::imread("Mandrill_gray.png");

    int height = img.rows;
    int width = img.cols;

    int Imin, Imax, Imode;
    double u;

    Imin = 256;
    Imax = -1;
    u = 0;
    Imode = 0;

    int x, y;

    int value, count;

    int sum = 0;

    for(x = 0; x < width; x++){
        for(y = 0; y < height; y++){
            value = img.at<unsigned char>(y, x);

            sum += value;

            if(value > Imax){
                Imax = value;
            }
            if(value < Imin){
                Imin = value;
            }
        }
    }

    u = sum/(width*height);

    //最頻値を調べる配列をMにする
    int M[256];

    int i;

    for(i = 0; i < 256; i++){
        M[i] = 0;
    }

    for(x = 0; x < width; x++){
        for(y = 0; y < height; y++){
            value = img.at<unsigned char>(y, x);
            M[value]++;
        }
    }

    int max = 0;

    for(i = 0; i < 256; i++){
        if(max < M[i]){
            max = M[i];
            Imode = i;
        }
    }

    printf("Imin = %d\n", Imin);
    printf("Imax = %d\n", Imax);
    printf("µ = %lf\n", u);
    printf("Imode = %d\n", Imode);
    

    if ( img.empty() ) {
        return -1;
    }

    return 0;
}

