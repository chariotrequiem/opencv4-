#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//全局变量声明
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3;//存储图片的Mat类型
int g_nBoxFilterValue = 3;
int g_nMeanBlurVakue = 3;
int g_mGaussianBlurValue = 3;

//全局函数声明
static void on_BoxFilter(int, void*); 
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);

int main(int argc, char**argv)
{
	//载入原图
	g_srcImage = imread("D:/images/椒盐噪声.jpg", 1);
	if (g_srcImage.empty())
	{
		cout << "could not load the picture" << endl;
	}
	//复制源图到3个Mat类中
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	//显示原图
	namedWindow("原图", 1);
	imshow("原图", g_srcImage);

	/*               方框滤波           */
	//方框滤波
	namedWindow("方框滤波", 1);
	//创建轨迹条
	createTrackbar("内核值：", "方框滤波", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	imshow("方框滤波", g_dstImage1);

	/*               均值滤波           */
	//均值滤波
	namedWindow("均值滤波", 1);
	//创建轨迹条
	createTrackbar("内核值：", "均值滤波", &g_nMeanBlurVakue, 40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurVakue, 0);
	imshow("均值滤波", g_dstImage2);

	/*               高斯滤波           */
	namedWindow("高斯滤波", 1);
	createTrackbar("内核值：", "高斯滤波", &g_mGaussianBlurValue, 40, on_GaussianBlur);
	on_GaussianBlur(g_mGaussianBlurValue, 0);
	imshow("高斯滤波", g_dstImage3);

	//waitKey(0);
	cout << endl << "\t请调整滚动条观察图像效果\n\n" << "\t按下q键时，程序退出~!\n";
	while(char(waitKey(1)!='q')){}
	return 0;
}


//方框滤波操作的回调函数
static void on_BoxFilter(int, void*)
{
	//方框滤波操作
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
	//显示窗口
	imshow("方框滤波", g_dstImage1);
}

//均值滤波操作的回调函数
static void on_MeanBlur(int, void*)
{
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurVakue + 1, g_nMeanBlurVakue + 1), Point(-1, -1));
	imshow("均值滤波", g_dstImage2);
}

//高斯滤波操作的回调函数
static void on_GaussianBlur(int, void*)
{
	GaussianBlur(g_srcImage, g_dstImage3, Size(g_mGaussianBlurValue * 2 + 1, g_mGaussianBlurValue * 2 + 1), 0, 0);
	imshow("高斯滤波", g_dstImage3);
}