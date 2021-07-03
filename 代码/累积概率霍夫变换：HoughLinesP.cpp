#include<opencv2/opencv.hpp>
#include<imgproc/imgproc.hpp>
#include<highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat srcImage = imread("D:/images/16.jpg");
	Mat midImage, dstImage;
	//进行边缘检测并转化为灰度图
	Canny(srcImage, midImage, 50, 250, 3);
	cvtColor(midImage, dstImage, COLOR_GRAY2BGR);
	//进行霍夫线变换
	vector<Vec4i>lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
	HoughLinesP(midImage, lines, 1, CV_PI / 180, 80, 50, 10);
	//依次在途中绘制出每条线段
	for (size_t i = 0; i < lines.size(); i++)
	{
		Vec4i l = lines[i];
		line(dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);
	}
	//显示图像
	imshow("原始图", srcImage);
	imshow("边缘检测后的图", midImage);
	imshow("效果图", dstImage);
	waitKey(0);
	return 0;
}