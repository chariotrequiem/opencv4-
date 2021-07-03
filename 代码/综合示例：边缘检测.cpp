#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace std;
using namespace cv;
//——————全局变量声明——————
Mat srcImage, dstImage, srcGrayImage;
//Canny边缘检测相关变量
Mat cannyDetectedEdges;
int cannyLowThreshold = 1;//TrackBar位置函数
//Sobel边缘检测变量
Mat sobelGradient_x, sobelGradient_y;
Mat sobelAbsGradient_x, sobelAbsGradient_y;
int sobelKernelSize = 1;//TrackBar位置参数
//Scharr滤波器相关变量
Mat scharrGradient_x, scharrGradient_y;
Mat scharrAbsGradient_x, scharrAbsGradient_y;
//全局函数声明部分
static void on_Canny(int, void*);//Canny边缘检测窗口滚动条的回调函数
static void on_Sobel(int, void*);//Sobel边缘检测窗口滚动条的回调函数
void Scharr();//封装了Scharr边缘检测相关代码的函数

//主函数
int main(int argc, char** argv)
{
	srcImage = imread("D:/images/4.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	namedWindow("原始图");
	imshow("原始图", srcImage);
	//创建与src同类型和大小的矩阵(dst)
	dstImage.create(srcImage.size(), srcImage.type());
	//将原图像转换为灰度图像
	cvtColor(srcImage, srcGrayImage, COLOR_BGR2GRAY);
	//创建显示窗口
	namedWindow("Canny边缘检测", WINDOW_AUTOSIZE);
	namedWindow("Sobel边缘检测", WINDOW_AUTOSIZE);
	//创建trackbar
	createTrackbar("参数值：", "Canny边缘检测", &cannyLowThreshold, 120, on_Canny);
	createTrackbar("参数值：", "Sobel边缘检测", &sobelKernelSize, 3, on_Sobel);

	//调用回调函数
	on_Canny(0, 0);
	on_Sobel(0, 0);
	//调用封装了Scharr边缘检测代码的函数
	Scharr();
	//轮询获取案按键信息，若按下Q，程序退出
	while ((char(waitKey(1)) != 'q')) {}
	return 0;
}

//on_Canny()函数，Canny边缘检测窗口滚动条的回调函数
static void on_Canny(int, void*)
{
	//先使用3*3内核来降噪
	blur(srcGrayImage, cannyDetectedEdges, Size(3, 3));
	//运行Canny算子
	Canny(cannyDetectedEdges, cannyDetectedEdges, cannyLowThreshold, cannyLowThreshold * 3, 3);
	//先将dstImage内的所有元素置为0
	dstImage = Scalar::all(0);
	//使用Canny算子输出的边缘图cannyDetectedEdges作为掩码，来将srcImage拷到目标图dstImage中
	srcImage.copyTo(dstImage, cannyDetectedEdges);
	//显示效果图
	imshow("Canny边缘检测", dstImage);
}

//Sobel边缘检测窗口滚动条的回调函数
static void on_Sobel(int, void*)
{
	//求X方向梯度
	Sobel(srcImage, sobelGradient_x, CV_16S, 1, 0, (2 * sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(sobelGradient_x, sobelAbsGradient_x);//计算绝对值，并将结果转换成8位
	//求Y方向梯度
	Sobel(srcImage, sobelGradient_y, CV_16S, 0, 1, (2 * sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(sobelGradient_y, sobelAbsGradient_y);//计算绝对值，并将结果转换成8位
	//合并梯度
	addWeighted(sobelAbsGradient_x, 0.5, sobelAbsGradient_y, 0.5, 0, dstImage);
	//显示效果图
	imshow("Sobel边缘检测", dstImage);
}

//封装了Scharr边缘检测相关代码的函数
void Scharr()
{
	//求X方向梯度
	Scharr(srcImage, scharrGradient_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(scharrGradient_x, scharrAbsGradient_x);//计算绝对值，并将结果转换成8位
	//求Y方向梯度
	Scharr(srcImage, scharrGradient_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(scharrGradient_y, scharrAbsGradient_y);//计算绝对值，并将结果转换成8位
	//合并梯度
	addWeighted(scharrAbsGradient_x, 0.5, scharrAbsGradient_y, 0.5, 0, dstImage);
	//显示效果图
	imshow("Scharr滤波器", dstImage);
}