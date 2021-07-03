#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat srcImage, dstImage;
	Mat map_x, map_y;
	srcImage = imread("D:/images/13.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	imshow("原始图", srcImage);
	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);
	for (int j = 0; j < srcImage.rows; j++)
	{
		for (int i = 0; i < srcImage.cols; i++)
		{
			//改变map_x，map_y的值
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
		}
	}

	//进行重映射操作
	remap(srcImage, dstImage, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));

	//显示效果图
	imshow("效果图", dstImage);
	waitKey(0);
	return 0;
}