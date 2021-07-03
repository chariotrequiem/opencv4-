#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
//全局变量声明
Mat srcImage, dstImage1, dstImage2;
int MedianBlurValue = 10;//中值滤波参数值
int BilateralFilterValue = 10;//双边滤波参数值

//全局函数声明
//轨迹条回调函数
static void on_MedianBlur(int, void*);
static void on_BilateralFilter(int, void*);

//主函数
int main(int argc, char** argv)
{
	//载入原图
	srcImage = imread("D:/images/6.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the srcImage" << endl;
	}

	//复制原图到Mat类中
	dstImage1 = srcImage.clone();
	dstImage2 = srcImage.clone();
	//显示原图
	imshow("原图", srcImage);

	//中值滤波
	namedWindow("中值滤波", 1);
	//创建轨迹条
	createTrackbar("内核值：", "中值滤波", &MedianBlurValue, 50, on_MedianBlur);
	on_MedianBlur(MedianBlurValue, 0);

	//双边滤波
	namedWindow("双边滤波", 1);
	createTrackbar("内核值：", "双边滤波", &BilateralFilterValue, 50, on_BilateralFilter);
	on_BilateralFilter(BilateralFilterValue, 0);

	while(char (waitKey(1))!='q'){}
	return 0;
}

static void on_MedianBlur(int, void*)
{
	medianBlur(srcImage, dstImage1, MedianBlurValue * 2 + 1);
	imshow("中值滤波", dstImage1);
}
static void on_BilateralFilter(int, void*)
{
	bilateralFilter(srcImage, dstImage2, BilateralFilterValue, BilateralFilterValue * 2, BilateralFilterValue / 2);
	imshow("双边滤波", dstImage2);
}