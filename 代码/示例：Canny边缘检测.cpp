#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** aergv)
{
	//载入原始图
	Mat src = imread("D:/images/13.jpg");
	Mat src1 = src.clone();
	if (src.empty())
	{
		cout << "copuld not load the src!" << endl;
	}
	imshow("原始图", src);

	//转成灰度图，降噪，用Canny，最后将得到的边缘作为掩码。拷贝原图到效果图上，得到彩色边缘图
	Mat dst, edge, gray;
	//1.创建与src同类型和大小的矩阵(dst)
	dst.create(src1.size(), src1.type());
	//2.将源图像转换为灰度图像
	cvtColor(src1, gray, COLOR_BGR2GRAY);
	//3.先使用3*3内核来降噪
	blur(gray, edge, Size(3, 3));
	//4.运行Canny算子
	Canny(edge, edge, 3, 9, 3);
	//5.将dst内的所有元素设置为0
	dst = Scalar::all(0);
	//6.使用Canny算子输出的边缘图g_cannyDetectedEdges作为掩码，来讲原图g_srcImage拷到目标图g_dstImage中
	src1.copyTo(dst, edge);
	//显示效果图
	imshow("效果图", dst);

	waitKey(0);
	return 0;
}