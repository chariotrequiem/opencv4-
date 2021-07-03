#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//ROI_AddImage��������
//���ø���Ȥ����ROIʵ��ͼ�����
bool ROI_AddImage()
{
	//1.����ͼ��
	Mat srcImage1 = imread("D:/images/a.jpg");
	Mat logoImage = imread("D:/images/women.png");
	if (srcImage1.empty()) 
	{
		cout << "��ȡsrcImage1ʧ��" << endl;
		return false;
	}
	if (logoImage.empty())
	{
		cout << "��ȡlogoImageʧ��" << endl;
		return false;
	}
	//2.����һ��Mat���Ͳ������趨ROI����
	Mat imageROI = srcImage1(Rect(0,0, logoImage.cols, logoImage.rows));
	//3.������Ĥ�������ǻҶ�ͼ��
	Mat mask = imread("D:/images/women.png", 0);
	//4.����Ĥ���Ƶ�ROI
	logoImage.copyTo(imageROI, mask);
	//5.��ʾ���
	namedWindow("����ROIʵ��ͼ�����ʾ������",WINDOW_FREERATIO);
	imshow("����ROIʵ��ͼ�����ʾ������", srcImage1);
	waitKey(0);
	return true;
}
int main(int argc, char** argv)
{
	ROI_AddImage();
	return 0;
}