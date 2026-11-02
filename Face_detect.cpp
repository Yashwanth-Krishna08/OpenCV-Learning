#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/objdetect.hpp>
#include<vector>
void main()
{
	cv::VideoCapture cap(0);
	cv::Mat image,grey;
	cv::CascadeClassifier faceCascade("C:/Yachu/haarcascade_frontalface_alt.xml");
	if (faceCascade.empty()) {
		std::cout << "Not loaded" << std::endl;
	}
	while (true)
	{
		cap.read(image);

		
		cv::cvtColor(image, grey, cv::COLOR_BGR2GRAY);
		std::vector<cv::Rect>faces;
		faceCascade.detectMultiScale(grey, faces, 1.1, 10);
		for (int i = 0;i < faces.size();i++)
		{
			cv::rectangle(image, faces[i].tl(), faces[i].br(), cv::Scalar(255, 0, 0), 1, 8);
		}
		cv::imshow("hi", image);
		cv::waitKey(2);
	}
	
}