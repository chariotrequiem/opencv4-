#include<opencv2/opencv.hpp>
#include<iostream>
using namespace std;
using namespace cv;
int main(int argc, char**argv)
{
	Mat src = imread("D:/images/6.jpg");
	if (src.empty())
	{
		cout << "could load the src" << endl;
	}
	namedWindow("Ô­Í¼");
	namedWindow("¸¯Ê´²Ù×÷");
	imshow("Ô­Í¼", src);

	Mat element = getStructuringElement(MORPH_RECT, Size(5, 5));
	Mat dst;
	//½øÐÐ¸¯Ê´²Ù×÷
	erode(src, dst, element);
	imshow("¸¯Ê´²Ù×÷", dst);
	waitKey(0);
	destroyAllWindows();
	return 0;
}