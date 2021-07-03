#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//定义辅助宏
#define WINDOW_NAME "【程序窗口】"
//定义全局变量
Mat srcImage, dstIamge;
Mat map_x, map_y;
//全局函数声明
int update_map(int key);
static void ShowHelpText();//输出帮助文字

int main(int argc, char** argv)
{
	ShowHelpText();
	//1.载入原始图
	srcImage = imread("D:/images/13.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src" << endl;
	}
	imshow("原始图", srcImage);
	//2.创建和原始图一样的效果图，x重映射图，y重映射图
	dstIamge.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);
	//创建窗口并显示
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, srcImage);
	//waitKey(0);
	//4.轮询按键，更新map_x和map_y的值，进行重映射操作并显示效果图
	while (1)
	{
		//获取键盘按键
		int key = waitKey(0);
		//判断ESC是否按下，若按下便退出
		if ((key & 255) == 27)
		{
			cout << "——————程序退出——————" << endl;
			break;
		}
		//根据按下的键盘按键来更新map_x和map_y的值，然后调用remap()进行重映射
		update_map(key);
		remap(srcImage, dstIamge, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
		//显示效果图
		imshow(WINDOW_NAME, dstIamge);
	}
	return 0;
}

//根据按键来更新map_x和map_y的值
int update_map(int key)
{
	//双层循环，遍历每一个像素点
	for (int j = 0; j < srcImage.rows; j++)
	{
		for (int i = 0; i < srcImage.cols; i++)
		{
			switch (key)
			{
			case'1'://键盘【1】按下，进行第一种映射操作
				if (i > srcImage.cols*0.25 && i<srcImage.cols*0.75 && j>srcImage.rows*0.25 && j < srcImage.rows*0.75)
				{
					map_x.at<float>(j, i) = static_cast<float>(2 * (i - srcImage.cols*0.25) + 0.5);
					map_y.at<float>(j, i) = static_cast<float>(2 * (j - srcImage.rows*0.25) + 0.5);
				}
				else
				{
					map_x.at<float>(j, i) = 0;
					map_y.at<float>(j, i) = 0;
				}
				break;
			case'2'://键盘【2】按下，进行第一种映射操作
				map_x.at<float>(j, i) = static_cast<float>(i);
				map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
				break;
			case'3'://键盘【3】按下，进行第一种映射操作
				map_x.at<float>(j, i) = static_cast<float>(srcImage.cols - i);
				map_y.at<float>(j, i) = static_cast<float>(j);
				break;
			case'4'://键盘【4】按下，进行第一种映射操作
				map_x.at<float>(j, i) = static_cast<float>(srcImage.cols - i);
				map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
				break;
			}
		}
	}
	return 1;
}
//输出帮助文字
static void ShowHelpText()
{
	cout << "\t欢迎来到重映射示例程序~" << endl;
	cout << "当前使用的openCV版本为OpenCV" << CV_VERSION << endl;
	cout << "\t按键操作说明：" << endl;
	cout << "\t\t键盘按键【ESC】 - 退出程序" << endl;
	cout << "\t\t键盘按键【1】 - 第一种映射方式" << endl;
	cout << "\t\t键盘按键【2】 - 第二种映射方式" << endl;
	cout << "\t\t键盘按键【3】 - 第三种映射方式" << endl;
	cout << "\t\t键盘按键【4】 - 第四种映射方式" << endl;
}