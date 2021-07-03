#include<opencv2/opencv.hpp>
#include<imgproc/imgproc.hpp>
#include<highgui/highgui.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat srcImage = imread("D:/images/4.jpg");
	Mat grayImage, dstImage;
	if (srcImage.empty())
	{
		cout << "could not load the src" << endl;
	}
	imshow("ԭͼ", srcImage);
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	GaussianBlur(grayImage, grayImage, Size(9, 9), 2, 2);
	//���л���Բ�任
	vector<Vec3f>circles;
	HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1.5, 10, 120, 100, 20, 100);
	
	//������ͼ�л��Ƴ�Բ
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//����Բ��
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ����
		circle(srcImage, center, radius, Scalar(155, 50, 255), 2, 8, 0);

	}
	namedWindow("Ч��ͼ", WINDOW_AUTOSIZE);
	imshow("Ч��ͼ", srcImage);
	waitKey(0);
	return 0;
}