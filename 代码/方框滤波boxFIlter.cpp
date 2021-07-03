#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc,char** argv)
{
	Mat src = imread("D:/images/6.jpg");
	if (src.empty())
	{
		cout << "could not load the picture" << endl;
	}
	namedWindow("·½¿òÂË²¨Ô­Í¼");
	namedWindow("·½¿òÂË²¨Ð§¹ûÍ¼");
	imshow("·½¿òÂË²¨Ô­Í¼", src);
	Mat dst;
	boxFilter(src, dst, -1, Size(5, 5));
	imshow("·½¿òÂË²¨Ð§¹ûÍ¼", dst);

	waitKey(0);
	return 0;
}