#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat img = imread("D:/images/leena.png", IMREAD_COLOR);
	if (!img.data)
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	//转换为灰度图像
	Mat gray;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	//计算Harris评价系数
	Mat harris;
	int blockSize = 2;//邻域半径
	int apertureSize = 3;
	cornerHarris(gray, harris, blockSize, apertureSize, 0.04);
	//归一化以便进行数值比较和结果显示
	Mat harrisn;
	normalize(harris, harrisn, 0, 255, NORM_MINMAX);

	//将图像的数据类型变为CV_8U
	convertScaleAbs(harrisn, harrisn);
	//寻找Harris角点
	vector<KeyPoint> keyPoints;
	for (int row = 0; row < harrisn.rows; row++)
	{
		for (int col = 0; col < harrisn.cols; col++)
		{
			int R = harrisn.at<uchar>(row, col);
			if (R > 125)
			{
				//将角点存入KeyPoint中
				KeyPoint keyPoint;
				keyPoint.pt.y = row;
				keyPoint.pt.x = col;
				keyPoints.push_back(keyPoint);
			}
		}
	}
	//绘制角点与显示结果
	drawKeypoints(img, keyPoints, img);
	imshow("系数矩阵", harrisn);
	imshow("Harris角点", img);
	waitKey(0);
	return 0;
}