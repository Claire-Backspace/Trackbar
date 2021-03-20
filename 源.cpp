#include<iostream>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
using namespace cv;
using namespace std;
vector<vector<Point>>contours;
vector<Vec4i>hierarchy;
const int max_value_H = 360 / 2;
const int max_value = 255;
int low_H = 0, low_S = 0, low_V = 0;
int high_H = max_value_H, high_S = max_value, high_V = max_value;
//ÑÕÉ«Çø¼ä
String HSVname = "HSV";
Mat clo_HSV, clo_threshold;
Mat element = getStructuringElement(MORPH_RECT, Size(1, 1));

static void on_low_H_thresh_trackbar(int, void*)
{
	low_H = min(high_H - 1, low_H);
	setTrackbarPos("Low H", HSVname, low_H);
}
static void on_high_H_thresh_trackbar(int, void*)
{
	high_H = max(high_H, low_H + 1);
	setTrackbarPos("High H", HSVname, high_H);
}
static void on_low_S_thresh_trackbar(int, void*)
{
	low_S = min(high_S - 1, low_S);
	setTrackbarPos("Low S", HSVname, low_S);
}
static void on_high_S_thresh_trackbar(int, void*)
{
	high_S = max(high_S, low_S + 1);
	setTrackbarPos("High S", HSVname, high_S);
}
static void on_low_V_thresh_trackbar(int, void*)
{
	low_V = min(high_V - 1, low_V);
	setTrackbarPos("Low V", HSVname, low_V);
}
static void on_high_V_thresh_trackbar(int, void*)
{
	high_V = max(high_V, low_V + 1);
	setTrackbarPos("High V", HSVname, high_V);
}


int main(int argc, char* argv[])
{
	VideoCapture capture(1);
	Mat src;
	while (1)
	{
		capture >> src;
		//namedWindow("thr");
		//Mat hsv, dst;
		//inRange(hsv, Scalar(55, 184, 170), Scalar(89, 245, 255), dst); filter green
		//inRange(hsv, Scalar(17, 125, 132), Scalar(32, 245, 255), dst);filter yellow
		//inRange(hsv, Scalar(),Scalar(),dst)filter gray;
		

		createTrackbar("Low H", HSVname, &low_H, max_value_H, on_low_H_thresh_trackbar);
		createTrackbar("High H", HSVname, &high_H, max_value_H, on_high_H_thresh_trackbar);
		createTrackbar("Low S", HSVname, &low_S, max_value, on_low_S_thresh_trackbar);
		createTrackbar("High S", HSVname, &high_S, max_value, on_high_S_thresh_trackbar);
		createTrackbar("Low V", HSVname, &low_V, max_value, on_low_V_thresh_trackbar);
		createTrackbar("High V", HSVname, &high_V, max_value, on_high_V_thresh_trackbar);

		// Convert from BGR to HSV colorspace
		cvtColor(src, clo_HSV, COLOR_BGR2HSV);
		// Detect the object based on HSV Range Values
		inRange(clo_HSV, Scalar(low_H, low_S, low_V), Scalar(high_H, high_S, high_V), clo_threshold);
		// Show the frames
		namedWindow("src", WINDOW_GUI_NORMAL);
		namedWindow(HSVname, WINDOW_GUI_NORMAL);
		imshow(HSVname, clo_threshold);
		imshow("dst", clo_threshold);

		imshow("capture", src);

		char(key) = (char)waitKey(1);
		if (key == 27)
			break;
	}

	return 0;
}

