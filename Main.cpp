#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat imgOrg, imgGray,imgBlur,imgCanny,imgThre,imgDil,imgErode;
vector<Point>intialPoints;


Mat preProcessing(Mat img)
{
	cvtColor(imgOrg, imgGray, COLOR_BGR2GRAY);
	GaussianBlur(imgGray, imgBlur, Size(3, 3), 3, 0);
	Canny(imgBlur, imgCanny, 25, 75);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	dilate(imgCanny, imgDil, kernel);
	erode(imgDil, imgErode, kernel);

	return imgErode;
}

	vector<Point> getContours(Mat image)
{
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>>conPoly(contours.size());
	vector<Rect>boundRect(contours.size());

	vector<Point>biggest;
	int maxArea = 0;

	for (int i = 0; i < contours.size(); i++) {
		int area = contourArea(contours[i]);
		cout << area<<endl;

		string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i]);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size()==4) {

				biggest = { conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3] };
				maxArea = area;
				
			}
			drawContours(imgOrg, conPoly, i, Scalar(255, 0, 255), 2);
		}
	}
	return biggest;
}

	void drawPoints(vector<Point>points, Scalar color)
	{
		for (int i = 0; i < points.size(); i++)
		{
			circle(imgOrg, points[i], 30, color, FILLED);
			putText(imgOrg, to_string(i), points[i], FONT_HERSHEY_PLAIN, 5, color, 5);
		}
	}

void main() {
	string path = "Resources/paper.jpg";
	imgOrg = imread(path);
	resize(imgOrg, imgOrg, Size(), 0.5, 0.4);

	//Pre-Processing of the img;
	
	imgThre = preProcessing(imgOrg);



	// Get Contours: BIGGEST
	intialPoints = getContours(imgThre);

	//warp


	imshow("img", imgOrg);
	imshow("img Dilate", imgThre);
	waitKey(0);
}