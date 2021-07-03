#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//ȫ�ֺ�������
bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();

int main(int argc, char** argv)
{
	if (ROI_AddImage()&& LinearBlending()&& ROI_LinearBlending())
	{
		cout << "���гɹ�" << endl;
	}
	waitKey(0);
	return 0;
}

//ROI_AddImage()����
//���ø���Ȥ����ROIʵ��ͼ�����
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
	namedWindow("����ROIʵ��ͼ�����ʾ������",WINDOW_NORMAL);
	imshow("����ROIʵ��ͼ�����ʾ������", srcImage1);
	return true;
}

//����addWeighted����ʵ�����Ի�Ϻ���
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
	namedWindow("ԭͼ1", WINDOW_FREERATIO);
	namedWindow("ԭͼ2", WINDOW_FREERATIO);
	namedWindow("���Ի��ͼ", WINDOW_FREERATIO);
	imshow("ԭͼ1", src1);
	imshow("ԭͼ2", src2);
	imshow("���Ի��ͼ", dst);
	return true;
}

//���Ի��ʵ�ֺ�����ָ����������ͼ����
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
	//����һ��Mat���Ͳ������趨ROI����
	Mat imageROI = src1(Rect(50, 50, src2.cols, src2.rows));
	addWeighted(imageROI, 0.5, src2, 0.5, 0., imageROI);

	namedWindow("��������ͼ����ʾ������",WINDOW_NORMAL);
	imshow("��������ͼ����ʾ������", src1);
	return true;
}
