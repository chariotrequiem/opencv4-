#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace std;
using namespace cv;
//������������ȫ�ֱ�������������������
Mat srcImage, dstImage, srcGrayImage;
//Canny��Ե�����ر���
Mat cannyDetectedEdges;
int cannyLowThreshold = 1;//TrackBarλ�ú���
//Sobel��Ե������
Mat sobelGradient_x, sobelGradient_y;
Mat sobelAbsGradient_x, sobelAbsGradient_y;
int sobelKernelSize = 1;//TrackBarλ�ò���
//Scharr�˲�����ر���
Mat scharrGradient_x, scharrGradient_y;
Mat scharrAbsGradient_x, scharrAbsGradient_y;
//ȫ�ֺ�����������
static void on_Canny(int, void*);//Canny��Ե��ⴰ�ڹ������Ļص�����
static void on_Sobel(int, void*);//Sobel��Ե��ⴰ�ڹ������Ļص�����
void Scharr();//��װ��Scharr��Ե�����ش���ĺ���

//������
int main(int argc, char** argv)
{
	srcImage = imread("D:/images/4.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	namedWindow("ԭʼͼ");
	imshow("ԭʼͼ", srcImage);
	//������srcͬ���ͺʹ�С�ľ���(dst)
	dstImage.create(srcImage.size(), srcImage.type());
	//��ԭͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor(srcImage, srcGrayImage, COLOR_BGR2GRAY);
	//������ʾ����
	namedWindow("Canny��Ե���", WINDOW_AUTOSIZE);
	namedWindow("Sobel��Ե���", WINDOW_AUTOSIZE);
	//����trackbar
	createTrackbar("����ֵ��", "Canny��Ե���", &cannyLowThreshold, 120, on_Canny);
	createTrackbar("����ֵ��", "Sobel��Ե���", &sobelKernelSize, 3, on_Sobel);

	//���ûص�����
	on_Canny(0, 0);
	on_Sobel(0, 0);
	//���÷�װ��Scharr��Ե������ĺ���
	Scharr();
	//��ѯ��ȡ��������Ϣ��������Q�������˳�
	while ((char(waitKey(1)) != 'q')) {}
	return 0;
}

//on_Canny()������Canny��Ե��ⴰ�ڹ������Ļص�����
static void on_Canny(int, void*)
{
	//��ʹ��3*3�ں�������
	blur(srcGrayImage, cannyDetectedEdges, Size(3, 3));
	//����Canny����
	Canny(cannyDetectedEdges, cannyDetectedEdges, cannyLowThreshold, cannyLowThreshold * 3, 3);
	//�Ƚ�dstImage�ڵ�����Ԫ����Ϊ0
	dstImage = Scalar::all(0);
	//ʹ��Canny��������ı�ԵͼcannyDetectedEdges��Ϊ���룬����srcImage����Ŀ��ͼdstImage��
	srcImage.copyTo(dstImage, cannyDetectedEdges);
	//��ʾЧ��ͼ
	imshow("Canny��Ե���", dstImage);
}

//Sobel��Ե��ⴰ�ڹ������Ļص�����
static void on_Sobel(int, void*)
{
	//��X�����ݶ�
	Sobel(srcImage, sobelGradient_x, CV_16S, 1, 0, (2 * sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(sobelGradient_x, sobelAbsGradient_x);//�������ֵ���������ת����8λ
	//��Y�����ݶ�
	Sobel(srcImage, sobelGradient_y, CV_16S, 0, 1, (2 * sobelKernelSize + 1), 1, 1, BORDER_DEFAULT);
	convertScaleAbs(sobelGradient_y, sobelAbsGradient_y);//�������ֵ���������ת����8λ
	//�ϲ��ݶ�
	addWeighted(sobelAbsGradient_x, 0.5, sobelAbsGradient_y, 0.5, 0, dstImage);
	//��ʾЧ��ͼ
	imshow("Sobel��Ե���", dstImage);
}

//��װ��Scharr��Ե�����ش���ĺ���
void Scharr()
{
	//��X�����ݶ�
	Scharr(srcImage, scharrGradient_x, CV_16S, 1, 0, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(scharrGradient_x, scharrAbsGradient_x);//�������ֵ���������ת����8λ
	//��Y�����ݶ�
	Scharr(srcImage, scharrGradient_y, CV_16S, 0, 1, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(scharrGradient_y, scharrAbsGradient_y);//�������ֵ���������ת����8λ
	//�ϲ��ݶ�
	addWeighted(scharrAbsGradient_x, 0.5, scharrAbsGradient_y, 0.5, 0, dstImage);
	//��ʾЧ��ͼ
	imshow("Scharr�˲���", dstImage);
}