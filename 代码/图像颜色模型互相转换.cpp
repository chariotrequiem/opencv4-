#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main(int* argc,char** argv)
{
	Mat img = imread("D:/images/leena.png");
	if (img.empty())
	{
		cout << "could load the picture!" << endl;
		return -1;
	}
	Mat gray, HSV, YUV, Lab, img32;
	img.convertTo(img32, CV_32F, 1.0 / 255);//将CV_8U类型转换为CV_32F类型；
	//img32.convertTo(img,CV_8U,255);将CV_32F类型转换为CV_8U类型；
	cvtColor(img32, HSV, COLOR_BGR2HSV);
	cvtColor(img32, YUV, COLOR_BGR2YUV);
	cvtColor(img32, Lab, COLOR_BGR2Lab);
	cvtColor(img32, gray, COLOR_BGR2GRAY);
	imshow("原图", img32);
	imshow("HSV", HSV);
	imshow("YUV", YUV);
	imshow("Lab", Lab);
	imshow("Gray", gray);
	waitKey(0);
	return 0;
}