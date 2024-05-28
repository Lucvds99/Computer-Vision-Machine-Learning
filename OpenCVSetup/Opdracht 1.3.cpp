#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

void main() {

	// Blank Image 
	Mat img(512, 512, CV_8UC3, Scalar(255, 255, 255));

	//Draws different shapes with set colors
	circle(img, Point(150, 400), 100, Scalar(0, 69, 255), FILLED);
	circle(img, Point(350, 400), 100, Scalar(0, 69, 255), FILLED);
	rectangle(img, Point(200, 100), Point(300, 400), Scalar(0, 69, 255), FILLED);
	circle(img, Point(250, 100), 50, Scalar(0, 69, 255), FILLED);
	line(img, Point(250, 50), Point(250, 60), Scalar(255, 255, 255), 2);

	//writes text with specific Font and Color
	putText(img, "Bowling alley with 1 pin", Point(200, 500), FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 0, 0), 2);

	imshow("Image", img);
	waitKey(0);
}