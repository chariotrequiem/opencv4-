#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	//����һ��500*500��ͼ��������ʾ������ͷ�����
	Mat img(500, 500, CV_8UC3, Scalar(255, 255, 255));
	RNG rng(10000);
	//����������ɫ
	Scalar colorLut[3] =
	{
		Scalar(0,0,255),
	    Scalar(0, 255, 0),
	    Scalar(255,0,0),
	};

	//����3���㼯������ÿ���㼯���е����Ŀ���
	int number = 3;
	int points1 = rng.uniform(20, 200);
	int points2 = rng.uniform(20, 200);
	int points3 = rng.uniform(20, 200);
	int Points_num = points1 + points2 + points3;
	Mat points(Points_num, 1, CV_32FC2);

	int i = 0;
	for (; i < points1; i++)
	{
		Point2f pts;
		pts.x = rng.uniform(100, 200);
		pts.y = rng.uniform(100, 200);
		points.at<Point2f>(i, 0) = pts;
	}

	for (; i < points1 + points2; i++)
	{
		Point2f pts;
		pts.x = rng.uniform(300, 400);
		pts.y = rng.uniform(100, 300);
		points.at<Point2f>(i, 0) = pts;
	}

	for (; i < points1 + points2 + points3; i++)
	{
		Point2f pts;
		pts.x = rng.uniform(100, 200);
		pts.y = rng.uniform(390, 490);
		points.at<Point2f>(i, 0) = pts;
	}
	//ʹ��k��ֵ
	Mat labels;//ÿ��������������
	Mat centers;//ÿ��������λ������
	kmeans(points, number, labels,TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 10, 0.1), 3, KMEANS_PP_CENTERS, centers);

	//���ݷ���Ϊÿ�������ò�ͬ����ɫ
	img = Scalar::all(255);
	for (int i = 0; i < Points_num; i++)
	{
		int index = labels.at<int>(i);
		Point point = points.at<Point2f>(i);
		circle(img, point, 2, colorLut[index], -1, 4);
	}
	//��ÿ�����������ΪԲ��������Բ
	for (int i = 0; i < centers.rows; i++)
	{
		int x = centers.at<float>(i, 0);
		int y = centers.at<float>(i, 1);
		cout << "��" << i + 1 << "�����������Ϊ: x = " << x << "  y = " << y << endl;
		circle(img, Point(x, y), 50, colorLut[i], 1, LINE_AA);
	}

	imshow("K�ٽ��㼯������", img);
	waitKey(0);
	return 0;
}