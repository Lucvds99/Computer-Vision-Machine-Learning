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

	//cout << img.size() << endl;
	resize(img, imgResize, Size(3840,2160));

	Rect roi(1500, 0, 400, 300);
	imgCrop = imgResize(roi);

	imshow("Image", img);
	imshow("Image Resize", imgResize);
	imshow("Image Crop", imgCrop);
	waitKey(0);
}
