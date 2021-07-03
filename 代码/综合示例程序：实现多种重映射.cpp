#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//���帨����
#define WINDOW_NAME "�����򴰿ڡ�"
//����ȫ�ֱ���
Mat srcImage, dstIamge;
Mat map_x, map_y;
//ȫ�ֺ�������
int update_map(int key);
static void ShowHelpText();//�����������

int main(int argc, char** argv)
{
	ShowHelpText();
	//1.����ԭʼͼ
	srcImage = imread("D:/images/13.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src" << endl;
	}
	imshow("ԭʼͼ", srcImage);
	//2.������ԭʼͼһ����Ч��ͼ��x��ӳ��ͼ��y��ӳ��ͼ
	dstIamge.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);
	//�������ڲ���ʾ
	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME, srcImage);
	//waitKey(0);
	//4.��ѯ����������map_x��map_y��ֵ��������ӳ���������ʾЧ��ͼ
	while (1)
	{
		//��ȡ���̰���
		int key = waitKey(0);
		//�ж�ESC�Ƿ��£������±��˳�
		if ((key & 255) == 27)
		{
			cout << "�����������������˳�������������" << endl;
			break;
		}
		//���ݰ��µļ��̰���������map_x��map_y��ֵ��Ȼ�����remap()������ӳ��
		update_map(key);
		remap(srcImage, dstIamge, map_x, map_y, INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
		//��ʾЧ��ͼ
		imshow(WINDOW_NAME, dstIamge);
	}
	return 0;
}

//���ݰ���������map_x��map_y��ֵ
int update_map(int key)
{
	//˫��ѭ��������ÿһ�����ص�
	for (int j = 0; j < srcImage.rows; j++)
	{
		for (int i = 0; i < srcImage.cols; i++)
		{
			switch (key)
			{
			case'1'://���̡�1�����£����е�һ��ӳ�����
				if (i > srcImage.cols*0.25 && i<srcImage.cols*0.75 && j>srcImage.rows*0.25 && j < srcImage.rows*0.75)
				{
					map_x.at<float>(j, i) = static_cast<float>(2 * (i - srcImage.cols*0.25) + 0.5);
					map_y.at<float>(j, i) = static_cast<float>(2 * (j - srcImage.rows*0.25) + 0.5);
				}
				else
				{
					map_x.at<float>(j, i) = 0;
					map_y.at<float>(j, i) = 0;
				}
				break;
			case'2'://���̡�2�����£����е�һ��ӳ�����
				map_x.at<float>(j, i) = static_cast<float>(i);
				map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
				break;
			case'3'://���̡�3�����£����е�һ��ӳ�����
				map_x.at<float>(j, i) = static_cast<float>(srcImage.cols - i);
				map_y.at<float>(j, i) = static_cast<float>(j);
				break;
			case'4'://���̡�4�����£����е�һ��ӳ�����
				map_x.at<float>(j, i) = static_cast<float>(srcImage.cols - i);
				map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
				break;
			}
		}
	}
	return 1;
}
//�����������
static void ShowHelpText()
{
	cout << "\t��ӭ������ӳ��ʾ������~" << endl;
	cout << "��ǰʹ�õ�openCV�汾ΪOpenCV" << CV_VERSION << endl;
	cout << "\t��������˵����" << endl;
	cout << "\t\t���̰�����ESC�� - �˳�����" << endl;
	cout << "\t\t���̰�����1�� - ��һ��ӳ�䷽ʽ" << endl;
	cout << "\t\t���̰�����2�� - �ڶ���ӳ�䷽ʽ" << endl;
	cout << "\t\t���̰�����3�� - ������ӳ�䷽ʽ" << endl;
	cout << "\t\t���̰�����4�� - ������ӳ�䷽ʽ" << endl;
}