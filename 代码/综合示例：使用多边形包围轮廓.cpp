#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;
#define WINDOW_NAME1 "【原始图窗口】"
#define WINDOW_NAME2 "【效果图窗口】"
//全局变量声明
Mat srcImage, grayImage;
int g_Thresh = 50, g_MaxThresh = 255;
RNG g_rng(12345);
//全局函数声明
void on_ContoursChange(int, void*);
static void ShowHelpText();
int main(int argc, char** argv)
{
	srcImage = imread("D:/images/20.jpg", 1);
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
		return false;
	}
	//得到原图的灰度图像并进行平滑
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, srcImage);
	//设置滚动条并调用一次回调函数
	createTrackbar("阈值：", WINDOW_NAME1, &g_Thresh, g_MaxThresh, on_ContoursChange);
	on_ContoursChange(0, 0);
	waitKey(0);
	return 0;
}
void on_ContoursChange(int, void*)
{
	//定义一些参数
	Mat threshold_output;
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	//使用Threshold检测边缘
	threshold(grayImage, threshold_output, g_Thresh, 255, THRESH_BINARY);
	//找出轮廓
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//多边形逼近轮廓+获取矩形和圆形边界框
	vector<vector<Point>>contours_poly(contours.size());
	vector<Rect>boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());
	//一个循环，遍历所有部分，进行本程序核心部分
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);//用指定精度逼近多边形曲线
		boundRect[i] = boundingRect(Mat(contours_poly[i]));//计算点集的最外面矩形边界
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);//对给定的2D点集，寻找最小面积的包围圆形
	}
	//绘制多边形轮廓+包围的矩形框+圆形框
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int unsigned i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());//绘制轮廓
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);
}