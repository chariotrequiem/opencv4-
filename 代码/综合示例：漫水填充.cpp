#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//ȫ�ֱ�������
Mat srcImage, dstImage, grayImage, maskImage;//����ԭʼͼ��Ŀ��ͼ���Ҷ�ͼ����Ĥͼ
int g_nFillMode = 1;//��ˮ����ģʽ
int g_nLowDifference = 20, g_nUpDifference = 20;//�������ֵ���������ֵ
int g_nConnectivity = 4;//��ʾfloodFill������ʶ���Ͱ�λ����ֵͨ
int g_bIsColor = true;//�Ƿ�Ϊ��ɫͼ�ı�ʶ������ֵ
bool g_bUseMask = false;//�Ƿ���ʾ��Ĥ���ڵĲ���ֵ
int g_nNewMaskVal = 255;//�µ����»��Ƶ�����ֵ

//onMouse()�������������ϢonMouse�ص�����
static void onMouse(int event, int x, int y, int, void* param)
{
	//��������û�а��¾ͷ���
	if (event != EVENT_LBUTTONDOWN)
		return;

	//��������1.����floodFill����ǰ�Ĳ���׼�����֡�������
	Point seed = Point(x, y);
	int LowDifference = g_nFillMode == 0 ? 0 : g_nLowDifference;//�շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ�ֵ�g_nLowDifference
	int UpDifference = g_nFillMode == 0 ? 0 : g_nUpDifference;//�շ�Χ����ˮ��䣬��ֵ��Ϊ0��������Ϊȫ�ֵ�g_nUpDifference

	//��ʶ����0~7λΪg_nConnectivity��8~15λΪg_nNewMaskVal����8λ��ֵ��16~23λΪCV_FLOODFILL_FIXED_RANGE����0
	int flags = g_nConnectivity + (g_nNewMaskVal << 8) + (g_nFillMode == 1 ? FLOODFILL_FIXED_RANGE : 0);

	//�������bgrֵ
	int b = (unsigned)theRNG() & 255;//�漴����һ��0-255֮���ֵ
	int g = (unsigned)theRNG() & 255;//�漴����һ��0-255֮���ֵ
	int r = (unsigned)theRNG() & 255;//�漴����һ��0-255֮���ֵ
	Rect ccomp;//�����ػ��������С�߽��������

	//���ػ��������ص���ֵ�����ǲ�ɫͼģʽ��ȡScalar(b, g, r)�����ǻҶ�ͼģʽ��ȡScalar(r*0.299 + g * 0.587 + b * 0.114)
	Scalar newVal = g_bIsColor ? Scalar(b, g, r) : Scalar(r*0.299 + g * 0.587 + b * 0.114);

	Mat dst = g_bIsColor ? dstImage : grayImage;//Ŀ��ͼ�ĸ�ֵ
	int area;

	//��������2.��ʽ����floodFill������������
	if (g_bUseMask)
	{
		threshold(maskImage, maskImage, 1, 128, THRESH_BINARY);
		area = floodFill(dst, maskImage, seed, newVal, &ccomp,
			Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference));
		imshow("mask", maskImage);
	}
	else
	{
		area = floodFill(dst, seed, newVal, &ccomp, Scalar(LowDifference, LowDifference, LowDifference),
			Scalar(UpDifference, UpDifference, UpDifference), flags);
	}
	imshow("Ч��ͼ", dst);
	cout << area << " �����ر��ػ�" << endl;
}

//main����
int main(int argc, char** argv)
{
	//����ԭͼ
	srcImage = imread("D:/images/10.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	srcImage.copyTo(dstImage);//����ԭͼ��Ŀ��ͼ
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);//ת����ͨ��ͼ�񵽻Ҷ�ͼ
	maskImage.create(srcImage.rows + 2, srcImage.cols + 2, CV_8UC1);//����src�ĳߴ�����ʼ����Ĥ

	namedWindow("Ч��ͼ", WINDOW_AUTOSIZE);


	//ѭ����ѯ����
	while (1)
	{
		//����Trackbar
		createTrackbar("�������ֵ", "Ч��ͼ", &g_nLowDifference, 255, 0);
		createTrackbar("�������ֵ", "Ч��ͼ", &g_nUpDifference, 255, 0);
		//���ص�����
		setMouseCallback("Ч��ͼ", onMouse, 0);
		//����ʾЧ��ͼ
		imshow("Ч��ͼ", g_bIsColor ? dstImage : grayImage);
		//��ȡ���̰���
		int c = waitKey(0);
		//�ж�ESC�Ƿ��£������¾��˳�
		if ((c & 255) == 27)
		{
			cout << "�����˳�" << endl;
			break;
		}

		//���ݰ�����ͬ�������ֲ���
		switch ((char)c)
		{
			//�������'1'���£�Ч��ͼ�ڻҶ�ͼ����ɫͼ�以��
		case'1':
			if (g_bIsColor)//��ԭ��Ϊ��ɫ��ת��Ϊ�Ҷ�ͼ�����ҽ���Ĥmask����Ԫ����0
			{
				cout << "����'1'�����£��л���ɫ/�Ҷ�ģʽ����ǰ����Ϊ��[��ɫģʽ]�л�Ϊ[�Ҷ�ģʽ]" << endl;
				srcImage.copyTo(dstImage);
				maskImage = Scalar::all(0);
				g_bIsColor = true;//����ʶ����Ϊtrue����ʾ��ǰͼ��ģʽΪ��ɫ
			}
			break;
			//������̰���"2"�����£���ʾ/���ش���
		case'2':
			if (g_bUseMask)
			{
				destroyAllWindows();
				g_bUseMask = false;
			}
			else
			{
				namedWindow("mask", 0);
				maskImage = Scalar::all(0);
				imshow("mask", maskImage);
				g_bUseMask = true;
			}
			break;
			//������̰���'3'�����£��ָ�ԭʼͼ��
		case'3':
			cout << "����'3'�����£��ָ�ԭʼͼ��" << endl;
			srcImage.copyTo(dstImage);
			cvtColor(dstImage, grayImage, COLOR_BGR2GRAY);
			maskImage = Scalar::all(0);
			break;
			//������̰���'4'�����£�ʹ�ÿշ�Χ����ˮ���
		case'4':
			cout << "����'4'�����£�ʹ�ÿշ�Χ����ˮ���" << endl;
			g_nFillMode = 0;
			break;
			//������̰���'5'�����£�ʹ�ý��䡢�̶���Χ����ˮ���
		case'5':
			cout << "���̰���'5'�����£�ʹ�ý��䡢�̶���Χ����ˮ���" << endl;
			g_nFillMode = 1;
			break;
			//������̰���'6'�����£�ʹ�ý��䡢������Χ����ˮ���
		case'6':
			cout << "���̰���'6'�����£�ʹ�ý��䡢������Χ����ˮ���" << endl;
			g_nFillMode = 2;
			break;
			//������̰���'7'�����£�������־���ĵͰ�λʹ��4λ������ģʽ
		case'7':
			cout << "���̰���'7'�����£�������־���ĵͰ�λʹ��4λ������ģʽ" << endl;
			g_nConnectivity = 4;
			break;
			//���̰���'8'�����£�������־���ĵͰ�λʹ��8λ������ģʽ
		case'8':
			cout << "���̰���'8'�����£�������־���ĵͰ�λʹ��8λ������ģʽ" << endl;
			g_nConnectivity = 8;
			break;
		}
	}
	return 0;
}
