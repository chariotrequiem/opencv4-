#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>

using namespace std;
using namespace cv;

void orb_features(Mat& gray, vector<KeyPoint>& keypoints, Mat& descriptions)
{
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	orb->detect(gray, keypoints);
	orb->compute(gray, keypoints, descriptions);
}

int main(int argc, char** argv)
{
	Mat img1, img2;
	img1 = imread("D:/images/book2.jpg");
	img2 = imread("D:/images/book1.jpg");
	if (img1.empty() || img2.empty())
	{
		cout << "could not laod the src!" << endl;
		return -1;
	}
	//提取ORB特征点
	vector<KeyPoint> keypoints1, keypoints2;
	Mat descriptions1, descriptions2;
	//计算特征点
	orb_features(img1, keypoints1, descriptions1);
	orb_features(img2, keypoints2, descriptions2);
	//特征点匹配
	vector<DMatch>matches;//定义存放匹配结果的变量
	BFMatcher matcher(NORM_HAMMING);//定义特征点匹配的类，使用汉明距离
	matcher.match(descriptions1, descriptions2, matches);//进行特征点匹配
	cout << "matches = " << matches.size() << endl;//匹配成功特征点数目
	//通过汉明距离筛选匹配结果
	double min_dist = 10000, max_dist = 0;
	for (int i = 0; i < matches.size(); i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist)min_dist = dist;
		if (dist > max_dist)max_dist = dist;
	}

	//输出所有匹配结果中最大汉明距离和最小汉明距离
	cout << "min_dist = " << min_dist << endl;
	cout << "max_dist = " << max_dist << endl;
	//将汉明距离较大的匹配点对删除
	vector<DMatch>good_matches;
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance <= max(2 * min_dist, 20.0))
		{
			good_matches.push_back(matches[i]);
		}
	}
	cout << "good_min = " << good_matches.size() << endl;//剩余特征点数目为
	//绘制匹配结果
	Mat outimg, outimg1;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, outimg);
	drawMatches(img1, keypoints1, img2, keypoints2, good_matches, outimg1);
	imshow("未筛选结果", outimg);
	imshow("最小汉明距离筛选", outimg1);

	waitKey(0);
	return 0;
}