#include<opencv2/opencv.hpp>
#include<imgproc/imgproc.hpp>
#include<highgui/highgui.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat srcImage = imread("D:/images/4.jpg");
	Mat grayImage, dstImage;
	if (srcImage.empty())
	{
		cout << "could not load the src" << endl;
	}
	imshow("原图", srcImage);
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	GaussianBlur(grayImage, grayImage, Size(9, 9), 2, 2);
	//进行霍夫圆变换
	vector<Vec3f>circles;
	HoughCircles(grayImage, circles, HOUGH_GRADIENT, 1.5, 10, 120, 100, 20, 100);
	
	//依次在图中绘制出圆
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		//绘制圆心
		circle(srcImage, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆轮廓
		circle(srcImage, center, radius, Scalar(155, 50, 255), 2, 8, 0);

	}
	namedWindow("效果图", WINDOW_AUTOSIZE);
	imshow("效果图", srcImage);
	waitKey(0);
	return 0;
}