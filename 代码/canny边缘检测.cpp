#include<opencv2/opencv.hpp>
#include<iostream>

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
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}