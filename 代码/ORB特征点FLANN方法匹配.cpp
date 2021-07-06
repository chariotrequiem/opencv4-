#include<opencv2/opencv.hpp>
#include<iostream>
#include<vector>
using namespace std;
using namespace cv;

void orb_features(Mat& gray, vector<KeyPoint> &keypoints, Mat &descriptions)
{
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	orb->detect(gray, keypoints);
	orb->compute(gray, keypoints, descriptions);
}
int main(int argc, char** argv)
{
	Mat img1, img2;
	img1 = imread("D:/images/book1.jpg");
	img2 = imread("D:/images/book3.jpg");
	if (img1.empty() || img2.empty())
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	//提取ORB特征点
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptions1, descriptions2;
	//计算ORB特征点
	orb_features(img1, keypoints1, descriptions1);
	orb_features(img2, keypoints2, descriptions2);
	//判断描述子数据类型，如果数据类型不符，那么需要进行类型转换，主要针对ORB特征点
	if ((descriptions1.type() != CV_32F) && (descriptions2.type() != CV_32F))
	{
		descriptions1.convertTo(descriptions1, CV_32F); 
		descriptions2.convertTo(descriptions2, CV_32F);
	}
	//特征点匹配
	vector<DMatch>matches;//定义存放匹配结果的变量
	FlannBasedMatcher matcher;//使用默认值即可
	matcher.match(descriptions1, descriptions2, matches);
	cout << "matches = " << matches.size() << endl;//匹配成功特征点数目
	//寻找距离最大和最小值，如果是ORB特征点，那么min_dist取值要大一些
	double max_dist = 0, min_dist = 100;
	for (int i = 0; i < descriptions1.rows; i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist) min_dist = dist;
		if (dist > max_dist) max_dist = dist;
	}
	cout << "Max dist = " << max_dist << endl;
	cout << "Min dist = " << min_dist << endl;
	//将最大值距离的0.4倍作为最有匹配结果进行筛选
	std::vector<DMatch>good_matches;
	for (int i = 0; i < descriptions1.rows; i++)
	{
		if (matches[i].distance < 0.4*max_dist)
		{
			good_matches.push_back(matches[i]);
		}
	}
	cout << "good_matches = " << good_matches.size() << endl;
	//绘制匹配结果
	Mat outimg1, outimg2;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, outimg1);
	drawMatches(img1, keypoints1, img2, keypoints2, good_matches, outimg2);
	imshow("未筛选结果", outimg1);
	imshow("筛选结果", outimg2);

	waitKey(0);
	return 0;
}
