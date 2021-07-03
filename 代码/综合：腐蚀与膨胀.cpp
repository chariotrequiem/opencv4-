#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;

//ȫ�ֱ�����������
Mat srcImage, dstImage;
int TrackBarNumber = 0;//0��ʾ��ʴerode��1��ʾ����dilate
int StructElementSize = 3;//�ṹԪ��(�ں˾���)�ĳߴ�

//ȫ�ֺ�������
void Process();
void on_TrackbarNumChange(int, void*);//�ص�����
void on_ElementSizeChange(int, void*);//�ص�����
//������
int main(int argc, char**argv)
{
	srcImage = imread("D:/images/4.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src" << endl;
	}
	namedWindow("ԭʼͼ");
	imshow("ԭʼͼ", srcImage);
	//���г��θ�ʴ��������ʾЧ��ͼ
	namedWindow("Ч��ͼ");
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * StructElementSize + 1, 2 * StructElementSize + 1),
		Point(StructElementSize, StructElementSize));
	erode(srcImage, dstImage, element);
	imshow("Ч��ͼ", dstImage);

	//�����켣��
	createTrackbar("��ʴ/����", "Ч��ͼ", &TrackBarNumber, 1, on_TrackbarNumChange);
	createTrackbar("�ں˳ߴ�", "Ч��ͼ", &StructElementSize, 21, on_ElementSizeChange);
	//��ѯ��ȡ������Ϣ������q���������˳�
	while (char(waitKey(1)) != 'q') {}
	return 0;
}
//Process�������������Զ���ĸ�ʴ�����Ͳ���
void Process()
{
	//��ȡ�Զ����
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * StructElementSize + 1, 2 * StructElementSize + 1),
		Point(StructElementSize, StructElementSize));
	//���и�ʴ�����Ͳ���
	if (TrackBarNumber == 0)
	{
		erode(srcImage, dstImage, element);
	}
	else
	{
		dilate(srcImage, dstImage, element);
	}
	//��ʾЧ��ͼ
	imshow("Ч��ͼ", dstImage);
}
//��ʴ������֮���л����صĻص�����
void on_TrackbarNumChange(int, void*)
{
	//��ʴ�����ͼ�Ч���л����ص��庯����Ҫ����һ��Process������ʹ�ı���Ч��������Ч����ʾ����
	Process();
}
//��ʴ�����Ͳ����ں˸ı�ʱ�Ļص�����
void on_ElementSizeChange(int, void*)
{
	//�ں˳ߴ��Ѹı䣬�ص��庯������Ҫ����һ��Process������ʹ�ı���Ч��������Ч����ʾ����
	Process();
}