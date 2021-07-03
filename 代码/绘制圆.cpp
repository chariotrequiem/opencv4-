#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
#define WINDOW_WIDTH 600

//自定义的绘制函数，实现了实心圆的绘制
void DrawFilledCircle(Mat image, Point center)
{
	int thickness = -1;
	int lineType = 8;
	circle(image, center, WINDOW_WIDTH / 32, Scalar(0, 0, 255), thickness, lineType);
}
int main(int argc, char**argv)
{
	Mat image = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	DrawFilledCircle(image, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));
	imshow("绘制图", image);
	waitKey(0);
	return 0;
}