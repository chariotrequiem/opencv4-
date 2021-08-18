#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main(int *argc, char** argv)
{
	Mat img = imread("D:/images/left01.jpg");
	if (img.empty())
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//定义数目
	Size board_size = Size(9, 6);//方格标定板内角点数目（行，列）
	//检测角点
	vector<Point2f>img_points;
	findChessboardCorners(gray, board_size, img_points);

	//细化角点坐标
	find4QuadCornerSubpix(gray, img_points, Size(5, 5));
	//绘制角点检测结果
	drawChessboardCorners(img, board_size, img_points, true);
	//显示结果
	imshow("方形标定板角点检测结果", img);

	waitKey(0);
	return 0;
}