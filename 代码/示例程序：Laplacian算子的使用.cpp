#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//0.变量定义
	Mat src, src_gray, dst, abs_dst;
	//1.载入原始图
	src = imread("D:/images/13.jpg");
	if (src.empty())
	{
		cout << "could not load the src!" << endl;
	}
	imshow("原始图", src);
	//2.使用高斯滤波消除噪声
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//3.转化为灰度图
	cvtColor(src, src_gray, COLOR_RGB2GRAY);
	//4.使用拉普拉斯函数
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	//5.计算绝对值，并将结果转为8位
	convertScaleAbs(dst, abs_dst);
	//6.显示效果图
	imshow("拉普拉斯变换", abs_dst);
	waitKey(0);
	return 0;
}