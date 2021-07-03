#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//����ȫ�ֱ���
Mat srcImage, dstImage;
int ElementShape = MORPH_RECT;//Ԫ�ؽṹ����״
//�������յ�TrackBarλ�ò���
int MaxInterationNum = 10;
int OpenCloseNum = 0;
int ErodeDilateNum = 0;
int TopBlackHatNum = 0;
//ȫ�ֺ�������
static void on_OpenCLose(int, void*);//�ص�����
static void on_ErodeDilate(int, void*);//�ص�����
static void on_TopBlackHat(int, void*);//�ص�����
static void ShowHelpText();//����������ʾ

//������
int main(int argc, char** argv)
{
	ShowHelpText();
	//����ԭͼ
	srcImage = imread("D:/images/15.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
	}
	//��ʾԭʼͼ
	namedWindow("ԭʼͼ");
	imshow("ԭʼͼ", srcImage);
	//������������
	namedWindow("������/������", 1);
	namedWindow("��ʴ/����", 1);
	namedWindow("��ñ/��ñ", 1);
	//������ֵ
	OpenCloseNum = 9;
	ErodeDilateNum = 9;
	TopBlackHatNum = 2;
	//�ֱ�Ϊ�������ڴ���������
	createTrackbar("����ֵ", "������/������", &OpenCloseNum, MaxInterationNum * 2 + 1, on_OpenCLose);
	createTrackbar("����ֵ", "��ʴ/����", &ErodeDilateNum, MaxInterationNum * 2 + 1, on_ErodeDilate);
	createTrackbar("����ֵ", "��ñ/��ñ", &TopBlackHatNum, MaxInterationNum * 2 + 1, on_TopBlackHat);
	//��ѯ��ȡ������Ϣ
	while (true)
	{
		int c;
		//ִ�лص�����
		on_OpenCLose(OpenCloseNum, 0);
		on_ErodeDilate(ErodeDilateNum, 0);
		on_TopBlackHat(TopBlackHatNum, 0);
		//��ȡ����
		c = waitKey(1);

		//���¼��̰���Q��esc�������˳�
		if ((char)c == 'q' || (char)c == 27)
			break;
		//���¼��̰���1,ʹ����Բ(Elloptic)�ṹԪ��MORPH_ELLIPSE
		if ((char)c == 49)//���̰���1��ASII��Ϊ49
			ElementShape = MORPH_ELLIPSE;
		//���¼��̰���2,ʹ�þ���(Rectangle)�ṹԪ��MORPH_RECT
		else if ((char)c == 50)//���̰���2��ASCII��ֵΪ50
			ElementShape = MORPH_RECT;
		//���¼��̰���3,ʹ��ʮ����(Cross-shaped)�ṹԪ��MORPH_CROSS
		else if ((char)c == 51)//���̰���3��ASCII��ֵΪ51
			ElementShape = MORPH_CROSS;
		else if ((char)c == ' ')
			ElementShape = (ElementShape + 1) % 3;
	}
	return 0;
}

//������/�����㴰�ڵĻص�����
static void on_OpenCLose(int, void*)
{
	//ƫ�����Ķ���
	int offset = OpenCloseNum - MaxInterationNum;//ƫ����
	int Absolute_offset = offset > 0 ? offset : -offset;//ƫ��������ֵ
	//�Զ����
	Mat element = getStructuringElement(ElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	if (offset < 0)
		morphologyEx(srcImage, dstImage, MORPH_OPEN, element);
	else
		morphologyEx(srcImage, dstImage, MORPH_CLOSE, element);
	//��ʾͼ��
	imshow("������/������", dstImage);
}

//��ʴ/���ʹ��ڵĻص�����
static void on_ErodeDilate(int, void*)
{
	//ƫ�����Ķ���
	int offset = ErodeDilateNum - MaxInterationNum;//ƫ����
	int Absolute_offset = offset > 0 ? offset : -offset;//ƫ��������ֵ
	//�Զ����
	Mat element = getStructuringElement(ElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	if (offset < 0)
		erode(srcImage, dstImage, element);
	else
		dilate(srcImage, dstImage, element);
	//��ʾͼ��
	imshow("��ʴ/����", dstImage);
}

//��ñ/��ñ���ڵĻص�����
static void on_TopBlackHat(int, void*)
{
	//ƫ�����Ķ���
	int offset = TopBlackHatNum - MaxInterationNum;//ƫ����
	int Absolute_offset = offset > 0 ? offset : -offset;//ƫ��������ֵ
	//�Զ����
	Mat element = getStructuringElement(ElementShape, Size(Absolute_offset * 2 + 1, Absolute_offset * 2 + 1),
		Point(Absolute_offset, Absolute_offset));
	if (offset < 0)
		morphologyEx(srcImage, dstImage, MORPH_TOPHAT, element);
	else
		morphologyEx(srcImage, dstImage, MORPH_BLACKHAT, element);
	//��ʾͼ��
	imshow("��ñ/��ñ", dstImage);
}

//����������ʾ����
static void ShowHelpText()
{
	cout << "\t������������۲�ͼ��Ч��" << endl;
	cout << "\t��������˵��" << endl;
	cout << "\t\t���̰���ESC����Q �����˳�����" << endl;
	cout << "\t\t���̰���1        ����ʹ����Բ�ṹԪ��" << endl;
	cout << "\t\t���̰���2        ����ʹ�þ��νṹԪ��" << endl;
	cout << "\t\t���̰���3        ����ʹ��ʮ���νṹԪ��" << endl;
	cout << "\t\t���̰����ո�space��������Բ�����Ρ�ʮ���νṹԪ����ѭ��" << endl;
}