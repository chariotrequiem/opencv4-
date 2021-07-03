#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("D:/images/4.jpg");
	if (src.empty())
	{
		cout << "could not load the picture" << endl;
	}
	//������ʱ������Ŀ��ͼ
	Mat tmpImage, dstImage1, dstImage2;
	tmpImage = src;//��ԭʼͼ������ʱ����
	imshow("ԭʼͼ", src);//��ʾԭʼͼ
	//���гߴ��������
	resize(tmpImage, dstImage1, Size(tmpImage.cols / 2, tmpImage.rows / 2), (0, 0), (0, 0), 3);
	resize(tmpImage, dstImage2, Size(tmpImage.cols * 2, tmpImage.rows * 2), (0, 0), (0, 0), 3);
	//��ʾЧ��ͼ
	imshow("Ч��ͼ1", dstImage1);
	imshow("Ч��ͼ2", dstImage2);
	waitKey(0);
	return 0;
}