#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
int main(int argc, char** argv)
{
	Mat image(800, 800, CV_8UC3);
	RNG& rng = theRNG();
	while (1)
	{
		//参数初始化
		int count = rng.uniform(3, 103);//随机生成点的数量
		vector<Point>points;//点值

		//随机生成点坐标
		for (int i = 0; i < count; i++)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);
			points.push_back(point);
		}
		//对给定的二维点集，寻找最小面积的包围圆
		Point2f center;
		float radius = 0;
		minEnclosingCircle(Mat(points), center, radius);
		//绘制出随机颜色的点
		image = Scalar::all(0);
		for (int i = 0; i < count; i++)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);
		//绘制出最小面积的包围圆
		circle(image, center, radius, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 2, LINE_AA);
		imshow("矩形包围示例", image);
		char key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q')
			break;
	}
	return 0;
}