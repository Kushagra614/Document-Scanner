#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>

using namespace std;
using namespace cv;

Mat imgOrg, imgGray, imgBlur, imgCanny, imgThre, imgDil, imgErode, imgWarp, imgCrop;
vector<Point>initialPoints, docPoints;

float w = 420, h = 594;


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
		cout << area << endl;

		//string objectType;

		if (area > 1000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);

			if (area > maxArea && conPoly[i].size() == 4) {

				biggest = { conPoly[i][0],conPoly[i][1],conPoly[i][2],conPoly[i][3] };
				maxArea = area;
				//drawContours(imgOrg, conPoly, i, Scalar(255, 0, 255), 1);

			}

		}
	}
	return biggest;
}

void drawPoints(vector<Point>points, Scalar color)
{
	for (int i = 0; i < points.size(); i++)
	{
		circle(imgOrg, points[i], 5, color, FILLED);
		putText(imgOrg, to_string(i), points[i], FONT_HERSHEY_PLAIN, 3, color, 3);
	}
}


vector<Point> reorder(vector<Point>points) {
	vector<Point>newPoints;
	vector<int> sumPoints, subPoints;

	if (points.size() < 4)
	{
		cerr << "Error: not enought points to reorder" << endl;
		return newPoints;
	}

	for (int i = 0; i < 4; i++)
	{
		sumPoints.push_back(points[i].x + points[i].y);
		subPoints.push_back(points[i].x - points[i].y);
	}
	newPoints.push_back(points[min_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // index 0
	newPoints.push_back(points[max_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // index 1
	newPoints.push_back(points[min_element(subPoints.begin(), subPoints.end()) - subPoints.begin()]); // index 2
	newPoints.push_back(points[max_element(sumPoints.begin(), sumPoints.end()) - sumPoints.begin()]); // index 3

	return newPoints;
}

Mat getWarp(Mat img, vector<Point>points, float w, float h)
{
	Point2f src[4] = { points[0],points[1],points[2],points[3] };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	Mat matrix = getPerspectiveTransform(src, dst);
	warpPerspective(imgOrg, imgWarp, matrix, Point(w, h));

	return imgWarp;
}


void main() {

	/*VideoCapture cap(0);
	if (!cap.isOpened()) {
		cerr << "Error: Could not open the camera!" << endl;
		return ;
	}
	cap.read(imgOrg);
	if (imgOrg.empty()) {
		cerr << "Error: Could not capture an image!" << endl;
		return ;
	}*/

	string path = "Resources/paper.jpg";
	imgOrg = imread(path);
	//resize(imgOrg, imgOrg, Size(), 0.5, 0.4); We have removed this as now the img will be cropped in the final img

	//Pre-Processing of the img;

	imgThre = preProcessing(imgOrg);



	// Get Contours: BIGGEST
	initialPoints = getContours(imgThre);
	//drawPoints(initialPoints, Scalar(0, 0, 255));
	docPoints = reorder(initialPoints);
	/*if (initialPoints.size() < 4) {
		cerr << "Error: Not enough points detected for contour approximation." << endl;
		return ;
	}*/
	//drawPoints(docPoints, Scalar(0, 255, 0));

	//warp
	imgWarp = getWarp(imgOrg, docPoints, w, h);

	//crop
	int cropVal = 3;
	Rect roi(cropVal, cropVal, w - cropVal, h - cropVal);
	imgCrop = imgWarp(roi);

	imshow("img", imgOrg);
	imshow("img Dilate", imgThre);
	imshow("img Warp", imgWarp);
	imshow("img Crop", imgCrop);

	waitKey(0);
}