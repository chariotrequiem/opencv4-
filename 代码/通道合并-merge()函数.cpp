#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char**argv)
{
	vector<Mat> channels;
	Mat imageBlueChannel;
	Mat imageGreenChannel;
	Mat imageRedChannel;
	Mat src = imread("D:/images/leena.png");
	Mat dst;
	split(src, channels);
	imageBlueChannel = channels.at(0);
	imageGreenChannel = channels.at(1);
	imageRedChannel = channels.at(2);
	merge(channels, dst);
	imshow("ԭͼ", src);
	imshow("��ɫͨ��", imageBlueChannel);
	imshow("��ɫͨ��", imageGreenChannel);
	imshow("��ɫͨ��", imageRedChannel);
	imshow("�ϲ�ͼ", dst);
	waitKey(0);
	return 0;
}