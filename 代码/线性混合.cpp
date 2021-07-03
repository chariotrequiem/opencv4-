#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
//利用addWeight函数实现图像线性混合
int main(int argc, char** argv)
{
	Mat src1 = imread("D:/images/a.jpg");
	Mat src2 = imread("D:/images/b.jpg");
	Mat dst;
	if (src1.empty())
	{
		cout << "src1 could not load!" << endl;
	}
	if (src2.empty())
	{
		cout << "src2 could not load!" << endl;
	}
	double alphavalue = 0.5;
	double betavalue = 1 - alphavalue;
	double gamma = 0;
	addWeighted(src1, alphavalue, src2, betavalue, gamma, dst);
	namedWindow("原图1", WINDOW_FREERATIO);
	namedWindow("原图2", WINDOW_FREERATIO);
	namedWindow("线性混合图", WINDOW_FREERATIO);
	imshow("原图1", src1);
	imshow("原图2", src2);
	imshow("线性混合图", dst);
	waitKey(0);
	return 0;
}