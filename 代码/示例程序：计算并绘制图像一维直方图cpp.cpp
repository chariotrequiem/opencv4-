#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//1.载入原图并显示
	Mat src = imread("D:/images/13.jpg");
	imshow("源图", src);
	if (src.empty())
	{
		cout << "could not load the src!" << endl;
		return false;
	}
	//2.定义变量
	MatND dstHist;
	int dims = 1;
	float hranges[] = { 0,255 };
	const float *ranges[] = { hranges };
	int size = 256;
	int channels = 0;
	//3.计算图像直方图
	calcHist(&src, 1, &channels, Mat(), dstHist, dims, &size, ranges);
	int scale = 1;
	Mat dstImage(size* scale, size, CV_8U, Scalar(0));
	//4.获取最大值与最小值
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);
	//5.绘制出直方图
	int hpt = saturate_cast<int>(0.9*size);
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);
		int realValue = saturate_cast<int>(binValue*hpt / maxValue);
		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
	}
	imshow("一维直方图", dstImage);
	waitKey(0);
	return 0;
}