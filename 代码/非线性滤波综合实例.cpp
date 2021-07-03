#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
//ȫ�ֱ�������
Mat srcImage, dstImage1, dstImage2;
int MedianBlurValue = 10;//��ֵ�˲�����ֵ
int BilateralFilterValue = 10;//˫���˲�����ֵ

//ȫ�ֺ�������
//�켣���ص�����
static void on_MedianBlur(int, void*);
static void on_BilateralFilter(int, void*);

//������
int main(int argc, char** argv)
{
	//����ԭͼ
	srcImage = imread("D:/images/6.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the srcImage" << endl;
	}

	//����ԭͼ��Mat����
	dstImage1 = srcImage.clone();
	dstImage2 = srcImage.clone();
	//��ʾԭͼ
	imshow("ԭͼ", srcImage);

	//��ֵ�˲�
	namedWindow("��ֵ�˲�", 1);
	//�����켣��
	createTrackbar("�ں�ֵ��", "��ֵ�˲�", &MedianBlurValue, 50, on_MedianBlur);
	on_MedianBlur(MedianBlurValue, 0);

	//˫���˲�
	namedWindow("˫���˲�", 1);
	createTrackbar("�ں�ֵ��", "˫���˲�", &BilateralFilterValue, 50, on_BilateralFilter);
	on_BilateralFilter(BilateralFilterValue, 0);

	while(char (waitKey(1))!='q'){}
	return 0;
}

static void on_MedianBlur(int, void*)
{
	medianBlur(srcImage, dstImage1, MedianBlurValue * 2 + 1);
	imshow("��ֵ�˲�", dstImage1);
}
static void on_BilateralFilter(int, void*)
{
	bilateralFilter(srcImage, dstImage2, BilateralFilterValue, BilateralFilterValue * 2, BilateralFilterValue / 2);
	imshow("˫���˲�", dstImage2);
}