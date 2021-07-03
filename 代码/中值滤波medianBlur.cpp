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
	namedWindow("原图");
	namedWindow("中值滤波效果图");
	imshow("原图", src);
	Mat dst;
	medianBlur(src, dst, 7);
	imshow("中值滤波效果图", dst);

	waitKey(0);
	destroyAllWindows();
	return 0;
}