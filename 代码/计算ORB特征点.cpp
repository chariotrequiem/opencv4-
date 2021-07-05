#include<iostream>
#include<opencv2/opencv.hpp>
#include<xfeatures2d.hpp>
using namespace std;
using namespace cv;
using namespace xfeatures2d;

int main(int argc, char** argv)
{
	Mat img = imread("D:/images/leena.png");
	if (!img.data)
	{
		cout << "could not load te src!" << endl;
		return -1;
	}
	//创建ORB特征点类变量
	Ptr<ORB> orb = ORB::create(500,   //特征点数目
		                       1.2f, //“金字塔”层级间的缩放比例
		                       8,   //“金字塔”图像层数系数
		                       31, //边缘阈值
		                       0, //原图在“金字塔”中的层数
		                       2, //生成描述子时需要用的像素点数目
		                       ORB::HARRIS_SCORE, //使用Harris方法评价特征点
		                       31, //生成描述子时关键点周围邻域的尺寸
		                       20);//计算FAST角点时像素值差值的阈值
	//计算ORB关键点
	vector<KeyPoint> Keypoints;
	orb->detect(img, Keypoints);//确定关键点
	//计算ORB描述子
	Mat descriptions;
	orb->compute(img, Keypoints, descriptions);
	//绘制特征点
	Mat imgAngel;
	img.copyTo(imgAngel);
	//绘制不含角度和大小的结果
	drawKeypoints(img, Keypoints, img, Scalar(255, 255, 255));
	//绘制含有角度和大小的结果
	drawKeypoints(imgAngel, Keypoints, imgAngel, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("不含角度和大小的结果", img);
	imshow("含有角度和大小的结果", imgAngel);
	waitKey(0);
	return 0;
}