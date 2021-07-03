#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//——————————————————————————————————————————
//              本代码为OpenCV3编程入门P132页示例程序，存在错误
//——————————————————————————————————————————
//全局函数声明
static void on_ContrastAndBright(int, void *);
//static void ShowHelpText();

//全局函数变量
int g_nContrastValue;//对比度值
int g_nBrightValue;//亮度值
Mat g_srcImage, g_dstImage;

//main（）函数
int main(int argc, char** argv)
{
	//读取输入图像
	g_srcImage = imread("D:/images/women.jpg");
	if (g_srcImage.empty())
	{
		cout << "could not load the picture!" << endl;
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	//设置对比度和亮度初值
	g_nContrastValue = 80;
	g_nBrightValue = 80;
	//创建效果图窗口
	namedWindow("效果窗口图");
	//创建轨迹条
	createTrackbar("对比度: ", "效果图窗口", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("亮  度: ", "效果图窗口", &g_nBrightValue, 200, on_ContrastAndBright);
	//进行回调函数初始化
	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);
	waitKey(0);
	return 0;
}

//on_ContrastAndBright函数
//改变图像对比度和亮度值的回调函数
static void on_ContrastAndBright(int, void *)
{
	//创建窗口
	namedWindow("原始图窗口");
	//3个for循环，执行运算g_dstImage(i,j)=a*g_srcImage(i,j)+b
	for (int y = 0; y < g_srcImage.rows; y++)
	{
		for (int x = 0; x < g_srcImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<Vec3b>(y,x)[c]=
					saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y,x)[c]) + g_nBrightValue);
			}
		}
	}
	//显示图像
	imshow("原始图窗口", g_srcImage);
	imshow("效果图窗口", g_dstImage);
}