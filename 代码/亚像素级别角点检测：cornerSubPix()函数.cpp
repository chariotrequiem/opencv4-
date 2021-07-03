#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat img = imread("D:/images/29.jpg",IMREAD_COLOR);
	if (!img.data)
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	Mat img2;
	img.copyTo(img2);
	//彩色转化为灰度图像
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//提取角点
	int maxCorners = 100;//检测角点数目
	double quality_level = 0.01;//质量等级，或者是指阈值与最佳角点的比例关系
	double minDistance = 0.04;//两个角点之间的最小欧氏距离
	vector<Point2f>corners;
	goodFeaturesToTrack(gray, corners, maxCorners, quality_level, minDistance, Mat(), 3, false);
	//计算亚像素级别角点坐标
	vector<Point2f>cornersSub = corners;//角点备份，防止函数被修改
	Size winSize = Size(5, 5);
	Size zeroZone = Size(-1, -1);
	TermCriteria criteria = TermCriteria(TermCriteria::EPS + TermCriteria::COUNT, 40, 0.001);
	cornerSubPix(gray, cornersSub, winSize, zeroZone, criteria);
	//输出初始坐标与精细坐标
	for (size_t i = 0; i < corners.size(); i++)
	{
		string str = to_string(i);
		str = "第" + str + "个角点初始坐标：";
		cout << str << corners[i] << "  精细后坐标：" << cornersSub[i] << endl;
	}

	//初始角点存放在KeyPoint类中
	vector<KeyPoint>KeyPoints;
	for (int i = 0; i < corners.size(); i++)
	{
		KeyPoint KeyPoint;
		KeyPoint.pt = corners[i];
		KeyPoints.push_back(KeyPoint);
	}
	//将亚像素级别角点存入KeyPoint类中
	vector<KeyPoint>KeyPoints2;
	for (int i = 0; i < cornersSub.size(); i++)
	{
		KeyPoint KeyPoint;
		KeyPoint.pt = cornersSub[i];
		KeyPoints2.push_back(KeyPoint);
	}
	drawKeypoints(img, KeyPoints, img);
	drawKeypoints(img2, KeyPoints2, img2);
	imshow("初始角点", img);
	imshow("亚像素角点", img2);
	waitKey(0);
	return 0;
}