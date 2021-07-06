#include<iostream>
#include<opencv2/opencv.hpp>
#include<vector>
using namespace std;
using namespace cv;
void match_min(vector<DMatch> matches, vector<DMatch>& good_matches)
{
	double min_dist = 10000, max_dist = 0;
	for (int i = 0; i < matches.size(); i++)
	{
		double dist = matches[i].distance;
		if (dist < min_dist)min_dist = dist;
		if (dist > max_dist)max_dist = dist;
	}
	cout << "min_dist = " << min_dist << endl;
	cout << "max_dist = " << max_dist << endl;
	for (int i = 0; i < matches.size(); i++)
	{
		if (matches[i].distance <= max(2 * min_dist, 20.0))
			good_matches.push_back(matches[i]);
	}
}

//RANSAC�㷨ʵ��
void ransac(vector<DMatch>matches, vector<KeyPoint>queryKeyPoint, vector<KeyPoint>trainKeyPoint, vector<DMatch>& matches_ransac)
{
	//���屣��ƥ��������
	vector<Point2f>srcPoints(matches.size()), dstPoints(matches.size());
	//����ӹؼ�������ȡ����ƥ���Ե�����
	for (int i = 0; i < matches.size(); i++)
	{
		srcPoints[i] = queryKeyPoint[matches[i].queryIdx].pt;
		dstPoints[i] = trainKeyPoint[matches[i].trainIdx].pt;
	}

	//ƥ���Խ���RANSAC����
	vector<int>inliersMask(srcPoints.size());
	//Mat homography;
	//homography = findHomography(srcPoints, dstPoints, RANSAC, 5, inliersMask);
	findHomography(srcPoints, dstPoints, RANSAC, 5, inliersMask);
	//�ֶ�����RANSAC���˺��ƥ����
	for (int i = 0; i < inliersMask.size(); i++)
	{
		if (inliersMask[i])
			matches_ransac.push_back(matches[i]);
	}
}

void orb_features(Mat &gray, vector<KeyPoint>& keypoints, Mat& descriptions)
{
	Ptr<ORB> orb = ORB::create(1000, 1.2f);
	orb->detect(gray, keypoints);
	orb->compute(gray, keypoints, descriptions);
}
int main(int argc, char** argv)
{
	Mat img1 = imread("D:/images/book1.jpg");
	Mat img2 = imread("D:/images/books.jpg");
	if (!(img1.data && img2.data))
	{
		cout << "could not load the src!" << endl;
		return -1;
	}
	//��ȡORB������
	vector<KeyPoint>keypoints1, keypoints2;
	Mat descriptions1, descriptions2;
	//��������ָ��ORB��������ȡ
	orb_features(img1, keypoints1, descriptions1);
	orb_features(img2, keypoints2, descriptions2);
	//������ƥ��
	vector<DMatch>matches, good_min, good_ransac;
	BFMatcher matcher(NORM_HAMMING);
	matcher.match(descriptions1, descriptions2, matches);
	cout << "matches = " << matches.size() << endl;

	//��С��������
	match_min(matches, good_min);
	cout << "good_min = " << good_min.size() << endl;

	//��RANSAC�㷨ɸѡƥ����
	ransac(good_min, keypoints1, keypoints2, good_ransac);
	cout << "good_matches.size = " << good_ransac.size() << endl;

	//����ƥ����
	Mat outimg, outimg1, outimg2;
	drawMatches(img1, keypoints1, img2, keypoints2, matches, outimg);
	drawMatches(img1, keypoints1, img2, keypoints2, good_min, outimg1);
	drawMatches(img1, keypoints1, img2, keypoints2, good_ransac, outimg2);
	imshow("δɸѡ���", outimg);
	imshow("��С��������ɸѡ", outimg1);
	imshow("RANSACɸѡ", outimg2);

	waitKey(0);
	return 0;
}