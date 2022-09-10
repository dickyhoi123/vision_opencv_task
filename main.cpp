#include <iostream>
#include "Detector.hpp"

using namespace std;
using namespace cv;


int main() {
	Detector D;

	vector<Point> points;

	Mat img = imread("resources/task.jpg");
	D.set_img(img);
	points = D.detect();
	D.print();

	for (int i = 0; i < points.size(); i++) {
		circle(img, points[i], 3, Scalar(0, 255, 0), FILLED);
	}

	imshow("img", img);
	waitKey(0);
	


	system("pause");
	return 0;
}