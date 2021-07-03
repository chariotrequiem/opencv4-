#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc,char**argv)
{
	Mat srcImage;
	Mat imageROI;
	vector<Mat> channels;
	srcImage = imread("D:/images/b.jpg");
	Mat logoImage = imread("D:/images/women.jpg",0);//�ԻҶ�ͼ��򿪣���ͨ����
	//��һ��3ͨ��ͼ��ת����3����ͨ��ͼ��
	split(srcImage, channels);//�����ɫͨ��
	imageROI = channels.at(0);
	addWeighted(imageROI(Rect(50, 50, logoImage.cols, logoImage.rows)), 0.5,logoImage, 0.5, 0., imageROI(Rect(0, 0, logoImage.cols, logoImage.rows)));
	namedWindow("sample", WINDOW_NORMAL);
	imshow("sample", imageROI);
	waitKey(0);
	return 0;
}