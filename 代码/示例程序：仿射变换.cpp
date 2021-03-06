#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
//定义宏
#define WINDOW_NAME1 "[原始图窗口]"
#define WINDOW_NAME2 "[经过warp后的图像]"
#define WINDOW_NAME3 "[经过warp和Rotate后的窗口]"

//全局函数声明
static void ShowHelpText();

int main(int argc, char** argv)
{
	ShowHelpText();
	//1.参数准备
	//定义两组点，代表两个三角形
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	//定义一些Mat变量
	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	//2.加载源图像并作初始化
	srcImage = imread("D:/images/13.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
		return false;
	}
	dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());
	//3.设置源图像和目标图像上的三组点以计算仿射变换
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));

	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));
	//4.取得仿射变换
	warpMat = getAffineTransform(srcTriangle, dstTriangle);
	//5.对源图像应用刚刚求得的仿射变换
	warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());
	//6.对图像进行缩放后再旋转
	//计算绕图像中点顺时针旋转50度缩放因子为0.6的旋转矩阵
	Point center = Point(dstImage_warp.cols / 2, dstImage_warp.rows / 2);
	double angle = -50.0;
	double scale = 0.6;
	//通过上面的旋转细节信息求得旋转矩阵
	rotMat = getRotationMatrix2D(center, angle, scale);
	//旋转已缩放后的图像
	warpAffine(dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size());
	//7.显示结果
	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, dstImage_warp);
	imshow(WINDOW_NAME3, dstImage_warp_rotate);

	waitKey(0);
	return 0;
}

static void ShowHelpText()
{
	cout << "\t********欢迎来到【仿射变换】示例程序********" << endl;
	cout << "\t\t当前使用的OpenCV版本为" << CV_VERSION << endl;
}