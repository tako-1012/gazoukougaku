#include <iostream>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>

int main(int argc, char* argv[]){
    cv::Mat img = cv::imread("home.jpg");

    if ( img.empty() ) {
        return -1;
    }

    int x = 100, y = 50;
    cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);
    std::cout << pixel << std::endl;

    return 0;
}
