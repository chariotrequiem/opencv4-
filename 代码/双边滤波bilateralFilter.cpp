#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	Mat src = imread("D:/images/6.jpg");
	if (src.empty())
	{
		cout << "could not load the picture" << endl;
	}
	namedWindow("Ô­Í¼");
	namedWindow("Ë«±ßÂË²¨Ð§¹ûÍ¼");
	imshow("Ô­Í¼", src);
	Mat dst;
	bilateralFilter(src, dst, 25, 25 * 2, 25 / 2);
	imshow("Ë«±ßÂË²¨Ð§¹ûÍ¼", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}