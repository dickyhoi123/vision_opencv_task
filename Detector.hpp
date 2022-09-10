#pragma once
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

class Detector {
private:
	Mat _img;
	vector<Point> _points;

public:
	void set_img(Mat & img);

	vector<Point> detect();

	void print();
};