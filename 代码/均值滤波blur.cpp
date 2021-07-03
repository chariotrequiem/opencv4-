#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("D:/images/6.jpg");
	if (src.empty())
	{
		cout << "could not load the image" << endl;
	}
	namedWindow("均值滤波源图");
	namedWindow("均值滤波效果图");
	Mat dst;
	blur(src, dst, Size(5, 5));
	imshow("均值滤波源图", src);
	imshow("均值滤波效果图", dst);
	waitKey(0);
	return 0;
}