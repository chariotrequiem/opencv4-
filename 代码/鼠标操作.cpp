#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;


//ȫ�ֺ���������
void on_MouseHandle(int event, int x, int y, int flags, void* param);
void DrawRectangle(Mat& image, Rect box);
void ShowHelpText();

//ȫ�ֱ�������
Rect g_rectangle;
bool g_bDrawingBox = false;
RNG g_rng(12345);


//on_MouseHandle()����
//���ص����������ݲ�ͬ������¼����в�ͬ����
void on_MouseHandle(int event, int x, int y, int flags, void* param)
{
	Mat& image = *(Mat*)param;
	switch (event)
	{
		//����ƶ���Ϣ
	case EVENT_MOUSEMOVE:
	{
		if (g_bDrawingBox)//����Ƿ���л��Ƶı�ʶ��Ϊ�棬���¼�³��Ϳ�RECT�ͱ�����
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
	}
	break;

	//���������Ϣ
	case EVENT_LBUTTONDOWN:
	{
		g_bDrawingBox = true;
		g_rectangle = Rect(x, y, 0, 0);
	}
	break;

	//���̧����Ϣ
	case EVENT_LBUTTONUP:
	{
		g_bDrawingBox = false;//�ñ�ʶ��Ϊfalse
		//�Կ�͸�С��0�Ĵ���
		if (g_rectangle.width < 0)
		{
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}
		if (g_rectangle.height < 0)
		{
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		//���ú������л���
		DrawRectangle(image, g_rectangle);
	}
	break;
	}
}


//�Զ�����λ�ͼ����
void DrawRectangle(Mat& image, Rect box)
{
	//�����ɫ
	rectangle(image, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}

int main(int argc, char** argv)
{
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat src(600, 800, CV_8UC3), temp;
	src.copyTo(temp);
	g_rectangle = Rect(-1, -1, 0, 0);
	src = Scalar::all(0);

	//�����������ص�����
	namedWindow("WINDOW_NAME");
	setMouseCallback("WINDOW_NAME", on_MouseHandle, (void*)&src);

	//������ѭ���������Ʒ���Ϊ��ʱ���л���
	while (1)
	{
		src.copyTo(temp);//����Դͼ����ʱ����
		if (g_bDrawingBox)
			DrawRectangle(temp, g_rectangle);//�����л��Ʊ�ʶ����Ϊ��ʱ������л��ơ�
		imshow("WINDOW_NAME", temp);
		if (waitKey(10) == 27)
			break;
	}
	return 0;
}