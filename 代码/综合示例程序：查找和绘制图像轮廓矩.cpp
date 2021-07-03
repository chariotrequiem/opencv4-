#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "【原始图】"
#define WINDOW_NAME2 "【图像轮廓】"
//全局变量声明
Mat srcImage, grayImage;
int g_Thresh = 100, g_MaxThresh = 255;
RNG g_rng(12345);
Mat g_CannyMat_output;
vector<vector<Point>>g_Contours;
vector<Vec4i>g_Hierarchy;

//全局函数声明
void on_ThreshChange(int, void*);
static void ShowHelpText();

int main(int argc, char** argv)
{
	ShowHelpText();
	//读入源图像，返回3通道图像数据
	srcImage = imread("D:/images/13.jpg");
	//将源图像转化为灰度图像并进行平滑
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));
	//创建新窗口
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, srcImage);
	//创建滚动条并进行初始化
	createTrackbar("阈值：", WINDOW_NAME1, &g_Thresh, g_MaxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);
	waitKey(0);
	return 0;
}
static void ShowHelpText()
{
	cout << "欢迎来到查找和绘制轮廓矩程序" << endl;
	cout << "当前OpenCV版本为" << CV_VERSION << endl;
}

void on_ThreshChange(int, void*)
{
	//使用Canny边缘检测
	Canny(grayImage, g_CannyMat_output, g_Thresh, g_Thresh * 2, 3);
	//找到轮廓
	findContours(g_CannyMat_output, g_Contours, g_Hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//计算矩
	vector<Moments>mu(g_Contours.size());
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		mu[i] = moments(g_Contours[i], false);
	}
	//计算中心矩
	vector<Point2f>mc(g_Contours.size());
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}
	//绘制轮廓
	Mat drawing = Mat::zeros(g_CannyMat_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		//Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, g_Contours, i, color, 1, 8, g_Hierarchy, 0, Point());//绘制外层和内层轮廓
		circle(drawing, mc[i], 4, color, -1, 8, 0);//绘制圆
	}
	//显示到窗口
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);

	//通过m00计算轮廓面积并且和OpenCV函数进行比较
	cout << "\t输出内容：面积和轮廓长度" << endl;
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		cout << ">通过m00计算出轮廓" << i << "的面积：(M_00) = " << mu[i].m00 << endl;
		cout << "OpenCV函数计算出的面积 = " << contourArea(g_Contours[i]) << "，长度 = " << arcLength(g_Contours[i], true) << endl;
		/*Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_Contours, i, color, 1, 8, g_Hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);*/
	}
}
