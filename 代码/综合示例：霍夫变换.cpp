#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//ȫ�ֱ�����������
Mat srcImage, midImage, dstImage;
vector<Vec4i>lines;//����һ��ʸ���ṹ���ڴ�ŵõ����߶�ʸ������
int g_nthreshold = 100;//����trackBarλ�ò���

//ȫ�ֺ�������
static void on_HoughLines(int, void*);//�ص�����

int main(int argc, char** argv)
{
	srcImage = imread("D:/images/16.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src" << endl;
	}
	imshow("ԭʼͼ", srcImage);
	//����������
	namedWindow("Ч��ͼ", 1);
	createTrackbar("ֵ", "Ч��ͼ", &g_nthreshold, 200, on_HoughLines);
	//���б�Ե�����ת��Ϊ�Ҷ�ͼ
	Canny(srcImage, midImage, 50, 200, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);
	//����һ�λص�����������һ��HoughLinesP����
	on_HoughLines(g_nthreshold, 0);
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);
	imshow("Ч��ͼ", dstImage);
	waitKey(0);
	return 0;
}

//�ص�����
static void on_HoughLines(int, void*)
{
	//����ֲ���������ȫ�ֱ���
	Mat dst = dstImage.clone();
	Mat mid = midImage.clone();
	//����HoughLinesP����
	vector<Vec4i>mylines;
	HoughLinesP(mid, mylines, 1, CV_PI / 180, g_nthreshold + 1, 50, 10);
	//ѭ����������ÿһ���߶�
	for (size_t i = 0; i < mylines.size(); i++)
	{
		Vec4i l = mylines[i];
		line(dst, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23, 180, 55), 1, LINE_AA);

	}
	imshow("Ч��ͼ", dst);
}
