#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	Mat src = imread("D:/images/13.jpg");
	if (src.empty())
	{
		cout << "could not load the src!" << endl;
	}
	Mat tmpImage, dstImage;
	tmpImage = src;
	imshow("原始图", src);
	//进行向下取样操作
	pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
	imshow("效果图", dstImage);
	waitKey(0);
	return 0;
}