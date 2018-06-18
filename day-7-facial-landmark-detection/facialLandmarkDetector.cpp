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


#include <dlib/opencv.h>
#include <dlib/image_processing.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <opencv2/opencv.hpp>

using namespace dlib;
using namespace std;
using namespace cv;

// Write landmarks to file
void writeLandmarksToFile(full_object_detection &landmarks, const string &filename)
{
  // Open file
	std::ofstream ofs;
	ofs.open(filename);
  
  // Loop over all landmark points
  for (int i = 0; i < landmarks.num_parts(); i++)
	{
    // Print x and y coordinates to file
		ofs << landmarks.part(i).x() << " " << landmarks.part(i).y() << endl;

	}
  // Close file
	ofs.close();
} 

void drawLandmarks(Mat &im, full_object_detection landmarks )
{
  for(int i = 0; i < landmarks.num_parts(); i++)
  {
    int px = landmarks.part(i).x();
    int py = landmarks.part(i).y();

    char landmark_index[3];
    sprintf(landmark_index, "%d", i+1);

    circle(im, Point(px, py), 1, Scalar(0, 0, 255), 2, CV_AA);
    putText(im, landmark_index, Point(px, py), FONT_HERSHEY_SIMPLEX, .3, Scalar(255, 0, 0), 1);
  }
}

int main(int argc, char** argv)
{  
  
  // Get the face detector
  frontal_face_detector faceDetector = get_frontal_face_detector();

  // The landmark detector is implemented in the shape_predictor class
  shape_predictor landmarkDetector;

  // Load the landmark model
  deserialize("shape_predictor_68_face_landmarks.dat") >> landmarkDetector;

  // Read Image
  string imageFilename("girl.jpg");
  cv::Mat im = cv::imread(imageFilename);
  
  // landmarks will be stored in results/famil_0.txt
  string landmarksBasename("output_cpp");
  
  // Convert OpenCV image format to Dlib's image format
  cv_image<bgr_pixel> dlibIm(im);

  // Detect faces in the image
  std::vector<dlib::rectangle> faceRects = faceDetector(dlibIm);
  cout << "Number of faces detected: " << faceRects.size() << endl;

  // Vector to store landmarks of all detected faces
  std::vector<full_object_detection> landmarksAll;

  // Loop over all detected face rectangles
  for (int i = 0; i < faceRects.size(); i++)
  {
    // For every face rectangle, run landmarkDetector
    full_object_detection landmarks = landmarkDetector(dlibIm, faceRects[i]);
    
    // Print number of landmarks
    if (i == 0) cout << "Number of landmarks : " << landmarks.num_parts() << endl;
    
    // Store landmarks for current face
    landmarksAll.push_back(landmarks);
    
    // Draw landmarks on face
    drawLandmarks(im, landmarks);

    // Write landmarks to disk
    std::stringstream landmarksFilename;
    landmarksFilename << landmarksBasename <<  "_"  << i << ".txt";
    cout << "Saving landmarks to " << landmarksFilename.str() << endl;
    writeLandmarksToFile(landmarks, landmarksFilename.str());
    
  }
  
  // Save image
  string outputFilename("result_cpp_Landmarks.jpg");
  cout << "Saving output image to " << outputFilename << endl;
  cv::imwrite(outputFilename, im);
  
  // Display image
  cv::imshow("Facial Landmark Detector", im);
  cv::waitKey(0);
  
  return EXIT_SUCCESS;
}

