#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main()
{
	//����ԭʼͼ
	Mat src = imread("D:/images/6.jpg");
	if (src.empty())
	{
		cout << "could load the src!" << endl;
	}
	//��������
	namedWindow("ԭͼ");
	namedWindow("��̬ѧ�ݶ�Ч��ͼ");
	imshow("ԭͼ", src);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dst;
	morphologyEx(src, dst, MORPH_GRADIENT, element);
	imshow("��̬ѧ�ݶ�Ч��ͼ", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}