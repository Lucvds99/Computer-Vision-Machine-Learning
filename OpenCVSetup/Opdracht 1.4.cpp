#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;
using namespace std;

///////////////  Warp Images  //////////////////////

void main() {

	string path = "Resources/laptop.jpg";
	Mat img = imread(path);
	Mat matrix, imgWarp, imgResize;
	float w = 500, h = 350;

	Point2f src[4] = { {102,700},{2489,194},{690,2445},{3800,1075} };
	Point2f dst[4] = { {0.0f,0.0f},{w,0.0f},{0.0f,h},{w,h} };

	matrix = getPerspectiveTransform(src, dst);
	warpPerspective(img, imgWarp, matrix, Point(w, h));

	for (int i = 0; i < 4; i++)
	{
		circle(img, src[i], 10, Scalar(0, 0, 255), FILLED);
	}

	//resizes the image to 4k resolution
	resize(img, imgResize, Size(1990, 1080));

	imshow("Image", imgResize);
	imshow("Image Warp", imgWarp);
	waitKey(0);

}