#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//定义辅助宏
#define WINDOW_NAME1 "【原始图窗口】"
#define WINDOW_NAME2 "【效果图窗口】"
//全局变量声明部分
Mat srcImage, grayImage;
int g_Thresh = 50;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat srcImage_copy = srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point>>g_vContours;
vector<Vec4i>g_vHierarchy;
//全局函数声明
static void ShowHelpText();
void on_ThreshChange(int, void*);

int main(int argc, char** argv)
{
	srcImage = imread("D:/images/18.jpg");
	//将原图转化为灰度图并进行降噪
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));
	//创建窗口并显示
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, srcImage);
	//创建滚动条
	createTrackbar("阈值：", WINDOW_NAME1, &g_Thresh, g_maxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);//调用一次并进行初始化
	waitKey(0);
	return 0;
}
void on_ThreshChange(int, void*)
{
	//对图像进行二值化，控制阈值
	threshold(grayImage, g_thresholdImage_output, g_Thresh, 255, THRESH_BINARY);
	//寻找轮廓
	findContours(g_thresholdImage_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//遍历每个轮廓寻找其凸包
	vector<vector<Point>>hull(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		convexHull(Mat(g_vContours[i]), hull[i], false);

	}
	//绘制轮廓及其凸包
	Mat drawing = Mat::zeros(g_thresholdImage_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}
	imshow(WINDOW_NAME2, drawing);
}