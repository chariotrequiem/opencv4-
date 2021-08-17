#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int* argc, char** argv)
{
	Mat src = imread("D:/images/key.jpg");
	if (src.empty())
	{
		cout << "could not load yhe src!" << endl;
		return -1;
	}
	//修改图像尺寸
	Mat img;
	resize(src, img, Size(360,326), 0, 0, INTER_AREA);

	//分割
	Mat result1, result2;
	TermCriteria T10 = TermCriteria(TermCriteria::COUNT | TermCriteria::COUNT, 10, 0.1);
	pyrMeanShiftFiltering(img, result1, 20, 40, 2, T10);//第一次分割
	pyrMeanShiftFiltering(result1, result2, 20, 40, 2, T10);//第一次分割后的结果在进行分割

	//显示分割结果
	imshow("img", img);
	imshow("result1", result1);
	imshow("result2", result2);

	//对图像进行Canny边缘提取
	Mat imgCanny, result1Canny, result2Canny;
	Canny(img, imgCanny, 150, 300);
	Canny(result1, result1Canny, 150, 300);
	Canny(result2, result2Canny, 150, 300);

	//显示边缘检测结果
	imshow("imgCanny", imgCanny);
	imshow("result1Canny", result1Canny);
	imshow("result2Canny", result2Canny);
	waitKey(0);
	return 0;
}