#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//定义宏部分
#define WINDOW_NAME1 "【原始图窗口】"
#define WINDOW_NAME2 "【轮廓图】"
//全局变量声明
Mat srcImage, grayImage;
int Thresh = 80, Thresh_max = 255;
RNG g_rng(12345);
Mat cannyMat_output;
vector<vector<Point>>g_vContours;
vector<Vec4i>g_vHierarchy;
//全局函数声明
static void ShowHelpText();
void on_ThreshChange(int, void*);

int main(int argc, char** argv)
{
	ShowHelpText();
	srcImage = imread("D:/images/17.jpeg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	//转化为灰度并模糊化降噪
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	//创建窗口
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, srcImage);
	//创建滚动条并初始化
	createTrackbar("canny阈值", WINDOW_NAME1, &Thresh, Thresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);
	waitKey(0);
	return 0;
}

//回调函数
void on_ThreshChange(int, void*)
{
	//用canny算子检测边缘
	Canny(grayImage, cannyMat_output, Thresh, Thresh * 2, 3);
	//寻找轮廓
	findContours(cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//绘出轮廓
	Mat drawing = Mat::zeros(cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_vContours.size(); i++)
	{
		//Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//任意值
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, g_vContours, i, color, 1, 8, g_vHierarchy, 0, Point());
	}
	//显示效果图
	imshow(WINDOW_NAME2, drawing);
}

static void ShowHelpText()
{
	cout << "当前使用OpenCV版本为" << CV_VERSION << endl;
	cout << "\t【在图形中寻找轮廓】示例程序" << endl;
	cout << "\t按键操作说明" << endl;
	cout << "\t\t键盘按键任意键 - 退出程序" << endl;
	cout << "\t\t滑动滚动条" << endl;
}