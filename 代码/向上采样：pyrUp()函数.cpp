#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	Mat src = imread("D:/images/4.jpg");
	Mat tmpImage, dstImage;
	tmpImage = src;
	if (src.empty())
	{
		cout << "could not load the src!" << endl;
	}
	imshow("ԭʼͼ", src);
	//�������ϲ�������
	pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
	//��ʾЧ��ͼ
	imshow("Ч��ͼ", dstImage);

	waitKey(0);
	return 0;
}