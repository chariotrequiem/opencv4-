#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;


//全局函数的声明
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(Mat& image, Rect box);
void ShowHelpText();

//全局变量声明
Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(12345);


//on_MouseHandle()函数
//鼠标回调函数，根据不同的鼠标事件进行不同操作
void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	Mat& image = *(Mat*)param;
	switch (event)
	{
		//鼠标移动消息
	case EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox)//如果是否进行绘制的标识符为真，则记录下长和宽到RECT型变量中
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
	break;

	//左键按下消息
	case EVENT_LBUTTONDOWN:
	{
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0);
	}
	break;

	//左键抬起消息
	case EVENT_LBUTTONUP:
	{
		g_bDrawingBox = false;//置标识符为false
		//对宽和高小于0的处理
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}
		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		//调用函数进行绘制
		DrawRectangle(image, g_rectangle);
	}
	break;
	}
}


//自定义矩形绘图函数
void DrawRectangle(Mat& image, Rect box)
{
	//随机颜色
	rectangle(image, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}

int main(int argc, char** argv)
{
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat src(600, 800, CV_8UC3), temp;
	src.copyTo(temp);
	g_rectangle = Rect(-1, -1, 0, 0);
	src = Scalar::all(0);

	//设置鼠标操作回调函数
	namedWindow("WINDOW_NAME");
	setMouseCallback("WINDOW_NAME", on_MouseHandle, (void*)&src);

	//程序主循环，当绘制符号为真时进行绘制
	while (1)
	{
		src.copyTo(temp);//复制源图到临时变量
		if (g_bDrawingBox)
			DrawRectangle(temp, g_rectangle);//当进行绘制标识符号为真时，则进行绘制、
		imshow("WINDOW_NAME", temp);
		if (waitKey(10) == 27)
			break;
	}
	return 0;
}