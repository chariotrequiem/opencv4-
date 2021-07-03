#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace std;
using namespace cv;

int main(int argc, char** aergv)
{
	//����ԭʼͼ
	Mat src = imread("D:/images/13.jpg");
	Mat src1 = src.clone();
	if (src.empty())
	{
		cout << "copuld not load the src!" << endl;
	}
	imshow("ԭʼͼ", src);

	//ת�ɻҶ�ͼ�����룬��Canny����󽫵õ��ı�Ե��Ϊ���롣����ԭͼ��Ч��ͼ�ϣ��õ���ɫ��Եͼ
	Mat dst, edge, gray;
	//1.������srcͬ���ͺʹ�С�ľ���(dst)
	dst.create(src1.size(), src1.type());
	//2.��Դͼ��ת��Ϊ�Ҷ�ͼ��
	cvtColor(src1, gray, COLOR_BGR2GRAY);
	//3.��ʹ��3*3�ں�������
	blur(gray, edge, Size(3, 3));
	//4.����Canny����
	Canny(edge, edge, 3, 9, 3);
	//5.��dst�ڵ�����Ԫ������Ϊ0
	dst = Scalar::all(0);
	//6.ʹ��Canny��������ı�Եͼg_cannyDetectedEdges��Ϊ���룬����ԭͼg_srcImage����Ŀ��ͼg_dstImage��
	src1.copyTo(dst, edge);
	//��ʾЧ��ͼ
	imshow("Ч��ͼ", dst);

	waitKey(0);
	return 0;
}