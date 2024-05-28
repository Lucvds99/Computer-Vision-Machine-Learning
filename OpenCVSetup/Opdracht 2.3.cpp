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



/////////////////  Ilate / erode  //////////////////////

void main() {

	string path = "Resources/Johannusthemannus.png";
	Mat img = imread(path), cannyimg,  dilateimg, erodeimg;

	Canny(img, cannyimg, 150, 200);

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

	//Changes the color space to Gray for a black and white look
	dilate(cannyimg, dilateimg, kernel);
	erode(dilateimg, erodeimg, kernel);

	imshow("canny", cannyimg);
	imshow("default", img);
	imshow("dilate", dilateimg);
	imshow("erode", erodeimg);
	waitKey(0);
}