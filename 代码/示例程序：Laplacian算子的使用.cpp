#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//0.��������
	Mat src, src_gray, dst, abs_dst;
	//1.����ԭʼͼ
	src = imread("D:/images/13.jpg");
	if (src.empty())
	{
		cout << "could not load the src!" << endl;
	}
	imshow("ԭʼͼ", src);
	//2.ʹ�ø�˹�˲���������
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	//3.ת��Ϊ�Ҷ�ͼ
	cvtColor(src, src_gray, COLOR_RGB2GRAY);
	//4.ʹ��������˹����
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	//5.�������ֵ���������תΪ8λ
	convertScaleAbs(dst, abs_dst);
	//6.��ʾЧ��ͼ
	imshow("������˹�任", abs_dst);
	waitKey(0);
	return 0;
}