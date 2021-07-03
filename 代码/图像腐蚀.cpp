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
	namedWindow("Ô­Ê¼Í¼Ïñ", WINDOW_AUTOSIZE);
	imshow("Ô­Ê¼Í¼Ïñ", src);
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat dst;
	erode(src, dst, element);
	imshow("¸¯Ê´Í¼Ïñ", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}