#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat srcImage = imread("D:/images/abd.jpg");
	Mat midImage, dstImage;
	//���б�Ե����ת��Ϊ�Ҷ�ͼ
	Canny(srcImage, midImage, 50, 200, 3);//����һ��Canny��Ե���
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);
	//���л������Ա任
	vector<Vec2f> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLines(midImage, lines, 1, CV_PI / 180, 250, 0, 0);

	//������ͼ�л��Ƴ�ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);

	}
	//��ʾԭʼͼ
	imshow("ԭʼͼ", srcImage);
	imshow("��Ե�����ͼ", midImage);
	imshow("Ч��ͼ", dstImage);
	waitKey(0);
	return 0;

}