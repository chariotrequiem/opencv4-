#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//全局变量声明部分
Mat srcImage, dstImage;
int TrackBarNumber = 0;//0表示腐蚀erode，1表示膨胀dilate
int StructElementSize = 3;//结构元素(内核矩阵)的尺寸

//全局函数声明
void Process();
void on_TrackbarNumChange(int, void*);//回调函数
void on_ElementSizeChange(int, void*);//回调函数
//主函数
int main(int argc, char**argv)
{
	srcImage = imread("D:/images/4.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src" << endl;
	}
	namedWindow("原始图");
	imshow("原始图", srcImage);
	//进行初次腐蚀操作并显示效果图
	namedWindow("效果图");
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * StructElementSize + 1, 2 * StructElementSize + 1),
		Point(StructElementSize, StructElementSize));
	erode(srcImage, dstImage, element);
	imshow("效果图", dstImage);

	//创建轨迹条
	createTrackbar("腐蚀/膨胀", "效果图", &TrackBarNumber, 1, on_TrackbarNumChange);
	createTrackbar("内核尺寸", "效果图", &StructElementSize, 21, on_ElementSizeChange);
	//轮询获取按键信息，若下q键，程序退出
	while (char(waitKey(1)) != 'q') {}
	return 0;
}
//Process函数——进行自定义的腐蚀和膨胀操作
void Process()
{
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * StructElementSize + 1, 2 * StructElementSize + 1),
		Point(StructElementSize, StructElementSize));
	//进行腐蚀或膨胀操作
	if (TrackBarNumber == 0)
	{
		erode(srcImage, dstImage, element);
	}
	else
	{
		dilate(srcImage, dstImage, element);
	}
	//显示效果图
	imshow("效果图", dstImage);
}
//腐蚀和膨胀之间切换开关的回调函数
void on_TrackbarNumChange(int, void*)
{
	//腐蚀和膨胀间效果切换，回调体函数需要调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}
//腐蚀和膨胀操作内核改变时的回调函数
void on_ElementSizeChange(int, void*)
{
	//内核尺寸已改变，回调体函数内需要调用一次Process函数，使改变后的效果立即生效并显示出来
	Process();
}