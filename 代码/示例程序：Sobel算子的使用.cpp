#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//0.创建grad_x核grad_y矩阵
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y, dst;
	//1.载入原始图
	Mat src = imread("D:/images/6.jpg",0);
	if (src.empty())
	{
		cout << "could not load the src!" << endl;
	}
	imshow("原始图", src);
	//2.求x方向梯度
	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	imshow("x方向Sobel", abs_grad_x);
	//3.求y方向梯度
	Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	imshow("y方向Sobel", abs_grad_y);

	//4.合并梯度（近似）
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("整体方向Sobel", dst);

	waitKey(0);
	return 0;
}