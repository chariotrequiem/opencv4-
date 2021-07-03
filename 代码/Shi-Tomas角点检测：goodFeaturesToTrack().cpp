// opencv_contrib_test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>


int main()
{
	//SURF
	cv::Ptr<cv::xfeatures2d::SURF> surf = cv::xfeatures2d::SURF::create();
	cv::waitKey(0);
	return 0;
}