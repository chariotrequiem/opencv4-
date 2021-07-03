#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;
#define WINDOW_WIDTH 600

//�Զ���Ļ��ƺ�����ʵ���˻��Ʋ�ͬ�Ƕȡ���ͬ�ߴ����Բ
void DrawEllipse(Mat image, double angle)
{
	int thickness = 2;
	int lineType = 8;
	ellipse(image, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle, 0, 360, Scalar(255, 129, 0), thickness, lineType);
}

int main(int argc, char** argv)
{
	//�����հ�ͼ��
	Mat image = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	DrawEllipse(image, 90);
	DrawEllipse(image, 180);
	DrawEllipse(image, 45);
	DrawEllipse(image, -45);
	imshow("����ͼ1", image);
	waitKey(0);
	return 0;
}