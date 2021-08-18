#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

int main(int *argc, char** argv)
{
	Mat img = imread("D:/images/left01.jpg");
	if (img.empty())
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);

	//������Ŀ
	Size board_size = Size(9, 6);//����궨���ڽǵ���Ŀ���У��У�
	//���ǵ�
	vector<Point2f>img_points;
	findChessboardCorners(gray, board_size, img_points);

	//ϸ���ǵ�����
	find4QuadCornerSubpix(gray, img_points, Size(5, 5));
	//���ƽǵ�����
	drawChessboardCorners(img, board_size, img_points, true);
	//��ʾ���
	imshow("���α궨��ǵ�����", img);

	waitKey(0);
	return 0;
}