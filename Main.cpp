#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat imgOrg, imgGrey, imgCanny;

void main() {
	string path = "Resources/paper.jpg";
	imgOrg = imread(path);
	resize(imgOrg, imgOrg, Size(), 0.5, 0.4);

	//Pre-Processing of the img
	imshow("img", imgOrg);
	waitKey(0);
}