#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
//�궨�岿��
# define WINDOW_NAME "���򴰿�"
//ȫ�ֱ�������
Mat srcImage, dstImage, tmpImage;

int main(int argc, char** argv)
{
	//����ԭͼ
	srcImage = imread("D:/images/13.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src" << endl;
	}
	//������ʾ����
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, srcImage);

	//������ֵ
	tmpImage = srcImage;
	dstImage = tmpImage;
	//int key = 0;

	//��ѯ��ȡ������Ϣ
	while (1)
	{
		int key = waitKey(0);//��ȡ��ֵ��key������

		//����key������ֵ�����в�ͬ����
		switch ((char)key)
		{
		case 27://��ESC
			return 0;
			break;
		case 'q':
			return 0;
			break;

			//ͼ��Ŵ���ؼ�ֵ����
		case 'a'://����A���£�����pyrUp����
			pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << "��⵽����'A'���£���ʼ���л���[pyrUp]������ͼƬ�Ŵ�ͼƬ�ߴ�*2" << endl;
			break;
		case 'w'://����W���£�����resize����
			resize(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << "��⵽����'W'���£���ʼ���л���[resize]������ͼƬ�Ŵ�ͼƬ�ߴ�*2" << endl;
			break;
		case '1'://����1���£�����resize����
			resize(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << "��⵽����'1'���£���ʼ���л���[resize]������ͼƬ�Ŵ�ͼƬ�ߴ�*2" << endl;
			break;
		case '3'://����3���£�����pyrUp����
			pyrUp(tmpImage, dstImage, Size(tmpImage.cols * 2, tmpImage.rows * 2));
			cout << "��⵽����'3'���£���ʼ���л���[pyrUp]������ͼƬ�Ŵ�ͼƬ�ߴ�*2" << endl;
			break;

			//ͼ����С��ؼ�ֵ����
		case'd':
			pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << "��⵽����'D'���£���ʼ���л���[pyrUp]������ͼƬ��С��ͼƬ�ߴ�/2" << endl;
			break;
		case's':
			resize(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << "��⵽����'S'���£���ʼ���л���[resize]������ͼƬ��С��ͼƬ�ߴ�/2" << endl;
			break;
		case'2':
			resize(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << "��⵽����'2'���£���ʼ���л���[resize]������ͼƬ��С��ͼƬ�ߴ�/2" << endl;
			break;
		case'4':
			pyrDown(tmpImage, dstImage, Size(tmpImage.cols / 2, tmpImage.rows / 2));
			cout << "��⵽����'4'���£���ʼ���л���[pyrUp]������ͼƬ��С��ͼƬ�ߴ�/2" << endl;
			break;
		}
		//������������ʾ�仯���ͼ
		imshow(WINDOW_NAME, dstImage);

		//��dstImage����tmpImage��������һ��ѭ��
		tmpImage = dstImage;
	}
	return 0;
}