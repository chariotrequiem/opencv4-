#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src, dst;
	src = imread("D:/images/13.jpg");
	if (src.empty())
	{
		cout << "could not load the src!" << endl;
		return false;
	}
	cvtColor(src, src, COLOR_BGR2GRAY);
	imshow("ԭʼͼ", src);
	equalizeHist(src, dst);
	imshow("ֱ��ͼ���⻯���", dst);
	waitKey(0);
	return 0;
}