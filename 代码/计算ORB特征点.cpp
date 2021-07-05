#include<iostream>
#include<opencv2/opencv.hpp>
#include<xfeatures2d.hpp>
using namespace std;
using namespace cv;
using namespace xfeatures2d;

int main(int argc, char** argv)
{
	Mat img = imread("D:/images/leena.png");
	if (!img.data)
	{
		cout << "could not load te src!" << endl;
		return -1;
	}
	//����ORB�����������
	Ptr<ORB> orb = ORB::create(500,   //��������Ŀ
		                       1.2f, //�����������㼶������ű���
		                       8,   //����������ͼ�����ϵ��
		                       31, //��Ե��ֵ
		                       0, //ԭͼ�ڡ����������еĲ���
		                       2, //����������ʱ��Ҫ�õ����ص���Ŀ
		                       ORB::HARRIS_SCORE, //ʹ��Harris��������������
		                       31, //����������ʱ�ؼ�����Χ����ĳߴ�
		                       20);//����FAST�ǵ�ʱ����ֵ��ֵ����ֵ
	//����ORB�ؼ���
	vector<KeyPoint> Keypoints;
	orb->detect(img, Keypoints);//ȷ���ؼ���
	//����ORB������
	Mat descriptions;
	orb->compute(img, Keypoints, descriptions);
	//����������
	Mat imgAngel;
	img.copyTo(imgAngel);
	//���Ʋ����ǶȺʹ�С�Ľ��
	drawKeypoints(img, Keypoints, img, Scalar(255, 255, 255));
	//���ƺ��нǶȺʹ�С�Ľ��
	drawKeypoints(imgAngel, Keypoints, imgAngel, Scalar(255, 255, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("�����ǶȺʹ�С�Ľ��", img);
	imshow("���нǶȺʹ�С�Ľ��", imgAngel);
	waitKey(0);
	return 0;
}