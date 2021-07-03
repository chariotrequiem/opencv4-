#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
//�����
#define WINDOW_NAME1 "[ԭʼͼ����]"
#define WINDOW_NAME2 "[����warp���ͼ��]"
#define WINDOW_NAME3 "[����warp��Rotate��Ĵ���]"

//ȫ�ֺ�������
static void ShowHelpText();

int main(int argc, char** argv)
{
	ShowHelpText();
	//1.����׼��
	//��������㣬��������������
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	//����һЩMat����
	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	//2.����Դͼ������ʼ��
	srcImage = imread("D:/images/13.jpg");
	if (srcImage.empty())
	{
		cout << "could not load the src!" << endl;
		return false;
	}
	dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());
	//3.����Դͼ���Ŀ��ͼ���ϵ�������Լ������任
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));

	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));
	//4.ȡ�÷���任
	warpMat = getAffineTransform(srcTriangle, dstTriangle);
	//5.��Դͼ��Ӧ�øո���õķ���任
	warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());
	//6.��ͼ��������ź�����ת
	//������ͼ���е�˳ʱ����ת50����������Ϊ0.6����ת����
	Point center = Point(dstImage_warp.cols / 2, dstImage_warp.rows / 2);
	double angle = -50.0;
	double scale = 0.6;
	//ͨ���������תϸ����Ϣ�����ת����
	rotMat = getRotationMatrix2D(center, angle, scale);
	//��ת�����ź��ͼ��
	warpAffine(dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size());
	//7.��ʾ���
	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, dstImage_warp);
	imshow(WINDOW_NAME3, dstImage_warp_rotate);

	waitKey(0);
	return 0;
}

static void ShowHelpText()
{
	cout << "\t********��ӭ����������任��ʾ������********" << endl;
	cout << "\t\t��ǰʹ�õ�OpenCV�汾Ϊ" << CV_VERSION << endl;
}