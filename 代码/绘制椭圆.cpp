#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
#define WINDOW_WIDTH 600

//自定义的绘制函数，实现了绘制不同角度、相同尺寸的椭圆
void DrawEllipse(Mat image, double angle)
{
	int thickness = 2;
	int lineType = 8;
	ellipse(image, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle, 0, 360, Scalar(255, 129, 0), thickness, lineType);
}

int main(int argc, char** argv)
{
	//创建空白图像
	Mat image = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	DrawEllipse(image, 90);
	DrawEllipse(image, 180);
	DrawEllipse(image, 45);
	DrawEllipse(image, -45);
	imshow("绘制图1", image);
	waitKey(0);
	return 0;
}