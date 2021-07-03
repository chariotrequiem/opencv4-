#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//定义全局变量
Mat srcImage, dstImage;
int ElementShape = MORPH_RECT;//元素结构的形状
//变量接收的TrackBar位置参数
int MaxInterationNum = 10;
int OpenCloseNum = 0;
int ErodeDilateNum = 0;
int TopBlackHatNum = 0;
//全局函数声明
static void on_OpenCLose(int, void*);//回调函数
static void on_ErodeDilate(int, void*);//回调函数
static void on_TopBlackHat(int, void*);//回调函数
static void ShowHelpText();//帮助文字显示

//主函数
int main(int argc, char** argv)
{
	ShowHelpText();
	//载入原图
	srcImage = imread("D:/images/15.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	//显示原始图
	namedWindow("原始图");
	imshow("原始图", srcImage);
	//创建三个窗口
	namedWindow("开运算/闭运算", 1);
	namedWindow("腐蚀/膨胀", 1);
	namedWindow("顶帽/黑帽", 1);
	//参数赋值
	OpenCloseNum = 9;
	ErodeDilateNum = 9;
	TopBlackHatNum = 2;
	//分别为三个窗口创建滚动条
	createTrackbar("迭代值", "开运算/闭运算", &OpenCloseNum, MaxInterationNum * 2 + 1, on_OpenCLose);
	createTrackbar("迭代值", "腐蚀/膨胀", &ErodeDilateNum, MaxInterationNum * 2 + 1, on_ErodeDilate);
	createTrackbar("迭代值", "顶帽/黑帽", &TopBlackHatNum, MaxInterationNum * 2 + 1, on_TopBlackHat);
	//轮询获取按键信息
	while (true)
	{
		int c;
		//执行回调函数
		on_OpenCLose(OpenCloseNum, 0);
		on_ErodeDilate(ErodeDilateNum, 0);
		on_TopBlackHat(TopBlackHatNum, 0);
		//获取按键
		c = waitKey(1);

		//按下键盘按键Q或esc，程序退出
		if ((char)c == 'q' || (char)c == 27)
			break;
		//按下键盘按键1,使用椭圆(Elloptic)结构元素MORPH_ELLIPSE
		if ((char)c == 49)//键盘按键1的ASII码为49
			ElementShape = MORPH_ELLIPSE;
		//按下键盘按键2,使用矩形(Rectangle)结构元素MORPH_RECT
		else if ((char)c == 50)//键盘按键2的ASCII码值为50
			ElementShape = MORPH_RECT;
		//按下键盘按键3,使用十字形(Cross-shaped)结构元素MORPH_CROSS
		else if ((char)c == 51)//键盘按键3的ASCII码值为51
			ElementShape = MORPH_CROSS;
		else if ((char)c == ' ')
			ElementShape = (ElementShape + 1) % 3;
	}
	return 0;
}

//开运算/闭运算窗口的回调函数
static void on_OpenCLose(int, void*)
{
	//偏移量的定义
	int offset = OpenCloseNum - MaxInterationNum;//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;//偏移量绝对值
	//自定义核
	Mat element = getStructuringElement(ElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	if (offset < 0)
		morphologyEx(srcImage, dstImage, MORPH_OPEN, element);
	else
		morphologyEx(srcImage, dstImage, MORPH_CLOSE, element);
	//显示图像
	imshow("开运算/闭运算", dstImage);
}

//腐蚀/膨胀窗口的回调函数
static void on_ErodeDilate(int, void*)
{
	//偏移量的定义
	int offset = ErodeDilateNum - MaxInterationNum;//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;//偏移量绝对值
	//自定义核
	Mat element = getStructuringElement(ElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	if (offset < 0)
		erode(srcImage, dstImage, element);
	else
		dilate(srcImage, dstImage, element);
	//显示图像
	imshow("腐蚀/膨胀", dstImage);
}

//顶帽/黑帽窗口的回调函数
static void on_TopBlackHat(int, void*)
{
	//偏移量的定义
	int offset = TopBlackHatNum - MaxInterationNum;//偏移量
	int Absolute_offset = offset > 0 ? offset : -offset;//偏移量绝对值
	//自定义核
	Mat element = getStructuringElement(ElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	if (offset < 0)
		morphologyEx(srcImage, dstImage, MORPH_TOPHAT, element);
	else
		morphologyEx(srcImage, dstImage, MORPH_BLACKHAT, element);
	//显示图像
	imshow("顶帽/黑帽", dstImage);
}

//帮助文字显示函数
static void ShowHelpText()
{
	cout << "\t请调整滚动条观察图像效果" << endl;
	cout << "\t按键操作说明" << endl;
	cout << "\t\t键盘按键ESC或者Q ——退出程序" << endl;
	cout << "\t\t键盘按键1        ——使用椭圆结构元素" << endl;
	cout << "\t\t键盘按键2        ——使用矩形结构元素" << endl;
	cout << "\t\t键盘按键3        ——使用十字形结构元素" << endl;
	cout << "\t\t键盘按键空格space——在椭圆、矩形、十字形结构元素中循环" << endl;
}