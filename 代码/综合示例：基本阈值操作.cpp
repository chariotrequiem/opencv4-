#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//���帨����
#define  WINDOW_NAME "���򴰿�"
//����ȫ�ֱ���
int ThresholdValue = 100;
int ThresholdType = 3;
Mat srcImage, grayImage, dstImage;
//ȫ�ֺ�������
static void ShowHelpText();//�����������
void on_Threshold(int, void*);//�ص�����

//������
int main(int argc, char** argv)
{
	ShowHelpText();
	srcImage = imread("D:/images/13.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	//����һ��ԭͼ�ĻҶ�ͼ
	cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	//������������������ֵ
	createTrackbar("ģʽ", WINDOW_NAME, &ThresholdType, 4, on_Threshold);
	createTrackbar("����ֵ", WINDOW_NAME, &ThresholdValue, 255, on_Threshold);

	//��ʼ���Զ������ֵ�ص�����
	on_Threshold(0, 0);
	//��ѯ�ȴ��û����������ESC�������˳�����
	while (1)
	{
		int key;
		key = waitKey(20);
		if ((char)key == 27) { break; }
	}
	return 0;
}

void on_Threshold(int, void*)
{
	//������ֵ����
	threshold(grayImage, dstImage, ThresholdValue, 255, ThresholdType);
	//����Ч��ͼ
	imshow(WINDOW_NAME, dstImage);
}

static void ShowHelpText()
{
	cout << "\t��������˵��" << endl;
	cout << "\t\t���̰���ESC �� �˳�����" << endl;
	cout << "\t\t������ģʽ0 �� ��������ֵ" << endl;
	cout << "\t\t������ģʽ1 �� ����������ֵ" << endl;
	cout << "\t\t������ģʽ2 �� �ض���ֵ" << endl;
	cout << "\t\t������ģʽ3 �� ����ֵ��Ϊ0" << endl;
	cout << "\t\t������ģʽ4 �� ��ֵ��Ϊ0" << endl;
}