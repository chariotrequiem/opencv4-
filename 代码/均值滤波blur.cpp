#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("D:/images/6.jpg");
	if (src.empty())
	{
		cout << "could not load the image" << endl;
	}
	namedWindow("��ֵ�˲�Դͼ");
	namedWindow("��ֵ�˲�Ч��ͼ");
	Mat dst;
	blur(src, dst, Size(5, 5));
	imshow("��ֵ�˲�Դͼ", src);
	imshow("��ֵ�˲�Ч��ͼ", dst);
	waitKey(0);
	return 0;
}