#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//ȫ�ֱ�������
Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3;//�洢ͼƬ��Mat����
int g_nBoxFilterValue = 3;
int g_nMeanBlurVakue = 3;
int g_mGaussianBlurValue = 3;

//ȫ�ֺ�������
static void on_BoxFilter(int, void*); 
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);

int main(int argc, char**argv)
{
	//����ԭͼ
	g_srcImage = imread("D:/images/��������.jpg", 1);
	if (g_srcImage.empty())
	{
		cout << "could not load the picture" << endl;
	}
	//����Դͼ��3��Mat����
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();
	//��ʾԭͼ
	namedWindow("ԭͼ", 1);
	imshow("ԭͼ", g_srcImage);

	/*               �����˲�           */
	//�����˲�
	namedWindow("�����˲�", 1);
	//�����켣��
	createTrackbar("�ں�ֵ��", "�����˲�", &g_nBoxFilterValue, 40, on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue, 0);
	imshow("�����˲�", g_dstImage1);

	/*               ��ֵ�˲�           */
	//��ֵ�˲�
	namedWindow("��ֵ�˲�", 1);
	//�����켣��
	createTrackbar("�ں�ֵ��", "��ֵ�˲�", &g_nMeanBlurVakue, 40, on_MeanBlur);
	on_MeanBlur(g_nMeanBlurVakue, 0);
	imshow("��ֵ�˲�", g_dstImage2);

	/*               ��˹�˲�           */
	namedWindow("��˹�˲�", 1);
	createTrackbar("�ں�ֵ��", "��˹�˲�", &g_mGaussianBlurValue, 40, on_GaussianBlur);
	on_GaussianBlur(g_mGaussianBlurValue, 0);
	imshow("��˹�˲�", g_dstImage3);

	//waitKey(0);
	cout << endl << "\t������������۲�ͼ��Ч��\n\n" << "\t����q��ʱ�������˳�~!\n";
	while(char(waitKey(1)!='q')){}
	return 0;
}


//�����˲������Ļص�����
static void on_BoxFilter(int, void*)
{
	//�����˲�����
	boxFilter(g_srcImage, g_dstImage1, -1, Size(g_nBoxFilterValue + 1, g_nBoxFilterValue + 1));
	//��ʾ����
	imshow("�����˲�", g_dstImage1);
}

//��ֵ�˲������Ļص�����
static void on_MeanBlur(int, void*)
{
	blur(g_srcImage, g_dstImage2, Size(g_nMeanBlurVakue + 1, g_nMeanBlurVakue + 1), Point(-1, -1));
	imshow("��ֵ�˲�", g_dstImage2);
}

//��˹�˲������Ļص�����
static void on_GaussianBlur(int, void*)
{
	GaussianBlur(g_srcImage, g_dstImage3, Size(g_mGaussianBlurValue * 2 + 1, g_mGaussianBlurValue * 2 + 1), 0, 0);
	imshow("��˹�˲�", g_dstImage3);
}