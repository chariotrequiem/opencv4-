// opencv_contrib_test.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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