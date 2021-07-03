#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	//����ԭʼͼ���ұ����Զ�ֵͼģʽ����
	Mat srcImage = imread("D:/images/4.jpg", 0);
	imshow("ԭʼͼ", srcImage);

	//��ʼ�����ͼ
	Mat dstImage = Mat::zeros(srcImage.rows, srcImage.cols, CV_8UC3);
	//srcImageȡ������ֵ119���ǲ���
	srcImage = srcImage > 119;
	imshow("ȡ��ֵż��ԭʼͼ", srcImage);
	//�����������Ͳ�νṹ
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;
	//��������
	findContours(srcImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	//�������ж����������������ɫ���Ƴ�ÿ�����������ɫ
	int index = 0;
	for (; index >= 0; index = hierarchy[index][0])
	{
		Scalar color(155, 50, 180);
		drawContours(dstImage, contours, index, color, FILLED, 8, hierarchy);
	}
	imshow("����ͼ", dstImage);
	waitKey(0);
	return 0;
}