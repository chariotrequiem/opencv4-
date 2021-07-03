#include<opencv2/opencv.hpp>
#include<imgproc/imgproc.hpp>
#include<highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat srcImage = imread("D:/images/16.jpg");
	Mat midImage, dstImage;
	//���б�Ե��Ⲣת��Ϊ�Ҷ�ͼ
	Canny(srcImage, midImage, 50, 250, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);
	//���л����߱任
	vector<Vec4i>lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);
	//������;�л��Ƴ�ÿ���߶�
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);
	}
	//��ʾͼ��
	imshow("ԭʼͼ", srcImage);
	imshow("��Ե�����ͼ", midImage);
	imshow("Ч��ͼ", dstImage);
	waitKey(0);
	return 0;
}