#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
#define WINDOW_WIDTH 600//定义窗口大小
//自定义的绘制函数，实现了线的绘制
void DrawLine(Mat image, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(image, start, end, Scalar(255, 255, 255), thickness, lineType);
}
//自定义的绘制函数，实现了凹多边形的绘制
void DrawPolygon(Mat image)
{
	int lineType = 8;
	//创建一些点
	Point rookPoints[1][20];
	rookPoints[0][0] = Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][1] = Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][2] = Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][3] = Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][4] = Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][5] = Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][6] = Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][7] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][8] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][9] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][10] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][11] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][12] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][13] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][14] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][15] = Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][16] = Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][17] = Point(13 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][18] = Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][19] = Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };
	fillPoly(image, ppt, npt, 1, Scalar(255, 255, 255), lineType);
}

//自定义的绘制函数，实现了实心圆的绘制
void DrawFilledCircle(Mat image, Point center)
{
	int thickness = -1;
	int lineType = 8;
	circle(image, center, WINDOW_WIDTH / 32, Scalar(0, 0, 255), thickness, lineType);
}

//自定义的绘制函数，实现了绘制不同角度、相同尺寸的椭圆
void DrawEllipse(Mat image, double angle)
{
	int thickness = 2;
	int lineType = 8;
	ellipse(image, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle, 0, 360, Scalar(255, 129, 0), thickness, lineType);
}

//主函数
int main(int argc, char**argv)
{
	double time0 = static_cast<double>(getTickCount());//记录起始时间
	Mat image1 = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat image2 = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	//图1.绘制化学中的原子示例图
	//1.1先绘制椭圆
	DrawEllipse(image1, 90);
	DrawEllipse(image1, 0);
	DrawEllipse(image1, 45);
	DrawEllipse(image1, -45);
	//1.2绘制圆心
	DrawFilledCircle(image1, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	//图2.绘制组合图
	//2.1绘制多边形
	DrawPolygon(image2);
	//2.2绘制矩形
	rectangle(image2, Point(0, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255), -1, 8);
	//2.3绘制一些线段
	DrawLine(image2, Point(0, 15 * WINDOW_WIDTH / 16), Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	DrawLine(image2, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	DrawLine(image2, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 2, WINDOW_WIDTH));
	DrawLine(image2, Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));
	imshow("绘制图1", image1);
	imshow("绘制图2", image2);

	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为" << time0 << "秒" << endl;//输出运行时间
	waitKey(0);
	return 0;
}