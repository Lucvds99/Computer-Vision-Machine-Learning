#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>
#include <algorithm> // for std::sort

using namespace cv;
using namespace std;

// Define the struct
struct Rectstruct {
    Rect boundRect;
    int Xposition;

    // Constructor to initialize the struct
    Rectstruct(Rect rect, int pos) : boundRect(rect), Xposition(pos) {}
};

// Comparator function to sort based on 'Xposition'
bool compareByPosition(const Rectstruct& a, const Rectstruct& b) {
    return a.Xposition < b.Xposition; // Ascending order
}

void getContours(Mat imgDil, Mat img) {
    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    findContours(imgDil, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    vector<vector<Point>> conPoly(contours.size());
    vector<Rect> boundRect(contours.size());
    vector<Rectstruct> Rectstructs;

    for (size_t i = 0; i < contours.size(); i++) {
        int area = contourArea(contours[i]);
        cout << "Area: " << area << endl;

        if (area > 20000 && area < 150000) {
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02 * peri, true);
            boundRect[i] = boundingRect(conPoly[i]);
            rectangle(img, boundRect[i].tl(), boundRect[i].br(), Scalar(0, 255, 0), 5);
            Mat numbCrop = img(boundRect[i]);

            Rectstruct rectStruct(boundRect[i], boundRect[i].x);
            Rectstructs.push_back(rectStruct);
        }
    }

    // Sort Rectstructs based on Xposition
    std::sort(Rectstructs.begin(), Rectstructs.end(), compareByPosition);
    int counter = 0;

    for (const auto& rect : Rectstructs) {
        Mat imgCrop = img(rect.boundRect);
        imwrite("Resources/Plates/PlateNumber_" + to_string(counter++) + ".png", imgCrop);
    }
}

int main() {
    VideoCapture cap(1);

    CascadeClassifier plateCascade;
    plateCascade.load("Resources/haarcascade_russian_plate_number.xml");

    if (plateCascade.empty()) {
        cout << "XML file not loaded" << endl;
        return -1;
    }

    string path = "Resources/cars/bently.jpg";
    Mat img = imread(path);

    vector<Rect> plates;
    plateCascade.detectMultiScale(img, plates, 1.1, 10);

    for (size_t i = 0; i < plates.size(); i++) {
        Mat imgCrop = img(plates[i]);

        Mat imgGray, imgBlur, imgCanny, imgDil, imgResize, erodeimg;
        Mat capturedPlate = imgCrop;

        Mat kernel = getStructuringElement(MORPH_RECT, Size(21, 21));
        Mat erodekernel = getStructuringElement(MORPH_RECT, Size(29, 29));

        resize(capturedPlate, imgResize, Size(2840, 1160));
        cvtColor(imgResize, imgGray, COLOR_BGR2GRAY);
        GaussianBlur(imgGray, imgBlur, Size(0, 0), 3, 0);
        dilate(imgBlur, imgDil, kernel);
        erode(imgDil, erodeimg, erodekernel);
        Canny(erodeimg, imgCanny, 10, 40);
        kernel = getStructuringElement(MORPH_RECT, Size(7, 7));
        dilate(imgCanny, imgDil, kernel);

        getContours(imgDil, imgResize);
        resize(imgResize, imgResize, Size(1920, 1080));

        imshow("Image", imgResize);
    }

    waitKey(0);
    return 0;
}
