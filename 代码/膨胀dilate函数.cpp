#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("D:/images/6.jpg");
	if (src.empty())
	{
		cout << "could not load the src" << endl;
	}
	//��������
	namedWindow("ԭͼ");
	namedWindow("���Ͳ���");
	imshow("ԭͼ", src);
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dst;
	//�������Ͳ���
	dilate(src, dst, element);
	imshow("���Ͳ���", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;

}