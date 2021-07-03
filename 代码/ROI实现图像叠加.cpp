#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//ROI_AddImage（）函数
//利用感兴趣区域ROI实现图像叠加
bool ROI_AddImage()
{
	//1.读入图像
	Mat srcImage1 = imread("D:/images/a.jpg");
	Mat logoImage = imread("D:/images/women.png");
	if (srcImage1.empty()) 
	{
		cout << "读取srcImage1失败" << endl;
		return false;
	}
	if (logoImage.empty())
	{
		cout << "读取logoImage失败" << endl;
		return false;
	}
	//2.定义一个Mat类型并给其设定ROI区域
	Mat imageROI = srcImage1(Rect(0,0, logoImage.cols, logoImage.rows));
	//3.加载掩膜（必须是灰度图）
	Mat mask = imread("D:/images/women.png", 0);
	//4.将掩膜复制到ROI
	logoImage.copyTo(imageROI, mask);
	//5.显示结果
	namedWindow("利用ROI实现图像叠加示例窗口",WINDOW_FREERATIO);
	imshow("利用ROI实现图像叠加示例窗口", srcImage1);
	waitKey(0);
	return true;
}
int main(int argc, char** argv)
{
	ROI_AddImage();
	return 0;
}