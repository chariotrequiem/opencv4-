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
	namedWindow("原始图像", WINDOW_AUTOSIZE);
	imshow("原始图像", src);
	
	waitKey(0);
	destroyAllWindows();
	return 0;
}