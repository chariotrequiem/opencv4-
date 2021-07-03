#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//全局函数声明
bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();

int main(int argc, char** argv)
{
	if (ROI_AddImage()&& LinearBlending()&& ROI_LinearBlending())
	{
		cout << "运行成功" << endl;
	}
	waitKey(0);
	return 0;
}

//ROI_AddImage()函数
//利用感兴趣区域ROI实现图像叠加
bool ROI_AddImage()
{
	Mat srcImage1 = imread("D:/images/a.jpg");
	Mat srcImage2 = imread("D:/images/women.png");
	if (srcImage1.empty())
	{
		cout << "srcImage1 could not load!" << endl;
	}
	if (srcImage2.empty())
	{
		cout << "srcImage2 could not load!" << endl;
	}
	Mat imageROI = srcImage1(Rect(50, 50, srcImage2.cols, srcImage2.rows));
	Mat mask = imread("D:/images/women.png", 0);
	srcImage2.copyTo(imageROI, mask);
	namedWindow("利用ROI实现图像叠加示例窗口",WINDOW_NORMAL);
	imshow("利用ROI实现图像叠加示例窗口", srcImage1);
	return true;
}

//运用addWeighted函数实现线性混合函数
bool LinearBlending()
{
	Mat src1 = imread("D:/images/a.jpg");
	Mat src2 = imread("D:/images/b.jpg");
	Mat dst;
	if (src1.empty())
	{
		cout << "src1 could not load!" << endl;
	}
	if (src2.empty())
	{
		cout << "src2 could not load!" << endl;
	}
	double alphavalue = 0.5;
	double betavalue = 1 - alphavalue;
	double gamma = 0;
	addWeighted(src1, alphavalue, src2, betavalue, gamma, dst);
	namedWindow("原图1", WINDOW_FREERATIO);
	namedWindow("原图2", WINDOW_FREERATIO);
	namedWindow("线性混合图", WINDOW_FREERATIO);
	imshow("原图1", src1);
	imshow("原图2", src2);
	imshow("线性混合图", dst);
	return true;
}

//线性混合实现函数，指定区域线性图像混合
bool ROI_LinearBlending()
{
	Mat src1 = imread("D:/images/a.jpg");
	Mat src2 = imread("D:/images/women.png");
	if (src1.empty())
	{
		cout << "src1 could not load" << endl;
	}
	if (src2.empty())
	{
		cout << "src2 could not load" << endl;
	}
	//定义一个Mat类型并给其设定ROI区域
	Mat imageROI = src1(Rect(50, 50, src2.cols, src2.rows));
	addWeighted(imageROI, 0.5, src2, 0.5, 0., imageROI);

	namedWindow("区域线型图象混合示例窗口",WINDOW_NORMAL);
	imshow("区域线型图象混合示例窗口", src1);
	return true;
}
