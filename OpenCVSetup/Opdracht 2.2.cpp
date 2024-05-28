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
	Mat img = imread(path);
	Mat canny;
	Mat blur;
	

	//Changes the color space to Gray for a black and white look
	Canny(img, canny, 200, 200);

	imshow("default", img);
	imshow("canny", canny);
	waitKey(0);
}