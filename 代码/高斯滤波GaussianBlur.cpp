#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char**argv)
{
	Mat src = imread("D:/images/6.jpg");
	if (src.empty())
	{
		cout << "could not load the picture" << endl;
	}
	namedWindow("高斯滤波源图");
	namedWindow("高斯滤波效果图");
	imshow("高斯滤波源图", src);
	Mat dst;
	GaussianBlur(src, dst, Size(3, 3), 0, 0);
	imshow("高斯滤波效果图", dst);
	waitKey(0);
	return 0;
}