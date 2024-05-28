#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

#ifdef _DEBUG
#pragma comment ( lib, "opencv_world490d")
#else
#pragma comment( lib, "opencv_world490" )
#endif



/////////////////  Canny  //////////////////////

void main() {

	string path = "Resources/Johannusthemannus.png";
	string hogpath = "hog rider.png";
	Mat hog = imread(hogpath);
	Mat img = imread(path);
	Mat canny, hogcanny;

	int maxthreshold = 0;
	int maxthreshold2 = 0;
	int minthreshold = 0;
	int minthreshold2 = 0;

	namedWindow("Trackbars", (640, 200));
	createTrackbar("Threshold Min", "Trackbars", &minthreshold, 1000);
	createTrackbar("Threshold Max", "Trackbars", &maxthreshold, 1000);
	namedWindow("Trackbars2", (640, 200));
	createTrackbar("Threshold Min", "Trackbars2", &minthreshold2, 1000);
	createTrackbar("Threshold Max", "Trackbars2", &maxthreshold2, 1000);

	while (true)
	{
		//Changes the color space to Gray for a black and white look
		Canny(img, canny, maxthreshold, minthreshold);
		Canny(hog, hogcanny, maxthreshold2, minthreshold2);

		imshow("default", img);
		imshow("default hog", hog);
		imshow("hog", hogcanny);
		imshow("canny", canny);
		waitKey(1);
	}

	

}