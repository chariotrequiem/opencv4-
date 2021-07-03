#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//���帨����
#define WINDOW_NAME1 "��ԭʼͼ���ڡ�"
#define WINDOW_NAME2 "��Ч��ͼ���ڡ�"
//ȫ�ֱ�����������
Mat srcImage, grayImage;
int g_Thresh = 50;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat srcImage_copy = srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point>>g_vContours;
vector<Vec4i>g_vHierarchy;
//ȫ�ֺ�������
static void ShowHelpText();
void on_ThreshChange(int, void*);

int main(int argc, char** argv)
{
	srcImage = imread("D:/images/18.jpg");
	//��ԭͼת��Ϊ�Ҷ�ͼ�����н���
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));
	//�������ڲ���ʾ
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, srcImage);
	//����������
	createTrackbar("��ֵ��", WINDOW_NAME1, &g_Thresh, g_maxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);//����һ�β����г�ʼ��
	waitKey(0);
	return 0;
}
void on_ThreshChange(int, void*)
{
	//��ͼ����ж�ֵ����������ֵ
	threshold(grayImage, g_thresholdImage_output, g_Thresh, 255, THRESH_BINARY);
	//Ѱ������
	findContours(g_thresholdImage_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//����ÿ������Ѱ����͹��
	vector<vector<Point>>hull(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		convexHull(Mat(g_vContours[i]), hull[i], false);

	}
	//������������͹��
	Mat drawing = Mat::zeros(g_thresholdImage_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}
	imshow(WINDOW_NAME2, drawing);
}