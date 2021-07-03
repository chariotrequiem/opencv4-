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
	//创建窗口
	namedWindow("原图");
	namedWindow("膨胀操作");
	imshow("原图", src);
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dst;
	//进行膨胀操作
	dilate(src, dst, element);
	imshow("膨胀操作", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;

}