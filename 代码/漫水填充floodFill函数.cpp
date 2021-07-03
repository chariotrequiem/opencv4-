#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat src = imread("D:/images/4.jpg");
	if (src.empty())
	{
		cout << "could not load the src!" << endl;
	}
	imshow("ԭͼ", src);
	Rect ccomp;
	floodFill(src, Point(50, 300), Scalar(155, 55, 155), &ccomp, Scalar(20, 20, 20), Scalar(20, 20, 20));
	imshow("Ч��ͼ", src);
	waitKey(0);
	destroyAllWindows();
	return 0;
}