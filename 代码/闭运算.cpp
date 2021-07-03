#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main()
{
	//载入原始图
	Mat src = imread("D:/images/6.jpg");
	if (src.empty())
	{
		cout << "could load the src!" << endl;
	}
	//创建窗口
	namedWindow("原图");
	namedWindow("闭运算效果图");
	imshow("原图", src);
	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dst;
	morphologyEx(src, dst, MORPH_CLOSE, element);
	imshow("闭运算效果图", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}