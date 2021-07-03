#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;

	Mat src = imread("D:/images/13.jpg",0);
	if (src.empty())
	{
		cout << "could not load the src!" << endl;
	}
	imshow("原始图", src);
	Scharr(src, grad_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("x方向Scharr", abs_grad_x);

	Scharr(src, grad_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("y方向Scharr", abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("合并梯度后效果图Scharr", dst);
	waitKey(0);
	return 0;
}