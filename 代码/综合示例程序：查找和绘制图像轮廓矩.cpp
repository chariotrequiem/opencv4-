#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;

#define WINDOW_NAME1 "��ԭʼͼ��"
#define WINDOW_NAME2 "��ͼ��������"
//ȫ�ֱ�������
Mat srcImage, grayImage;
int g_Thresh = 100, g_MaxThresh = 255;
RNG g_rng(12345);
Mat g_CannyMat_output;
vector<vector<Point>>g_Contours;
vector<Vec4i>g_Hierarchy;

//ȫ�ֺ�������
void on_ThreshChange(int, void*);
static void ShowHelpText();

int main(int argc, char** argv)
{
	ShowHelpText();
	//����Դͼ�񣬷���3ͨ��ͼ������
	srcImage = imread("D:/images/13.jpg");
	//��Դͼ��ת��Ϊ�Ҷ�ͼ�񲢽���ƽ��
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	blur(grayImage, grayImage, Size(3, 3));
	//�����´���
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1, srcImage);
	//���������������г�ʼ��
	createTrackbar("��ֵ��", WINDOW_NAME1, &g_Thresh, g_MaxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);
	waitKey(0);
	return 0;
}
static void ShowHelpText()
{
	cout << "��ӭ�������Һͻ��������س���" << endl;
	cout << "��ǰOpenCV�汾Ϊ" << CV_VERSION << endl;
}

void on_ThreshChange(int, void*)
{
	//ʹ��Canny��Ե���
	Canny(grayImage, g_CannyMat_output, g_Thresh, g_Thresh * 2, 3);
	//�ҵ�����
	findContours(g_CannyMat_output, g_Contours, g_Hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));
	//�����
	vector<Moments>mu(g_Contours.size());
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		mu[i] = moments(g_Contours[i], false);
	}
	//�������ľ�
	vector<Point2f>mc(g_Contours.size());
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}
	//��������
	Mat drawing = Mat::zeros(g_CannyMat_output.size(), CV_8UC3);
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		//Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, g_Contours, i, color, 1, 8, g_Hierarchy, 0, Point());//���������ڲ�����
		circle(drawing, mc[i], 4, color, -1, 8, 0);//����Բ
	}
	//��ʾ������
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);

	//ͨ��m00��������������Һ�OpenCV�������бȽ�
	cout << "\t������ݣ��������������" << endl;
	for (unsigned int i = 0; i < g_Contours.size(); i++)
	{
		cout << ">ͨ��m00���������" << i << "�������(M_00) = " << mu[i].m00 << endl;
		cout << "OpenCV�������������� = " << contourArea(g_Contours[i]) << "������ = " << arcLength(g_Contours[i], true) << endl;
		/*Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_Contours, i, color, 1, 8, g_Hierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);*/
	}
}
