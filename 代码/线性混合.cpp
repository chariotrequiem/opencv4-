#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
//����addWeight����ʵ��ͼ�����Ի��
int main(int argc, char** argv)
{
	Mat src1 = imread("D:/images/a.jpg");
	Mat src2 = imread("D:/images/b.jpg");
	Mat dst;
	if (src1.empty())
	{
		cout << "src1 could not load!" << endl;
	}
	if (src2.empty())
	{
		cout << "src2 could not load!" << endl;
	}
	double alphavalue = 0.5;
	double betavalue = 1 - alphavalue;
	double gamma = 0;
	addWeighted(src1, alphavalue, src2, betavalue, gamma, dst);
	namedWindow("ԭͼ1", WINDOW_FREERATIO);
	namedWindow("ԭͼ2", WINDOW_FREERATIO);
	namedWindow("���Ի��ͼ", WINDOW_FREERATIO);
	imshow("ԭͼ1", src1);
	imshow("ԭͼ2", src2);
	imshow("���Ի��ͼ", dst);
	waitKey(0);
	return 0;
}