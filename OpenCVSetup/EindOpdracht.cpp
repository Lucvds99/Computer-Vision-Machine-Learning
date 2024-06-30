#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

///////////////  Project 3 - License Plate Detector //////////////////////


void getContours(Mat imgDil, Mat img) {

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
	vector<vector<Point>> conPoly(contours.size());

	vector<Rect> boundRect(contours.size());

	for (int i = 0; i < contours.size(); i++)
	{
		int area = contourArea(contours[i]);
		cout << area << endl;
		string objectType;

		if (area > 20000)
		{
			float peri = arcLength(contours[i], true);
			approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
			boundRect[i] = boundingRect(conPoly[i]);
			int objCor = (int)conPoly[i].size();
			if (objCor == 3) { objectType = "triangle"; }
			else if (objCor == 4)
			{
				float aspRatio = (float)boundRect[i].width / (float)boundRect[i].height;
				if (aspRatio > 0.95 && aspRatio < 1.05) { objectType = "scuare"; }
				else { objectType = "rectangle"; }
			}
			else if (objCor > 4) { objectType = "circle"; }
			drawContours(img, conPoly, i, Scalar(255, 0, 255), 2, 8, hierarchy);
			rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
			putText(img, objectType, { boundRect[i].x,boundRect[i].y - 5 }, FONT_HERSHEY_PLAIN, 1, Scalar(0, 69, 255), 2);
		}


	}
}

void main() {

	VideoCapture cap(1);

	CascadeClassifier plateCascade;
	plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

	if (plateCascade.empty()) { cout << "XML file not loaded" << endl; }

	string path = "Resources/cars/bently.jpg";
	Mat img = imread(path);



	vector<Rect> plates;

	plateCascade.detectMultiScale(img, plates, 1.1, 10);

	for (int i = 0; i < plates.size(); i++)
	{
		Mat imgCrop = img(plates[i]);
		//imshow(to_string(i), imgCrop);
		imwrite("Resources/Plates/" + to_string(i) + ".png", imgCrop);
		rectangle(img, plates[i].tl(), plates[i].br(), Scalar(255, 0, 255), 3);

		imshow("crop",imgCrop);

		Mat imgGray, imgBlur, imgCanny, imgDil, imgErode, imgResize, erodeimg;

		Mat capturedPlate = imgCrop;
		imshow("captured plate", capturedPlate);

		Mat kernel = getStructuringElement(MORPH_RECT, Size(21, 21));
		Mat erodekernel = getStructuringElement(MORPH_RECT, Size(29, 29));


		resize(capturedPlate, imgResize, Size(2840, 1160));


		cvtColor(imgResize, imgGray, COLOR_BGR2GRAY);
		GaussianBlur(imgGray, imgBlur, Size(0, 0), 3, 0);
		imshow("blur", imgBlur);
		dilate(imgBlur, imgDil, kernel);
		imshow("dil1", imgDil);
		erode(imgDil, erodeimg, erodekernel);
		imshow("erode", erodeimg);
		Canny(erodeimg, imgCanny, 10, 40);
		imshow("canny", imgCanny);
		kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
		dilate(imgCanny, imgDil, kernel);
		imshow("dil2", imgDil);


		getContours(imgDil, imgResize);

		imshow("Image", imgResize);
	}



	
	waitKey(0);
}