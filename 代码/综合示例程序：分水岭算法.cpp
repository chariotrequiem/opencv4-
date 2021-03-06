#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
#define WINDOW_NAME "【程序窗口1】"
//全局变量声明
Mat g_maskImage, g_srcImage;
Point prevPt(-1, -1);
//全局函数声明
static void ShowHelText();
static void on_Mouse(int event, int x, int y, int flags, void*);

int main(int argc, char** argv)
{
	//1.载入原图并显示，初始化掩膜和灰度图
	g_srcImage = imread("D:/images/31.jpg", 1);
	imshow(WINDOW_NAME, g_srcImage);
	Mat srcImage, grayImage;
	g_srcImage.copyTo(srcImage);
	cvtColor(g_srcImage, g_maskImage, COLOR_BGR2GRAY);
	cvtColor(g_maskImage, grayImage, COLOR_GRAY2BGR);
	g_maskImage = Scalar::all(0);
	//2.设置鼠标回调函数
	setMouseCallback(WINDOW_NAME, on_Mouse, 0);
	//3.轮询按键，进行处理
	while (1)
	{
		//获取键值
		int c = waitKey(0);
		//若按键值为ESC，退出
		if ((char)c == 27)
			break;
		//若按键值为2，恢复源图
		if ((char)c == '2')
		{
			g_maskImage = Scalar::all(0);
			srcImage.copyTo(g_srcImage);
			imshow("image", g_srcImage);
		}
		//若检测到按键值为1或者空格，则进行处理
		if ((char)c == '1' || (char)c == ' ')
		{
			//定义一些参数
			int i, j, compCount = 0;
			vector<vector<Point>>contours;
			vector<Vec4i>hierarchy;
			//寻找轮廓
			findContours(g_maskImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
			//轮廓为空时
			if (contours.empty())
				continue;
			//复制掩膜
			Mat maskImage(g_maskImage.size(), CV_32S);
			maskImage = Scalar::all(0);

			//循环绘制轮廓
			for (int index = 0; index >= 0; index = hierarchy[index][0], compCount++)
				drawContours(maskImage, contours, index, Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
			//compCount为0时的处理
			if (compCount == 0)
				continue;
			//生成随机颜色
			vector<Vec3b>colorTab;
			for (int i = 0; i < compCount; i++)
			{
				int b = theRNG().uniform(0, 255);
				int g = theRNG().uniform(0, 255);
				int r = theRNG().uniform(0, 255);
				colorTab.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
			}
			//计算处理时间并输出到窗口
			double dTime = (double)getTickCount();
			watershed(srcImage, maskImage);
			dTime = ((double)getTickCount() - dTime) / getTickFrequency();
			cout << "\t处理时间为" << dTime << "秒" << endl;

			//双重循环，将分水岭图像遍历存入watershedImage中
			Mat watershedImage(maskImage.size(), CV_8UC3);
			for (i = 0; i < maskImage.rows; i++)
				for (j = 0; j < maskImage.cols; j++)
				{
					int index = maskImage.at<int>(i, j);
					if (index == -1)
						watershedImage.at<Vec3b>(i, j) = Vec3b(255, 255, 255);
					else if (index <= 0 || index > compCount)
						watershedImage.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
					else
						watershedImage.at<Vec3b>(i, j) = colorTab[index - 1];
				}
			//混合灰度图和分水岭效果图并显示最后的窗口
			watershedImage = watershedImage * 0.5 + grayImage * 0.5;
			imshow("watershed transform", watershedImage);
		}
	}
	return 0;
}

static void on_Mouse(int event, int x, int y, int flags, void*)
{
	//处理鼠标不在窗口中的情况
	if (x < 0 || x >= g_srcImage.cols || y < 0 || y >= g_srcImage.rows)
		return;
	//处理鼠标左键相关信息
	if (event == EVENT_LBUTTONUP || !(flags&EVENT_FLAG_LBUTTON))
		prevPt = Point(-1, -1);
	else if (event == EVENT_LBUTTONDOWN)
		prevPt = Point(x, y);
	//鼠标左键按下并移动，绘制出白色线条
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (prevPt.x < 0)
			prevPt = pt;
		line(g_maskImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		line(g_srcImage, prevPt, pt, Scalar::all(255), 5, 8, 0);
		prevPt = pt;
		imshow(WINDOW_NAME, g_srcImage);
	}
}