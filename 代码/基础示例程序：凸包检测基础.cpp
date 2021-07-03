#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//��ʼ�����������ֵ
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();
	//ѭ��������ESC��Q��q�������˳��������м����±�һֱ����
	while (1)
	{
		//������ʼ��
		char key;
		int count = (unsigned)rng % 100 + 3;//������ɵ������
		vector<Point>points;//��ֵ
		//������ɵ�����
		for (int i = 0; i < count; i++)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
			points.push_back(point);
		}
		//���͹��
		vector<int>hull;
		convexHull(Mat(points), hull, true);
		//���Ƴ������ɫ�ĵ�
		image = Scalar::all(0);
		for (int i = 0; i < count; i++)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);
		//׼������
		int hullcount = (int)hull.size();//͹���ı���
		Point point0 = points[hull[hullcount -1]];//����͹���������
		//����͹���ı�
		for (int i = 0; i < hullcount; i++)
		{
			Point point = points[hull[i]];
			line(image, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
			point0 = point;
		}
		imshow("͹�����ʾ��", image);
		key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q')
			break;
	}
	return 0;
}