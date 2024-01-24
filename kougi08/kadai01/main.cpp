#include <iostream>
#include <string>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>


void display(cv::Mat image, std::string windowName = "Image") {
    cv::namedWindow(windowName);
    cv::imshow(windowName, image);
}

int main(void){
  
  cv::Mat img_lobby = cv::imread("lobby.jpg");
  cv::Mat img_mandrill = cv::imread("Mandrill.png");

  display(img_lobby, "src");

  std::vector<cv::Point2f> lobby_points1(4);
  lobby_points1[0] = cv::Point2f(373, 415);
  lobby_points1[1] = cv::Point2f(370, 716);
  lobby_points1[2] = cv::Point2f(497, 729);
  lobby_points1[3] = cv::Point2f(496, 398);
  
  std::vector<cv::Point2f> lobby_points2(4);
  lobby_points2[0] = cv::Point2f(605, 383);
  lobby_points2[1] = cv::Point2f(605, 740);
  lobby_points2[2] = cv::Point2f(790, 755);
  lobby_points2[3] = cv::Point2f(780, 360);

  std::vector<cv::Point2f> lobby_points3(4);
  lobby_points3[0] = cv::Point2f(937, 338);
  lobby_points3[1] = cv::Point2f(953, 769);
  lobby_points3[2] = cv::Point2f(1226, 791);
  lobby_points3[3] = cv::Point2f(1197, 304);

  std::vector<cv::Point2f> mandrill_points(4);
  mandrill_points[0] = cv::Point2f(0, 0);
  mandrill_points[1] = cv::Point2f(0, 255);
  mandrill_points[2] = cv::Point2f(255, 255);
  mandrill_points[3] = cv::Point2f(255, 0);

  cv::Mat matrix1, matrix2, matrix3;
  matrix1 = cv::getPerspectiveTransform(mandrill_points, lobby_points1);
  matrix2 = cv::getPerspectiveTransform(mandrill_points, lobby_points2);
  matrix3 = cv::getPerspectiveTransform(mandrill_points, lobby_points3);

  std::cout << matrix1 << std::endl;
  std::cout << matrix2 << std::endl;
  std::cout << matrix3 << std::endl;

  cv::Mat img_transformed_mandrill1;
  warpPerspective(img_mandrill, img_transformed_mandrill1, matrix1, cv::Size(img_lobby.cols, img_lobby.rows));
  cv::Mat img_transformed_mandrill2;
  warpPerspective(img_mandrill, img_transformed_mandrill2, matrix2, cv::Size(img_lobby.cols, img_lobby.rows));
  cv::Mat img_transformed_mandrill3;
  warpPerspective(img_mandrill, img_transformed_mandrill3, matrix3, cv::Size(img_lobby.cols, img_lobby.rows));

  cv::Mat img_white1 = img_mandrill.clone();
  img_white1 = cv::Scalar(255, 255, 255);
  cv::Mat img_white2 = img_mandrill.clone();
  img_white2 = cv::Scalar(255, 255, 255);
  cv::Mat img_white3 = img_mandrill.clone();
  img_white3 = cv::Scalar(255, 255, 255);
  
  cv::Mat mask1, mask2, mask3;
  warpPerspective(img_white1, mask1, matrix1, cv::Size(img_lobby.cols, img_lobby.rows));
  warpPerspective(img_white2, mask2, matrix2, cv::Size(img_lobby.cols, img_lobby.rows));
  warpPerspective(img_white3, mask3, matrix3, cv::Size(img_lobby.cols, img_lobby.rows));

  img_transformed_mandrill1.copyTo(img_lobby, mask1);
  img_transformed_mandrill2.copyTo(img_lobby, mask2);
  img_transformed_mandrill3.copyTo(img_lobby, mask3);

  display(img_lobby, "dst");

  cv::imwrite("dst_image.jpg", img_lobby);

  cv::waitKey(1000 * 100);
  cv::destroyWindow("src");
  cv::destroyWindow("dst");

  return 0;
}

