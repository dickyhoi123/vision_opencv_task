#include "Detector.hpp"
#include <iostream>


using namespace cv;
using namespace std;

bool comp(vector<Point> a, vector<Point> b) {
	return a.size() < b.size();
}

void Detector::set_img(Mat &img) {
	_img = img.clone();
}

vector<Point> Detector::detect() {
	vector<vector<Point>> contours;
	
	vector<Vec4i> hierarchy;

	cvtColor(_img, _img, COLOR_BGR2GRAY);
	GaussianBlur(_img,_img, Size(5, 5), 5, 0);
	Canny(_img, _img, 35, 85);
	Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
	dilate(_img, _img, kernel);
	findContours(_img, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

	vector<vector<Point>> conPoly(contours.size());

	for (int i = 0; i < contours.size(); i++) {
		if (contourArea(contours[i]) > 500) {
			float peri = arcLength(contours[i],true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
		}
	}

	sort(conPoly.begin(),conPoly.end(),comp);

	for (int i = 0; i < conPoly.size(); i++) {
		Point p;
		for (int j = 0; j < conPoly[i].size(); j++) {
			p.x += conPoly[i][j].x / conPoly[i].size();
			p.y += conPoly[i][j].y / conPoly[i].size();
		}
		_points.push_back(p);
	}

	return _points;
}

void  Detector::print() {
		cout << "三角形: " << "x:" << _points[0].x << ", y:" << _points[0].y << endl;
		cout << "正方形: " << "x:" << _points[1].x << ", y:" << _points[1].y << endl;
		cout << "圓形: " << "x:" << _points[2].x << ", y:" << _points[2].y << endl;
}

