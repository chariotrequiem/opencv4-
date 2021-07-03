#include<opencv2/opencv.hpp>
#include<iostream>
#include<xfeatures2d.hpp>
using namespace std;
using namespace cv;
using namespace xfeatures2d;

int main(int argc, char** argv)
{
	Mat src1 = imread("D:/images/book1.jpg", 1);
	Mat src2 = imread("D:/images/book2.jpg", 1);
	if (!src1.data || !src2.data)
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	imshow("原始图1", src1);
	imshow("原始图2", src2);
	//定义需要用到的变量和类
	int minHessian = 400;//定义SURF中的hessian阈值特征点检测算子
	waitKey(0);
	return  0;
}