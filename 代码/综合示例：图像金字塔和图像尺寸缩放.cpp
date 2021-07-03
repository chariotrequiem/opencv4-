#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
//宏定义部分
# define WINDOW_NAME "程序窗口"
//全局变量声明
Mat srcImage, dstImage, tmpImage;

int main(int argc, char** argv)
{
	//载入原图
	srcImage = imread("D:/images/13.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src" << endl;
	}
	//创建显示窗口
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, srcImage);

	//参数赋值
	tmpImage = srcImage;
	dstImage = tmpImage;
	//int key = 0;

	//轮询获取按键信息
	while (1)
	{
		int key = waitKey(0);//读取键值到key变量中

		//根据key变量的值，进行不同操作
		switch ((char)key)
		{
		case 27://按ESC
			return 0;
			break;
		case 'q':
			return 0;
			break;

			//图像放大相关键值处理
		case 'a'://按键A按下，调用pyrUp函数
			pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << "检测到按键'A'按下，开始进行基于[pyrUp]函数的图片放大：图片尺寸*2" << endl;
			break;
		case 'w'://按键W按下，调用resize函数
			resize(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << "检测到按键'W'按下，开始进行基于[resize]函数的图片放大：图片尺寸*2" << endl;
			break;
		case '1'://按键1按下，调用resize函数
			resize(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << "检测到按键'1'按下，开始进行基于[resize]函数的图片放大：图片尺寸*2" << endl;
			break;
		case '3'://按键3按下，调用pyrUp函数
			pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << "检测到按键'3'按下，开始进行基于[pyrUp]函数的图片放大：图片尺寸*2" << endl;
			break;

			//图像缩小相关键值操作
		case'd':
			pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << "检测到按键'D'按下，开始进行基于[pyrUp]函数的图片缩小：图片尺寸/2" << endl;
			break;
		case's':
			resize(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << "检测到按键'S'按下，开始进行基于[resize]函数的图片缩小：图片尺寸/2" << endl;
			break;
		case'2':
			resize(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << "检测到按键'2'按下，开始进行基于[resize]函数的图片缩小：图片尺寸/2" << endl;
			break;
		case'4':
			pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << "检测到按键'4'按下，开始进行基于[pyrUp]函数的图片缩小：图片尺寸/2" << endl;
			break;
		}
		//经过操作后，显示变化后的图
		imshow(WINDOW_NAME, dstImage);

		//将dstImage赋给tmpImage，方便下一次循环
		tmpImage = dstImage;
	}
	return 0;
}