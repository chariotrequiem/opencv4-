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
	normalize(hist, hist, 255, 0, type, -1, Mat());
	namedWindow(name, WINDOW_NORMAL);
	imshow(name, hist);
}
int main()
{
	Mat img = imread("D:/images/b.jpg");
	Mat sub_img = imread("D:/images/111.png");
	Mat img_HSV, sub_HSV, hist, hist2;
	if (img.empty() || sub_img.empty())
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	imshow("img", img);
	imshow("sub_img", sub_img);
	//转成HSV通道，提取S、V两个通道
	cvtColor(img, img_HSV, COLOR_BGR2HSV);
	cvtColor(sub_img, sub_HSV, COLOR_BGR2HSV);
	int h_bins = 32;
	int s_bins = 32;
	int histSize[] = { h_bins ,s_bins };
	//H通道的范围为179
	float h_ranges[] = { 0,180 };
	//S通道的范围为179
	float s_ranges[] = { 0,256 };
	const float* ranges[] = { h_ranges ,s_ranges };//每个通道的范围
	int channels[] = { 0,1 };//统计的通道索引
	//绘制H-S直方图
	calcHist(&sub_HSV, 1, channels, Mat(), hist, 2, histSize, ranges, true, false);
	drawHist(hist, NORM_INF, "hist");//直方图归一化并绘制直方图
	Mat backproj;
	calcBackProject(&img_HSV, 1, channels, hist, backproj, ranges, 1.0);
	imshow("反向投影结果", backproj);
	waitKey(0);
	return 0;
}