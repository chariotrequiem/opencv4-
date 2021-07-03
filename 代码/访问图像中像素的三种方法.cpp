#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//全局函数声明
void colorReduce1(Mat& inputimage, Mat& outputimage, int div);
void colorReduce2(Mat& inputimage, Mat& outputimage, int div);
void colorReduce3(Mat& inputimage, Mat& outputimage, int div);


int main(int argc, char**argv)
{
	//创建原始图像
	Mat src = imread("D:/images/leena.png");
	imshow("原始图像", src);
	//按照原始图的参数规格来创建效果图
	Mat dst;
	dst.create(src.rows, src.cols, src.type());//效果图的大小、类型与原图片相等
	//记录起始时间
	double time0 = static_cast<double>(getTickCount());
	//调用颜色空间缩减函数
	//colorReduce1(src, dst, 32);
	//colorReduce2(src, dst, 32);
	colorReduce3(src, dst, 32);
	//计算运行时间并输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为" << time0 << "秒" << endl;
	//显示效果图
	imshow("效果图", dst);
	waitKey(0);
	return 0;
}

//使用指针访问：C操作符[]
void colorReduce1(Mat& inputimage, Mat& outputimage, int div)
{
	outputimage = inputimage.clone();//复制实参到临时变量
	int rowNumber = outputimage.rows;//行数
	//列数 * 通道数 = 每一行元素的个数
	int colNumber = outputimage.cols*outputimage.channels();
	//双重循环，遍历所有的像素值
	for (int i = 0; i < rowNumber; i++)//行循环
	{
		uchar* data = outputimage.ptr<uchar>(i);//获取第i行首地址
		for (int j = 0; j < colNumber; j++)//列循环
		{
			//开始处理每个像素
			data[j] = data[j] / div * div + div / 2;
		}//行处理结束
	}
}

//使用迭代器
void colorReduce2(Mat& inputimage, Mat& outputimage, int div)
{
	//参数准备
	outputimage = inputimage.clone();//复制实参到临时变量
	//获取迭代器
	Mat_<Vec3b>::iterator it = outputimage.begin<Vec3b>();//初始位置迭代器
	Mat_<Vec3b>::iterator itend = outputimage.end<Vec3b>();//终止位置迭代器

	//存取彩色图像像素
	for (; it != itend; ++it)
	{
		//开始处理每个像素
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}

}

//使用动态地址运算配合at
void colorReduce3(Mat& inputimage, Mat& outputimage, int div)
{
	//参数准备
	outputimage = inputimage.clone();//复制实参到临时变量
	int rowNumber = outputimage.rows;//行数
	int colNumber = outputimage.cols;//列数
	//存取彩色图像像素
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			//蓝色通道
			outputimage.at<Vec3b>(i, j)[0] = outputimage.at<Vec3b>(i, j)[0] / div * div + div / 2;
			//绿色通道
			outputimage.at<Vec3b>(i, j)[1] = outputimage.at<Vec3b>(i, j)[1] / div * div + div / 2;
			//红色通道
			outputimage.at<Vec3b>(i, j)[2] = outputimage.at<Vec3b>(i, j)[2] / div * div + div / 2;
		}//行处理结束
	}
}