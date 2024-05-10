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

void main() {

	string path = "Resources/johannusthemannus.png";
	Mat img = imread(path);
	Mat imgResize, imgCrop;

	//resizes the image to 4k resolution
	resize(img, imgResize, Size(3840,2160));

	//sets the area of the crop and crops it to these values
	Rect roi(1500, 0, 400, 300);
	imgCrop = imgResize(roi);

	//makes 3 windows with all the images
	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);
	waitKey(0);
}
