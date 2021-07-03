#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

//ȫ�ֺ�������
void colorReduce1(Mat& inputimage, Mat& outputimage, int div);
void colorReduce2(Mat& inputimage, Mat& outputimage, int div);
void colorReduce3(Mat& inputimage, Mat& outputimage, int div);


int main(int argc, char**argv)
{
	//����ԭʼͼ��
	Mat src = imread("D:/images/leena.png");
	imshow("ԭʼͼ��", src);
	//����ԭʼͼ�Ĳ������������Ч��ͼ
	Mat dst;
	dst.create(src.rows, src.cols, src.type());//Ч��ͼ�Ĵ�С��������ԭͼƬ���
	//��¼��ʼʱ��
	double time0 = static_cast<double>(getTickCount());
	//������ɫ�ռ���������
	//colorReduce1(src, dst, 32);
	//colorReduce2(src, dst, 32);
	colorReduce3(src, dst, 32);
	//��������ʱ�䲢���
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "�˷�������ʱ��Ϊ" << time0 << "��" << endl;
	//��ʾЧ��ͼ
	imshow("Ч��ͼ", dst);
	waitKey(0);
	return 0;
}

//ʹ��ָ����ʣ�C������[]
void colorReduce1(Mat& inputimage, Mat& outputimage, int div)
{
	outputimage = inputimage.clone();//����ʵ�ε���ʱ����
	int rowNumber = outputimage.rows;//����
	//���� * ͨ���� = ÿһ��Ԫ�صĸ���
	int colNumber = outputimage.cols*outputimage.channels();
	//˫��ѭ�����������е�����ֵ
	for (int i = 0; i < rowNumber; i++)//��ѭ��
	{
		uchar* data = outputimage.ptr<uchar>(i);//��ȡ��i���׵�ַ
		for (int j = 0; j < colNumber; j++)//��ѭ��
		{
			//��ʼ����ÿ������
			data[j] = data[j] / div * div + div / 2;
		}//�д������
	}
}

//ʹ�õ�����
void colorReduce2(Mat& inputimage, Mat& outputimage, int div)
{
	//����׼��
	outputimage = inputimage.clone();//����ʵ�ε���ʱ����
	//��ȡ������
	Mat_<Vec3b>::iterator it = outputimage.begin<Vec3b>();//��ʼλ�õ�����
	Mat_<Vec3b>::iterator itend = outputimage.end<Vec3b>();//��ֹλ�õ�����

	//��ȡ��ɫͼ������
	for (; it != itend; ++it)
	{
		//��ʼ����ÿ������
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}

}

//ʹ�ö�̬��ַ�������at
void colorReduce3(Mat& inputimage, Mat& outputimage, int div)
{
	//����׼��
	outputimage = inputimage.clone();//����ʵ�ε���ʱ����
	int rowNumber = outputimage.rows;//����
	int colNumber = outputimage.cols;//����
	//��ȡ��ɫͼ������
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			//��ɫͨ��
			outputimage.at<Vec3b>(i, j)[0] = outputimage.at<Vec3b>(i, j)[0] / div * div + div / 2;
			//��ɫͨ��
			outputimage.at<Vec3b>(i, j)[1] = outputimage.at<Vec3b>(i, j)[1] / div * div + div / 2;
			//��ɫͨ��
			outputimage.at<Vec3b>(i, j)[2] = outputimage.at<Vec3b>(i, j)[2] / div * div + div / 2;
		}//�д������
	}
}