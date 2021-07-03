#include<iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

//��һ��������ֱ��ͼ����
void drawHist(Mat& hist, int type, string name)
{
	int hist_w = 512;
	int hist_h = 400;
	int width = 2;
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
	normalize(hist, hist, 255, 0, type, -1, Mat());
	namedWindow(name, WINDOW_NORMAL);
	imshow(name, hist);
}
int main()
{
	Mat img = imread("D:/images/b.jpg");
	Mat sub_img = imread("D:/images/111.png");
	Mat img_HSV, sub_HSV, hist, hist2;
	if (img.empty() || sub_img.empty())
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	imshow("img", img);
	imshow("sub_img", sub_img);
	//ת��HSVͨ������ȡS��V����ͨ��
	cvtColor(img, img_HSV, COLOR_BGR2HSV);
	cvtColor(sub_img, sub_HSV, COLOR_BGR2HSV);
	int h_bins = 32;
	int s_bins = 32;
	int histSize[] = { h_bins ,s_bins };
	//Hͨ���ķ�ΧΪ179
	float h_ranges[] = { 0,180 };
	//Sͨ���ķ�ΧΪ179
	float s_ranges[] = { 0,256 };
	const float* ranges[] = { h_ranges ,s_ranges };//ÿ��ͨ���ķ�Χ
	int channels[] = { 0,1 };//ͳ�Ƶ�ͨ������
	//����H-Sֱ��ͼ
	calcHist(&sub_HSV, 1, channels, Mat(), hist, 2, histSize, ranges, true, false);
	drawHist(hist, NORM_INF, "hist");//ֱ��ͼ��һ��������ֱ��ͼ
	Mat backproj;
	calcBackProject(&img_HSV, 1, channels, hist, backproj, ranges, 1.0);
	imshow("����ͶӰ���", backproj);
	waitKey(0);
	return 0;
}