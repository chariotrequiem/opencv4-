#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("D:/images/4.jpg");
	if (src.empty())
	{
		cout << "could not load the picture" << endl;
	}
	//定义临时变量和目标图
	Mat tmpImage, dstImage1, dstImage2;
	tmpImage = src;//将原始图赋给临时变量
	imshow("原始图", src);//显示原始图
	//进行尺寸调整操作
	resize(tmpImage, dstImage1, Size(tmpImage.cols / 2, tmpImage.rows / 2), (0, 0), (0, 0), 3);
	resize(tmpImage, dstImage2, Size(tmpImage.cols * 2, tmpImage.rows * 2), (0, 0), (0, 0), 3);
	//显示效果图
	imshow("效果图1", dstImage1);
	imshow("效果图2", dstImage2);
	waitKey(0);
	return 0;
}