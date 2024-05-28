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



/////////////////  Images  //////////////////////

//void main() {
//
//	string path = "Resources/Johannusthemannus.png";
//	Mat img = imread(path);
//	Mat bw;
//	Mat blur;
//	
//
//	//Changes the color space to Gray for a black and white look
//	cvtColor(img, bw, COLOR_BGR2GRAY);
//
//	
//	GaussianBlur(bw, blur, Size(3, 3), 3, 0);
//
//	imshow("default", img);
//	imshow("bw", bw);
//	imshow("blur", blur);
//	waitKey(0);
//}

/////////////////  Images  //////////////////////

void main() {

	string path = "Resources/Johannusthemannus.png";
	Mat img = imread(path);
	Mat blur;
	Mat blur7;

	//Gives a blur effect over the black and white img with a size of a 3 by 3 matrix
	GaussianBlur(img, blur, Size(7, 7), 3, 0);
	GaussianBlur(img, blur7, Size(7, 7), 7, 0);

	imshow("default", img);
	imshow("blur", blur);
	imshow("blur 7", blur7);
	waitKey(0);
}