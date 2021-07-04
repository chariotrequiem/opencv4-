#include<opencv2/opencv.hpp>
#include<iostream>
#include<xfeatures2d.hpp>//SURF特征点头文件
#include<vector>

using namespace std;
using namespace cv;
using namespace xfeatures2d;

int main(int argc, char** argv)
{
	Mat img = imread("D:/images/13.jpg");
	if (!img.data)
	{
		cout << "cold not load the src!" << endl;
		return -1;
	}
	//创建SURF特征点类变量
	Ptr<SURF> surf = SURF::create(500,//关键点阈值
		                          4,  //4组“金字塔”
	                           	  3,  //每组“金字塔”有3层
		                          true,//使用128维描述子
		                          false);//计算关键点方向
	//计算SURF关键点
	vector<KeyPoint> Keypoints;
	surf->detect(img, Keypoints);
	//计算SURF描述子
	Mat descriptions;
	surf->compute(img, Keypoints, descriptions);
	//绘制特征点
	Mat imgAngel;
	img.copyTo(imgAngel);
	//绘制不含角度和大小的结果
	drawKeypoints(img, Keypoints, img, Scalar(255, 255, 255));
	//绘制含有角度和大小的结果
	drawKeypoints(img, Keypoints, imgAngel, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
	//显示结果
	imshow("不含角度和大小的结果", img);
	imshow("含有角度和大小的结果", imgAngel);
	waitKey(0);
	return 0;
}