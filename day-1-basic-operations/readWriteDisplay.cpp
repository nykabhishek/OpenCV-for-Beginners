/*
Copyright 2017 BIG VISION LLC ALL RIGHTS RESERVED

This code is made available to the students of 
the online course titled "OpenCV for Beginners" 
by Satya Mallick for personal non-commercial use. 

Sharing this code is strictly prohibited without written
permission from Big Vision LLC. 

For licensing and other inquiries, please email 
spmallick@bigvisionllc.com 
*/

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

int main(void)
{
	Mat image;
	// Read the file "image.jpg".
 	// This file "image.jpg" should be in the project folder.
	// Else provide full path: "D:/images/image.jpg"
	String imageName( "sample.jpg" ); // by default
 
	// LOAD image
	image = imread(imageName, IMREAD_COLOR);

	if(image.empty()) // Check for invalid input
	{
		cout <<  "Could not open or find the image" << std::endl ;
		return -1;
	}

	Mat grayImage;
	// convert color image to gray
	cvtColor(image, grayImage, COLOR_BGR2GRAY);

	// DISPLAY image
	// Create a window for display.
	namedWindow("image", WINDOW_AUTOSIZE);
	namedWindow("gray image", WINDOW_NORMAL);

	// Show our image inside it.
	imshow("image", image);
	imshow("gray image", grayImage);
	// Both images are displayed but gray image on top of original image
	// Move gray image window to see original image

	// SAVE image
	imwrite("result.jpg", image);  // it will store the image with name "result.jpg"
	imwrite("result_gray.jpg", grayImage); // it will store the gray image with name "result_gray.jpg"

	waitKey(0);  // Wait for a keystroke in the window
	return 0;
}