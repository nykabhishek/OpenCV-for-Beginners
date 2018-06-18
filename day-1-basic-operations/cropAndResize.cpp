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


#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(void)
{
Mat source, scaleDown, scaleUp;

// Read source image
source = imread("sample.jpg",1);

// Scaling factors
double scaleX = 0.6;
double scaleY = 0.6;

// Scaling down the image 0.6 times
cv::resize(source, scaleDown, Size(), scaleX, scaleY, INTER_LINEAR );
// Scaling up the image 1.8 times
cv::resize(source,scaleUp,Size(), scaleX*3, scaleY*3, INTER_LINEAR );

//Cropped image
Mat crop = source(cv::Range(50,150), cv::Range(20, 200));

// Create Display windows for all three images
namedWindow("Original", WINDOW_AUTOSIZE);
namedWindow("Scaled Down", WINDOW_AUTOSIZE);
namedWindow("Scaled Up", WINDOW_AUTOSIZE);
namedWindow("Cropped Image", WINDOW_AUTOSIZE);

// Show images
imshow("Original", source);
imshow("Scaled Down", scaleDown);
imshow("Scaled Up", scaleUp);
imshow("Cropped Image", crop);

waitKey(0);

}

