#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main()
{
	Mat img = imread("D:/images/27.jpg", IMREAD_COLOR);
	if (img.empty())
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	Mat imgGray;
	cvtColor(img, imgGray, COLOR_BGR2GRAY);
	//���ɹؼ���
	vector<KeyPoint> keypoints;
	RNG rng(10086);
	for (int i = 0; i < 100; i++)
	{
		float pty = rng.uniform(0, img.rows - 1);
		float ptx = rng.uniform(0, img.cols - 1);
		KeyPoint keypoint;//��KeyPoint����и�ֵ
		keypoint.pt.x = ptx;
		keypoint.pt.y = pty;
		keypoints.push_back(keypoint);//���浽�ؼ���������
	}
	//���ƹؼ���
	drawKeypoints(img, keypoints, img, Scalar(0, 0, 0));
	drawKeypoints(imgGray, keypoints, imgGray, Scalar(255, 255, 255));
	//��ʾͼ����ƽ��
	imshow("img", img);
	imshow("imgGray", imgGray);
	waitKey(0);
	return 0;
}