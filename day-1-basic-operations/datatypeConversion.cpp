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
  Mat source;

  // Scale will convert pixel values
  double scale=1/255.0;
  double shift=0;

  // Read image
  source= imread("sample.jpg",1);

  //Converting from unsigned char to float(32bit)
  source.convertTo(source, CV_32FC3, scale, shift);

  //Converting from float to unsigned char
  source.convertTo(source, CV_8UC3, 1.0/scale, shift);
  cout << "Nothing to Display" << endl;
}
