#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat srcImage = imread("D:/images/abd.jpg");
	Mat midImage, dstImage;
	//进行边缘检测和转化为灰度图
	Canny(srcImage, midImage, 50, 200, 3);//进行一次Canny边缘检测
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);
	//进行霍夫线性变换
	vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLines(midImage, lines, 1, CV_PI / 180, 250, 0, 0);

	//依次在图中绘制出每段线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstImage, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);

	}
	//显示原始图
	imshow("原始图", srcImage);
	imshow("边缘检测后的图", midImage);
	imshow("效果图", dstImage);
	waitKey(0);
	return 0;

}