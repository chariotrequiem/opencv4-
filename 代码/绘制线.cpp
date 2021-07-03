#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
#define WINDOW_WIDTH 600
//自定义的绘制函数，实现了线的绘制
void DrawLine(Mat image, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(image, start, end, Scalar(255, 255, 255), thickness, lineType);
}
int main(int argc, char**argv)
{
	Mat image = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	DrawLine(image, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	imshow("绘制图", image);
	waitKey(0);
	return 0;
}