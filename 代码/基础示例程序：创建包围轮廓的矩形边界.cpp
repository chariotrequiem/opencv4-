#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc,char** argv)
{
	Mat image(800, 800, CV_8UC3);
	RNG& rng = theRNG();
	while (1)
	{
		//������ʼ��
		int count = rng.uniform(3, 103);//������ɵ������
		vector<Point>points;//��ֵ

		//������ɵ�����
		for (int i = 0; i < count; i++)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
			points.push_back(point);
		}
		//�Ը����Ķ�ά�㼯��Ѱ����С����İ�Χ����
		RotatedRect box = minAreaRect(Mat(points));
		Point2f vertex[4];
		box.points(vertex);
		//���Ƴ������ɫ�ĵ�
		image = Scalar::all(0);
		for (int i = 0; i < count; i++)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);
		//���Ƴ���С����İ�Χ���Ρ�
		for (int i = 0; i < 4; i++)
			line(image, vertex[i], vertex[(i + 1) % 4], Scalar(100, 200, 211), 2, LINE_AA);
		imshow("���ΰ�Χʾ��", image);
		char key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q')
			break;
	}
	return 0;
}