#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//全局变量声明部分
Mat srcImage, midImage, dstImage;
vector<Vec4i>lines;//定义一个矢量结构用于存放得到的线段矢量集合
int g_nthreshold = 100;//接受trackBar位置参数

//全局函数声明
static void on_HoughLines(int, void*);//回调函数

int main(int argc, char** argv)
{
	srcImage = imread("D:/images/16.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src" << endl;
	}
	imshow("原始图", srcImage);
	//创建滚动条
	namedWindow("效果图", 1);
	createTrackbar("值", "效果图", &g_nthreshold, 200, on_HoughLines);
	//进行边缘检测与转化为灰度图
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);
	//调用一次回调函数，调用一次HoughLinesP函数
	on_HoughLines(g_nthreshold, 0);
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);
	imshow("效果图", dstImage);
	waitKey(0);
	return 0;
}

//回调函数
static void on_HoughLines(int, void*)
{
	//定义局部变量储存全局变量
	Mat dst = dstImage.clone();
	Mat mid = midImage.clone();
	//调用HoughLinesP函数
	vector<Vec4i>mylines;
	HoughLinesP(mid, mylines, 1, CV_PI / 180, g_nthreshold + 1, 50, 10);
	//循环遍历绘制每一条线段
	for (size_t i = 0; i < mylines.size(); i++)
	{
		Vec4i l = mylines[i];
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 1, LINE_AA);

	}
	imshow("效果图", dst);
}
