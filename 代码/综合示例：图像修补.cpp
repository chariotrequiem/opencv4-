#include<iostream>
#include<opencv2/opencv.hpp>
using namespace std;
using namespace cv;
#define WINDOW_NAME1 "��ԭʼͼ��"
#define WINDOW_NAME2 "���޲����Ч��ͼ��"
//ȫ�ֱ�������
Mat srcImage1, inpaintMask;
Point previousPoint(-1, -1);//ԭ���ĵ�����
//on_Mouse�ص�����
static void on_Mouse(int event, int x, int y, int flags, void*)
{
	//������������Ϣ
	if (event == EVENT_LBUTTONUP || !(flags & EVENT_FLAG_LBUTTON))
		previousPoint = Point(-1, -1);
	//������������Ϣ
	else if (event == EVENT_LBUTTONDOWN)
		previousPoint = Point(x, y);
	//��갴�²��ƶ������л���
	else if (event == EVENT_MOUSEMOVE && (flags & EVENT_FLAG_LBUTTON))
	{
		Point pt(x, y);
		if (previousPoint.x < 0)
			previousPoint = pt;
		//���ư�ɫ����
		line(inpaintMask, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		line(srcImage1, previousPoint, pt, Scalar::all(255), 5, 8, 0);
		previousPoint = pt;
		imshow(WINDOW_NAME1, srcImage1);
	}
}

int main(int argc, char** argv)
{
	//����ԭʼͼ��������Ĥ��ʼ��
	Mat src = imread("D:/images/b.jpg", -1);
	if (src.empty())
	{
		cout << "could not load the src!" << endl;
		return false;
	}
	srcImage1 = src.clone();
	inpaintMask = Mat::zeros(srcImage1.size(), CV_8U);
	//��ʾԭʼͼ
	imshow(WINDOW_NAME1, srcImage1);
	//�������ص�����
	setMouseCallback(WINDOW_NAME1, on_Mouse, 0);
	//��ѯ���������ݲ�ͬ�İ������д���
	while (1)
	{
		//��ȡ����ֵ
		char c = (char)waitKey(0);
		//��ֵΪESC�������˳�
		if (c == 27)
			break;
		//��ֵΪ2���ָ���ԭʼͼ��
		if (c == '2')
		{
			inpaintMask = Scalar::all(0);
			src.copyTo(srcImage1);
			imshow(WINDOW_NAME1, srcImage1);
		}
		//��ֵΪ1���߿ո񣬽���ͼ���޲�����
		if (c == '1' || c == ' ')
		{
			Mat inpaintedImage;
			inpaint(srcImage1, inpaintMask, inpaintedImage, 3, INPAINT_TELEA);
			imshow(WINDOW_NAME2, inpaintedImage);
		}
	}
	return 0;
}