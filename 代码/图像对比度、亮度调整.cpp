#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//������������������������������������������������������������������������������������
//              ������ΪOpenCV3�������P132ҳʾ�����򣬴��ڴ���
//������������������������������������������������������������������������������������
//ȫ�ֺ�������
static void on_ContrastAndBright(int, void *);
//static void ShowHelpText();

//ȫ�ֺ�������
int g_nContrastValue;//�Աȶ�ֵ
int g_nBrightValue;//����ֵ
Mat g_srcImage, g_dstImage;

//main��������
int main(int argc, char** argv)
{
	//��ȡ����ͼ��
	g_srcImage = imread("D:/images/women.jpg");
	if (g_srcImage.empty())
	{
		cout << "could not load the picture!" << endl;
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());
	//���öԱȶȺ����ȳ�ֵ
	g_nContrastValue = 80;
	g_nBrightValue = 80;
	//����Ч��ͼ����
	namedWindow("Ч������ͼ");
	//�����켣��
	createTrackbar("�Աȶ�: ", "Ч��ͼ����", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("��  ��: ", "Ч��ͼ����", &g_nBrightValue, 200, on_ContrastAndBright);
	//���лص�������ʼ��
	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);
	waitKey(0);
	return 0;
}

//on_ContrastAndBright����
//�ı�ͼ��ԱȶȺ�����ֵ�Ļص�����
static void on_ContrastAndBright(int, void *)
{
	//��������
	namedWindow("ԭʼͼ����");
	//3��forѭ����ִ������g_dstImage(i,j)=a*g_srcImage(i,j)+b
	for (int y = 0; y < g_srcImage.rows; y++)
	{
		for (int x = 0; x < g_srcImage.cols; x++)
		{
			for (int c = 0; c < 3; c++)
			{
				g_dstImage.at<Vec3b>(y,x)[c]=
					saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y,x)[c]) + g_nBrightValue);
			}
		}
	}
	//��ʾͼ��
	imshow("ԭʼͼ����", g_srcImage);
	imshow("Ч��ͼ����", g_dstImage);
}