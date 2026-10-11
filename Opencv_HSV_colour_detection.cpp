
#include <opencv2/opencv.hpp>
#include <iostream>
cv::Mat imghsv, mask;
int hmin = 45, smin = 50, vmin = 66, hmax = 83, smax = 255, vmax = 255;
int main()
{
    std::string path = "C:/2.jpeg";
    cv::Mat img = cv::imread(path);
    if (img.empty())
    {
        std::cout << "Image not found" << std::endl;
        return 0;
    }
    cv::cvtColor(img, imghsv, cv::COLOR_BGR2HSV);
    cv::namedWindow("Trackbar", (640, 340));
    cv::createTrackbar("Hue min", "Trackbar", &hmin, 180);
    cv::createTrackbar("Saturation min", "Trackbar", &smin, 255);
    cv::createTrackbar("Vmin", "Trackbar", &vmin, 255);
    cv::createTrackbar("Hue max", "Trackbar", &hmax, 180);
    cv::createTrackbar("Saturation max", "Trackbar", &smax, 255);
    cv::createTrackbar("Vmax", "Trackbar", &vmax, 255);
    while (true)
    {
        cv::Scalar lower(hmin, smin, vmin);
        cv::Scalar upper(hmax, smax, vmax);
        cv::inRange(imghsv, lower, upper, mask);
        cv::imshow("Mask", mask);
        cv::imshow("hsv", imghsv);
        cv::imshow("Image", img);
        cv::waitKey(1);
    }
    return 0;
}
