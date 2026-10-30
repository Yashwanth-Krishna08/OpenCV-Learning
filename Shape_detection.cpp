#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
void getcontour(cv::Mat imgdil,cv:: Mat img)
{
	std::vector<std::vector<cv::Point>> contour;
	std::vector<cv::Vec4i> h;
	cv::findContours(imgdil, contour, h, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
	std::vector<std::vector<cv::Point>> conploy(contour.size());
	std::string objtype;
	for (int i = 0;i < contour.size();i++)
	{
		int area = contourArea(contour[i]);
		std::cout << area << std::endl;
		if (area >= 1000)
		{
			float peri = cv::arcLength(contour[i], true);
			cv::approxPolyDP(contour[i], conploy[i], 0.02*peri, true);
			cv::drawContours(img, conploy, i, cv::Scalar(255, 0, 0), 2);
			std::cout << conploy[i].size() << std::endl;
			double c = 4 * CV_PI * area / (peri * peri);
			cv::Rect box = cv::boundingRect(conploy[i]);
			int corner = conploy[i].size();
			if (corner == 4) {
				cv::Rect rr = cv::boundingRect(conploy[i]);
				int w = rr.size().width;
				int h = rr.size().height;
				double arr = std::min(w, h) / std::max(w, h);
				objtype = (arr > 0.95) ? "Square" : "Rect";
			}
			else if (corner == 3) { objtype = "tri"; }
			else if (corner== 6) { objtype = "hex"; }
			else if (c>=0.8 ) { objtype = "circle"; }
			else { objtype = "unknown"; }
			std::cout << objtype << std::endl;
			cv::putText(img, objtype, cv::Point(box.x, box.y), 1, 1, cv::Scalar(255, 0, 0), 1, true);
		}

	}
}
void main()
{
	std::string path = "C:/Yachu/2.jpeg";
	cv::Mat img = cv::imread(path),imgblur,imgcanny,imgdil,imgray;
	cv::cvtColor(img, imgray, cv::COLOR_BGR2GRAY);
	cv::GaussianBlur(imgray, imgblur, cv::Size(3,3), 3,0);
	//cv::imshow("image blur",imgblur);
	cv::Canny(imgblur, imgcanny, 75, 25);
	cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
	cv::dilate(imgcanny, imgdil, kernel);
	getcontour(imgdil, img);
	//cv::imshow("dilate", imgdil);
	//cv::imshow("Canny", imgcanny);
	cv::imshow("image", img);
	cv::waitKey(0);
}