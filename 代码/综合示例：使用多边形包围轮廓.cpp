#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;
#define WINDOW_NAME1 "��ԭʼͼ���ڡ�"
#define WINDOW_NAME2 "��Ч��ͼ���ڡ�"
//ȫ�ֱ�������
Mat srcImage, grayImage;
int g_Thresh = 50, g_MaxThresh = 255;
RNG g_rng(12345);
//ȫ�ֺ�������
void on_ContoursChange(int, void*);
static void ShowHelpText();
int main(int argc, char** argv)
{
	srcImage = imread("D:/images/20.jpg", 1);
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
		return false;
	}
	//�õ�ԭͼ�ĻҶ�ͼ�񲢽���ƽ��
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, srcImage);
	//���ù�����������һ�λص�����
	createTrackbar("��ֵ��", WINDOW_NAME1, &g_Thresh, g_MaxThresh, on_ContoursChange);
	on_ContoursChange(0, 0);
	waitKey(0);
	return 0;
}
void on_ContoursChange(int, void*)
{
	//����һЩ����
	Mat threshold_output;
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	//ʹ��Threshold����Ե
	threshold(grayImage, threshold_output, g_Thresh, 255, THRESH_BINARY);
	//�ҳ�����
	findContours(threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//����αƽ�����+��ȡ���κ�Բ�α߽��
	vector<vector<Point>>contours_poly(contours.size());
	vector<Rect>boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());
	//һ��ѭ�����������в��֣����б�������Ĳ���
	for (unsigned int i = 0; i < contours.size(); i++)
	{
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);//��ָ�����ȱƽ����������
		boundRect[i] = boundingRect(Mat(contours_poly[i]));//����㼯����������α߽�
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);//�Ը�����2D�㼯��Ѱ����С����İ�ΧԲ��
	}
	//���ƶ��������+��Χ�ľ��ο�+Բ�ο�
	Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
	for (int unsigned i = 0; i < contours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, contours_poly, i, color, 1, 8, vector<Vec4i>(), 0, Point());//��������
		rectangle(drawing, boundRect[i].tl(), boundRect[i].br(), color, 2, 8, 0);
		circle(drawing, center[i], (int)radius[i], color, 2, 8, 0);
	}
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);
}