#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//归一化并绘制直方图函数
void drawHist(Mat& hist, int type, string name)
{
	int hist_w = 512;
	int hist_h = 400;
	int width = 2;
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	normalize(hist, hist, 1, 0, type, -1, Mat());
	for (int i = 1; i <= hist.rows; i++)
	{
		//rectangle(histImage, Point(width*(i - 1), hist_h - 1), Point(width*i - 1, hist_h - cvRound(hist_h*hist.at<float>(i - 1)) - 1), Scalar(255, 255, 255), -1);
		rectangle(histImage, Point(width*(i - 1), hist_h - 1), Point(width*i -1, hist_h - cvRound(hist_h*hist.at<float>(i - 1)) - 1), Scalar(255, 255, 255), -1);
	}
	imshow(name, histImage);
}
int main()
{
	Mat img = imread("D:/images/13.jpg");
	if (img.empty())
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	Mat gray, hist, gray2, hist2, gray3, hist3;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	resize(gray, gray2, Size(), 0.5, 0.5);
	gray3 = imread("D:/images/17.jpg", IMREAD_GRAYSCALE);
	const int channels[1] = { 0 };//通道索引
	float inRanges[2] = { 0,255 };
	const float* ranges[1] = { inRanges };//像素灰度值范围
	const int bins[1] = { 256 };//直方图的维度，就是像素灰度值的最大值
	calcHist(&gray, 1, channels, Mat(), hist, 1, bins, ranges);
	calcHist(&gray2, 1, channels, Mat(), hist2, 1, bins, ranges);
	calcHist(&gray3, 1, channels, Mat(), hist3, 1, bins, ranges);
	drawHist(hist, NORM_INF, "hist");
	drawHist(hist2, NORM_INF, "hist2");
	drawHist(hist3, NORM_INF, "hist3");
	//原图直方图与原图直方图的相关系数
	double hist_hist = compareHist(hist, hist, HISTCMP_CORREL);
	cout << "原图直方图与原图直方图的相关系数：" << hist_hist << endl;
	//原图与缩小原图后的直方图相关系数
	double hist_hist2 = compareHist(hist, hist2, HISTCMP_CORREL);
	cout << "原图与缩小原图后的直方图相关系数：" << hist_hist2 << endl;
	//两幅不同图像直方图相关系数
	double hist_hist3 = compareHist(hist, hist3, HISTCMP_CORREL);
	cout << "两幅不同图像直方图相关系数：" << hist_hist3 << endl;
	waitKey(0);
	return 0;
}