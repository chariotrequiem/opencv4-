#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
#define WINDOW_WIDTH 600//���崰�ڴ�С
//�Զ���Ļ��ƺ�����ʵ�����ߵĻ���
void DrawLine(Mat image, Point start, Point end)
{
	int thickness = 2;
	int lineType = 8;
	line(image, start, end, Scalar(255, 255, 255), thickness, lineType);
}
//�Զ���Ļ��ƺ�����ʵ���˰�����εĻ���
void DrawPolygon(Mat image)
{
	int lineType = 8;
	//����һЩ��
	Point rookPoints[1][20];
	rookPoints[0][0] = Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][1] = Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8);
	rookPoints[0][2] = Point(3 * WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][3] = Point(11 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][4] = Point(19 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][5] = Point(3 * WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][6] = Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][7] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][8] = Point(26 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][9] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][10] = Point(22 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][11] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][12] = Point(18 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][13] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 4);
	rookPoints[0][14] = Point(14 * WINDOW_WIDTH / 40, WINDOW_WIDTH / 8);
	rookPoints[0][15] = Point(WINDOW_WIDTH / 4, WINDOW_WIDTH / 8);
	rookPoints[0][16] = Point(WINDOW_WIDTH / 4, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][17] = Point(13 * WINDOW_WIDTH / 32, 3 * WINDOW_WIDTH / 8);
	rookPoints[0][18] = Point(5 * WINDOW_WIDTH / 16, 13 * WINDOW_WIDTH / 16);
	rookPoints[0][19] = Point(WINDOW_WIDTH / 4, 13 * WINDOW_WIDTH / 16);
	const Point* ppt[1] = { rookPoints[0] };
	int npt[] = { 20 };
	fillPoly(image, ppt, npt, 1, Scalar(255, 255, 255), lineType);
}

//�Զ���Ļ��ƺ�����ʵ����ʵ��Բ�Ļ���
void DrawFilledCircle(Mat image, Point center)
{
	int thickness = -1;
	int lineType = 8;
	circle(image, center, WINDOW_WIDTH / 32, Scalar(0, 0, 255), thickness, lineType);
}

//�Զ���Ļ��ƺ�����ʵ���˻��Ʋ�ͬ�Ƕȡ���ͬ�ߴ����Բ
void DrawEllipse(Mat image, double angle)
{
	int thickness = 2;
	int lineType = 8;
	ellipse(image, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2), Size(WINDOW_WIDTH / 4, WINDOW_WIDTH / 16),
		angle, 0, 360, Scalar(255, 129, 0), thickness, lineType);
}

//������
int main(int argc, char**argv)
{
	double time0 = static_cast<double>(getTickCount());//��¼��ʼʱ��
	Mat image1 = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);
	Mat image2 = Mat::zeros(WINDOW_WIDTH, WINDOW_WIDTH, CV_8UC3);

	//ͼ1.���ƻ�ѧ�е�ԭ��ʾ��ͼ
	//1.1�Ȼ�����Բ
	DrawEllipse(image1, 90);
	DrawEllipse(image1, 0);
	DrawEllipse(image1, 45);
	DrawEllipse(image1, -45);
	//1.2����Բ��
	DrawFilledCircle(image1, Point(WINDOW_WIDTH / 2, WINDOW_WIDTH / 2));

	//ͼ2.�������ͼ
	//2.1���ƶ����
	DrawPolygon(image2);
	//2.2���ƾ���
	rectangle(image2, Point(0, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH, WINDOW_WIDTH),
		Scalar(0, 255, 255), -1, 8);
	//2.3����һЩ�߶�
	DrawLine(image2, Point(0, 15 * WINDOW_WIDTH / 16), Point(WINDOW_WIDTH, 15 * WINDOW_WIDTH / 16));
	DrawLine(image2, Point(WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 4, WINDOW_WIDTH));
	DrawLine(image2, Point(WINDOW_WIDTH / 2, 7 * WINDOW_WIDTH / 8), Point(WINDOW_WIDTH / 2, WINDOW_WIDTH));
	DrawLine(image2, Point(3 * WINDOW_WIDTH / 4, 7 * WINDOW_WIDTH / 8), Point(3 * WINDOW_WIDTH / 4, WINDOW_WIDTH));
	imshow("����ͼ1", image1);
	imshow("����ͼ2", image2);

	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "�˷�������ʱ��Ϊ" << time0 << "��" << endl;//�������ʱ��
	waitKey(0);
	return 0;
}