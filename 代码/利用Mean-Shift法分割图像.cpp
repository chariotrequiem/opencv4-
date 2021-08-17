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
	//�޸�ͼ��ߴ�
	Mat img;
	resize(src, img, Size(360,326), 0, 0, INTER_AREA);

	//�ָ�
	Mat result1, result2;
	TermCriteria T10 = TermCriteria(TermCriteria::COUNT | TermCriteria::COUNT, 10, 0.1);
	pyrMeanShiftFiltering(img, result1, 20, 40, 2, T10);//��һ�ηָ�
	pyrMeanShiftFiltering(result1, result2, 20, 40, 2, T10);//��һ�ηָ��Ľ���ڽ��зָ�

	//��ʾ�ָ���
	imshow("img", img);
	imshow("result1", result1);
	imshow("result2", result2);

	//��ͼ�����Canny��Ե��ȡ
	Mat imgCanny, result1Canny, result2Canny;
	Canny(img, imgCanny, 150, 300);
	Canny(result1, result1Canny, 150, 300);
	Canny(result2, result2Canny, 150, 300);

	//��ʾ��Ե�����
	imshow("imgCanny", imgCanny);
	imshow("result1Canny", result1Canny);
	imshow("result2Canny", result2Canny);
	waitKey(0);
	return 0;
}