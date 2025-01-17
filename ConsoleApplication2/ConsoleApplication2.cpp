#include "stdafx.h"
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>	
#include <string.h>

using namespace cv;
using namespace std;
using std::cout;

//declaration variable save image
int ct = 0, c = 1;
char filename[100];

//declaration variable max of Track
const int brightness_track_max = 100;
const int contrast_track_max = 100;
const int saturation_track_max = 100;
const int hue_track_max = 100;

//declaration variable of Track value and default
int brightness_track, default_brightness_track;
int contrast_track, default_contrast_track;
int saturation_track, default_saturation_track;
int hue_track, default_hue_track;

//	open the default camera
VideoCapture cap(0);

//create function for capture set
static void on_trackbar(int, void*)
{
	//set Brightness
	cap.set(CAP_PROP_BRIGHTNESS, brightness_track);
	//set Contrast
	cap.set(CAP_PROP_CONTRAST, contrast_track);
	//set Saturation
	cap.set(CAP_PROP_SATURATION, saturation_track);
	//set Hue
	cap.set(CAP_PROP_HUE, hue_track);
}

//main function
int main(int argc, char** argv)
{
	if (!cap.isOpened()) // check if we	succeeded
		return -1;

	//Set Default Value of Track
	brightness_track = 50;
	contrast_track = 50;
	saturation_track = 50;
	hue_track = 50;

	//Save to Default Variable
	default_brightness_track = brightness_track;
	default_contrast_track = contrast_track;
	default_saturation_track = saturation_track;
	default_hue_track = hue_track;

	//create new window for Track
	namedWindow("Live Adjustment", WINDOW_AUTOSIZE); // Create Window

	//create Track
	createTrackbar("Brightness", "Live Adjustment", &brightness_track, brightness_track_max, on_trackbar);
	createTrackbar("Contrast", "Live Adjustment", &contrast_track, contrast_track_max, on_trackbar);
	createTrackbar("Saturation", "Live Adjustment", &saturation_track, saturation_track_max, on_trackbar);
	createTrackbar("Hue", "Live Adjustment", &hue_track, hue_track_max, on_trackbar);

	//call on_trackbar fuction for push value
	on_trackbar(brightness_track, 0);
	on_trackbar(contrast_track, 0);
	on_trackbar(saturation_track, 0);
	on_trackbar(hue_track, 0);

	//set Width Resolution
	int dWidth = cap.set(CAP_PROP_FRAME_WIDTH, 640);
	//set Height Resolution
	int dHeight = cap.set(CAP_PROP_FRAME_HEIGHT, 480);

	//get width
	int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	//get width
	int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);

	//print on terminal
	printf("WIDTH = %d\n", frame_width);
	printf("HEIGHT = %d\n", frame_height);
	printf("-----------------------------------\n");
	printf("Default Brightness----------> %d\n", default_brightness_track);
	printf("Default Contrast------------> %d\n", default_contrast_track);
	printf("Default Saturation----------> %d\n", default_saturation_track);
	printf("Default Hue-----------------> %d\n", default_hue_track);
	printf("-----------------------------------\n");
	printf("Press S for Save Image\n");

	//close loop
	for (;;)
	{
		Mat frame;
		cap >> frame;
		imshow("Live Adjustment", frame);

		//if 's' from keyboard is pressed
		if (waitKey(30) == 's') {
			sprintf_s(filename, "Snap_%d.jpg", c); //save with name "Snap_..."
			waitKey(10);
			imshow("Live Adjustment", frame);
			imwrite(filename, frame); //save or write to image
			printf("Image saved : Snap_%d\n",c);
			c++;
		}

		//if 'ESC' from keyboard is pressed
		if (waitKey(1) == 27) break;

	}
	return 0;
}
