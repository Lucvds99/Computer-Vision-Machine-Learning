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

	rectangle(img, Point(200, 50), Point(300, 500), Scalar(139, 188, 216), FILLED);
	
	for (int x = 210; x < 300; x += 10) {
		line(img, Point(x, 50), Point(x, 500), Scalar(0, 0, 0), 1);
	}
	circle(img, Point(260, 250), 15, Scalar(0, 127, 14), FILLED);

	

	//writes text with specific Font and Color
	putText(img, "Bowling alley with 0 pins", Point(200, 500), FONT_HERSHEY_DUPLEX, 0.75, Scalar(0, 0, 0), 2);

	imshow("Image", img);
	waitKey(0);
}