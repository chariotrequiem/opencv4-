#include<opencv2/opencv.hpp>
#include<iostream>
#include<xfeatures2d.hpp>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("D:/images/leena.png");
	if (src.empty())
	{
		cout << "could load the image" << endl;
	}
	namedWindow("ԭʼͼ��", WINDOW_AUTOSIZE);
	imshow("ԭʼͼ��", src);
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dst;
	erode(src, dst, element);
	imshow("��ʴͼ��", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}