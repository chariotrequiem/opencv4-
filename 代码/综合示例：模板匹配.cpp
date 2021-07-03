#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "��ԭʼ���ڡ�"
#define WINDOW_NAME2 "��Ч�����ڡ�"
//ȫ�ֱ�������
Mat g_srcImage, g_templateImage, g_resultImage;
int g_nMatchMethod;
int g_nMaxTrackbarNum = 5;
//ȫ�ֺ�������
void on_Matching(int, void*);
int main()
{
	//1.����Դͼ���ģ���
	g_srcImage = imread("D:/images/6.jpg", 1);
	g_templateImage = imread("D:/images/face.png", 1);
	//2.��������
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	//3.����������������һ�γ�ʼ��
	createTrackbar("����", WINDOW_NAME1, &g_nMatchMethod, g_nMaxTrackbarNum, on_Matching);
	on_Matching(0, 0);
	waitKey(0);
	return 0;
}

void on_Matching(int, void*)
{
	//1.���ֲ�������ʼ��
	Mat srcImage;
	g_srcImage.copyTo(srcImage);
	//2.��ʼ�����ڽ������ľ���
	int resultImage_cols = g_srcImage.cols - g_templateImage.cols + 1;
	int resultImage_rows = g_srcImage.rows - g_templateImage.rows + 1;
	g_resultImage.create(resultImage_cols, resultImage_rows, CV_32FC1);
	//3.����ƥ�����׼��
	matchTemplate(g_srcImage, g_templateImage, g_resultImage, g_nMatchMethod);
	normalize(g_resultImage, g_resultImage, 0, 1, NORM_MINMAX, -1, Mat());
	//4.ͨ������minMaxLoc��λ��ƥ���λ��
	double minValue, maxValue;
	Point minLocation, maxLocation, matchLocation;
	minMaxLoc(g_resultImage, &minValue, &maxValue, &minLocation, &maxLocation, Mat());
	//5.���ڷ���SQDIFF �� SQDIFF_NORMED��ԽС����ֵ���Ÿ��ߵ�ƥ������������ķ�������ֵԽ��ƥ��Ч��Խ��
	if (g_nMatchMethod == TM_SQDIFF || g_nMatchMethod == TM_SQDIFF_NORMED)
	{
		matchLocation = minLocation;
	}
	else
	{
		matchLocation = maxLocation;
	}
	//6.���ƾ��Σ�����ʾ���ս��
	rectangle(srcImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);
	rectangle(g_resultImage, matchLocation, Point(matchLocation.x + g_templateImage.cols, matchLocation.y + g_templateImage.rows), Scalar(0, 0, 255), 2, 8, 0);
	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, g_resultImage);

}