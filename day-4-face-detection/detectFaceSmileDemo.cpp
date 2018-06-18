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


#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

/** Global variables */
String faceCascadePath, smileCascadePath;
CascadeClassifier faceCascade, smileCascade;

int main( int argc, const char** argv )
{
  int smileNeighborsMax = 100;
  int neighborStep = 2;

  faceCascadePath = "models/haarcascade_frontalface_default.xml";
  smileCascadePath = "models/haarcascade_smile.xml";

  //-- 1. Load the cascades
  if( !faceCascade.load( faceCascadePath ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
  if( !smileCascade.load( smileCascadePath ) ){ printf("--(!)Error loading smile cascade\n"); return -1; };

  std::vector<Rect> faces;

  Mat frame = imread("hillary_clinton.jpg");
  Mat frameGray, frameClone;
  cvtColor(frame, frameGray, COLOR_BGR2GRAY);

  faceCascade.detectMultiScale( frameGray, faces, 1.4, 5);

  for ( size_t i = 0; i < faces.size(); i++ )
  {
    int x = faces[i].x;
    int y = faces[i].y;
    int w = faces[i].width;
    int h = faces[i].height;

    rectangle(frame, Point(x, y), Point(x + w, y + h), Scalar(255,0,0), 2, 4);

    Mat faceROI = frameGray( faces[i] );
    for (int neigh = 0; neigh < smileNeighborsMax; neigh = neigh + neighborStep)
    {
      std::vector<Rect> smile;

      Mat frameClone = frame.clone();
      Mat faceROIClone = frameClone( faces[i] );
      //-- In each face, detect smile
      smileCascade.detectMultiScale( faceROI, smile, 1.5, neigh);

      for ( size_t j = 0; j < smile.size(); j++ )
      {
        int smileX = smile[j].x;
        int smileY = smile[j].y;
        int smileW = smile[j].width;
        int smileH = smile[j].height;

        rectangle(faceROIClone, Point(smileX, smileY), Point(smileX + smileW, smileY + smileH), Scalar(0,255,0), 2, 4);
      }

      putText(frameClone, format("# Neighbors = %d",neigh), Point(10, 50), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 255), 4);
      imshow( "Face and Smile Demo", frameClone );
      int k = waitKey(500);
      if(k ==  27)
      {
        destroyAllWindows();
        break;
      }  
    }
  }
}