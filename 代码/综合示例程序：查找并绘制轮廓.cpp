#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;

//����겿��
#define WINDOW_NAME1 "��ԭʼͼ���ڡ�"
#define WINDOW_NAME2 "������ͼ��"
//ȫ�ֱ�������
Mat srcImage, grayImage;
int Thresh = 80, Thresh_max = 255;
RNG g_rng(12345);
Mat cannyMat_output;
vector<vector<Point>>g_vContours;
vector<Vec4i>g_vHierarchy;
//ȫ�ֺ�������
static void ShowHelpText();
void on_ThreshChange(int, void*);

int main(int argc, char** argv)
{
	ShowHelpText();
	srcImage = imread("D:/images/17.jpeg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	//ת��Ϊ�ҶȲ�ģ��������
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));

	//��������
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, srcImage);
	//��������������ʼ��
	createTrackbar("canny��ֵ", WINDOW_NAME1, &Thresh, Thresh_max, on_ThreshChange);
	on_ThreshChange(0, 0);
	waitKey(0);
	return 0;
}

//�ص�����
void on_ThreshChange(int, void*)
{
	//��canny���Ӽ���Ե
	Canny(grayImage, cannyMat_output, Thresh, Thresh * 2, 3);
	//Ѱ������
	findContours(cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//�������
	Mat drawing = Mat::zeros(cannyMat_output.size(), CV_8UC3);
	for (int i = 0; i < g_vContours.size(); i++)
	{
		//Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//����ֵ
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, g_vContours, i, color, 1, 8, g_vHierarchy, 0, Point());
	}
	//��ʾЧ��ͼ
	imshow(WINDOW_NAME2, drawing);
}

static void ShowHelpText()
{
	cout << "��ǰʹ��OpenCV�汾Ϊ" << CV_VERSION << endl;
	cout << "\t����ͼ����Ѱ��������ʾ������" << endl;
	cout << "\t��������˵��" << endl;
	cout << "\t\t���̰�������� - �˳�����" << endl;
	cout << "\t\t����������" << endl;
}