#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char**argv)
{
	Mat src = imread("D:/images/6.jpg");
	if (src.empty())
	{
		cout << "could not load the picture!" << endl;
	}
	namedWindow("ԭͼ");
	namedWindow("��ֵ�˲�Ч��ͼ");
	imshow("ԭͼ", src);
	Mat dst;
	medianBlur(src, dst, 7);
	imshow("��ֵ�˲�Ч��ͼ", dst);

	waitKey(0);
	destroyAllWindows();
	return 0;
}