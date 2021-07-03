#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//全局变量声明
Mat srcImage, dstImage, grayImage, maskImage;//定义原始图、目标图、灰度图、掩膜图
int g_nFillMode = 1;//漫水填充的模式
int g_nLowDifference = 20, g_nUpDifference = 20;//负差最大值，正差最大值
int g_nConnectivity = 4;//表示floodFill函数标识符低八位的连通值
int g_bIsColor = true;//是否为彩色图的标识符布尔值
bool g_bUseMask = false;//是否显示掩膜窗口的布尔值
int g_nNewMaskVal = 255;//新的重新绘制的像素值

//onMouse()函数——鼠标消息onMouse回调函数
static void onMouse(int event, int x, int y, int, void* param)
{
	//若鼠标左键没有按下就返回
	if (event != EVENT_LBUTTONDOWN)
		return;

	//————1.调用floodFill函数前的参数准备部分————
	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;//空范围的漫水填充，此值设为0，否则设为全局的g_nLowDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;//空范围的漫水填充，此值设为0，否则设为全局的g_nUpDifference

	//标识符的0~7位为g_nConnectivity，8~15位为g_nNewMaskVal左移8位的值，16~23位为CV_FLOODFILL_FIXED_RANGE或者0
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	//随机生成bgr值
	int b = (unsigned)theRNG() & 255;//随即返回一个0-255之间的值
	int g = (unsigned)theRNG() & 255;//随即返回一个0-255之间的值
	int r = (unsigned)theRNG() & 255;//随即返回一个0-255之间的值
	Rect ccomp;//定义重绘区域的最小边界矩形区域

	//在重绘区域像素的新值，若是彩色图模式，取Scalar(b, g, r)；若是灰度图模式，取Scalar(r*0.299 + g * 0.587 + b * 0.114)
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g * 0.587 + b * 0.114);

	Mat dst = g_bIsColor ? dstImage : grayImage;//目标图的赋值
	int area;

	//————2.正式调用floodFill函数————
	if (g_bUseMask)
	{
		threshold(maskImage, maskImage, 1, 128, THRESH_BINARY);
		area = floodFill(dst, maskImage, seed, newVal, &ccomp,
			Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference));
		imshow("mask", maskImage);
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
	}
	imshow("效果图", dst);
	cout << area << " 个像素被重绘" << endl;
}

//main函数
int main(int argc, char** argv)
{
	//载入原图
	srcImage = imread("D:/images/10.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	srcImage.copyTo(dstImage);//复制原图到目标图
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);//转换三通道图像到灰度图
	maskImage.create(srcImage.rows + 2, srcImage.cols + 2, CV_8UC1);//利用src的尺寸来初始化掩膜

	namedWindow("效果图", WINDOW_AUTOSIZE);


	//循环轮询按键
	while (1)
	{
		//创建Trackbar
		createTrackbar("负差最大值", "效果图", &g_nLowDifference, 255, 0);
		createTrackbar("正差最大值", "效果图", &g_nUpDifference, 255, 0);
		//鼠标回调函数
		setMouseCallback("效果图", onMouse, 0);
		//先显示效果图
		imshow("效果图", g_bIsColor ? dstImage : grayImage);
		//获取键盘按键
		int c = waitKey(0);
		//判断ESC是否按下，若按下就退出
		if ((c & 255) == 27)
		{
			cout << "程序退出" << endl;
			break;
		}

		//根据按键不同，做各种操作
		switch ((char)c)
		{
			//如果键盘'1'按下，效果图在灰度图、彩色图间互换
		case'1':
			if (g_bIsColor)//若原来为彩色，转换为灰度图，并且将掩膜mask所有元素置0
			{
				cout << "键盘'1'被按下，切换彩色/灰度模式，当前操作为将[彩色模式]切换为[灰度模式]" << endl;
				srcImage.copyTo(dstImage);
				maskImage = Scalar::all(0);
				g_bIsColor = true;//将标识符置为true，表示当前图像模式为彩色
			}
			break;
			//如果键盘按键"2"被按下，显示/隐藏窗口
		case'2':
			if (g_bUseMask)
			{
				destroyAllWindows();
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				maskImage = Scalar::all(0);
				imshow("mask", maskImage);
				g_bUseMask = true;
			}
			break;
			//如果键盘按键'3'被按下，恢复原始图像
		case'3':
			cout << "按键'3'被按下，恢复原始图像" << endl;
			srcImage.copyTo(dstImage);
			cvtColor(dstImage, grayImage, COLOR_BGR2GRAY);
			maskImage = Scalar::all(0);
			break;
			//如果键盘按键'4'被按下，使用空范围的漫水填充
		case'4':
			cout << "按键'4'被按下，使用空范围的漫水填充" << endl;
			g_nFillMode = 0;
			break;
			//如果键盘按键'5'被按下，使用渐变、固定范围的漫水填充
		case'5':
			cout << "键盘按键'5'被按下，使用渐变、固定范围的漫水填充" << endl;
			g_nFillMode = 1;
			break;
			//如果键盘按键'6'被按下，使用渐变、浮动范围的漫水填充
		case'6':
			cout << "键盘按键'6'被按下，使用渐变、浮动范围的漫水填充" << endl;
			g_nFillMode = 2;
			break;
			//如果键盘按键'7'被按下，操作标志符的低八位使用4位的连接模式
		case'7':
			cout << "键盘按键'7'被按下，操作标志符的低八位使用4位的连接模式" << endl;
			g_nConnectivity = 4;
			break;
			//键盘按键'8'被按下，操作标志符的低八位使用8位的连接模式
		case'8':
			cout << "键盘按键'8'被按下，操作标志符的低八位使用8位的连接模式" << endl;
			g_nConnectivity = 8;
			break;
		}
	}
	return 0;
}
