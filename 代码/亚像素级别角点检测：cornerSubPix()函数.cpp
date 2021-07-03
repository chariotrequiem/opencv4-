#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat img = imread("D:/images/29.jpg",IMREAD_COLOR);
	if (!img.data)
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	Mat img2;
	img.copyTo(img2);
	//��ɫת��Ϊ�Ҷ�ͼ��
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//��ȡ�ǵ�
	int maxCorners = 100;//���ǵ���Ŀ
	double quality_level = 0.01;//�����ȼ���������ָ��ֵ����ѽǵ�ı�����ϵ
	double minDistance = 0.04;//�����ǵ�֮�����Сŷ�Ͼ���
	vector<Point2f>corners;
	goodFeaturesToTrack(gray, corners, maxCorners, quality_level, minDistance, Mat(), 3, false);
	//���������ؼ���ǵ�����
	vector<Point2f>cornersSub = corners;//�ǵ㱸�ݣ���ֹ�������޸�
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 40, 0.001);
	cornerSubPix(gray, cornersSub, winSize, zeroZone, criteria);
	//�����ʼ�����뾫ϸ����
	for (size_t i = 0; i < corners.size(); i++)
	{
		string str = to_string(i);
		str = "��" + str + "���ǵ��ʼ���꣺";
		cout << str << corners[i] << "  ��ϸ�����꣺" << cornersSub[i] << endl;
	}

	//��ʼ�ǵ�����KeyPoint����
	vector<KeyPoint>KeyPoints;
	for (int i = 0; i < corners.size(); i++)
	{
		KeyPoint KeyPoint;
		KeyPoint.pt = corners[i];
		KeyPoints.push_back(KeyPoint);
	}
	//�������ؼ���ǵ����KeyPoint����
	vector<KeyPoint>KeyPoints2;
	for (int i = 0; i < cornersSub.size(); i++)
	{
		KeyPoint KeyPoint;
		KeyPoint.pt = cornersSub[i];
		KeyPoints2.push_back(KeyPoint);
	}
	drawKeypoints(img, KeyPoints, img);
	drawKeypoints(img2, KeyPoints2, img2);
	imshow("��ʼ�ǵ�", img);
	imshow("�����ؽǵ�", img2);
	waitKey(0);
	return 0;
}