#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//定义辅助宏
#define  WINDOW_NAME "程序窗口"
//描述全局变量
int ThresholdValue = 100;
int ThresholdType = 3;
Mat srcImage, grayImage, dstImage;
//全局函数声明
static void ShowHelpText();//帮助输出文字
void on_Threshold(int, void*);//回调函数

//主函数
int main(int argc, char** argv)
{
	ShowHelpText();
	srcImage = imread("D:/images/13.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	//存留一份原图的灰度图
	cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	//创建滑动条来控制阈值
	createTrackbar("模式", WINDOW_NAME, &ThresholdType, 4, on_Threshold);
	createTrackbar("参数值", WINDOW_NAME, &ThresholdValue, 255, on_Threshold);

	//初始化自定义的阈值回调函数
	on_Threshold(0, 0);
	//轮询等待用户按键，如果ESC按下则退出程序
	while (1)
	{
		int key;
		key = waitKey(20);
		if ((char)key == 27) { break; }
	}
	return 0;
}

void on_Threshold(int, void*)
{
	//调用阈值函数
	threshold(grayImage, dstImage, ThresholdValue, 255, ThresholdType);
	//更新效果图
	imshow(WINDOW_NAME, dstImage);
}

static void ShowHelpText()
{
	cout << "\t按键操作说明" << endl;
	cout << "\t\t键盘按键ESC — 退出程序" << endl;
	cout << "\t\t滚动条模式0 — 二进制阈值" << endl;
	cout << "\t\t滚动条模式1 — 反二进制阈值" << endl;
	cout << "\t\t滚动条模式2 — 截断阈值" << endl;
	cout << "\t\t滚动条模式3 — 反阈值化为0" << endl;
	cout << "\t\t滚动条模式4 — 阈值化为0" << endl;
}