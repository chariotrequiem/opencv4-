#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	//载入原始图，且必须以二值图模式载入
	Mat srcImage = imread("D:/images/4.jpg", 0);
	imshow("原始图", srcImage);

	//初始化结果图
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	//srcImage取大于阈值119的那部分
	srcImage = srcImage > 119;
	imshow("取阈值偶的原始图", srcImage);
	//定义轮廓共和层次结构
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	//查找轮廓
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	//遍历所有顶层轮廓，以随机颜色绘制出每个连接组件颜色
	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(155, 50, 180);
		drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
	}
	imshow("轮廓图", dstImage);
	waitKey(0);
	return 0;
}