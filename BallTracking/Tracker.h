#ifndef TRACKER_H
#define TRACKER_H

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>
#include "helpers2.h"

struct theObject
{
	int xpos;
	int ypos;
	int width;
	int height;
};
void markTheTrackedObject(cv::Mat& cameraFeed, std::string objName, int x, int y);
void searchForMovement(cv::Mat thresholdImage, cv::Mat &cameraFeed, std::string objName, const unsigned int objNum);
void tracker(int iLowH, int iLowS, int iLowV, int iHighH, int iHighS, int iHighV, cv::Mat imgOriginal, std::string objName, const unsigned int objNum);
void createControlMenu(int &iLowH, int &iLowS, int &iLowV, int &iHighH, int &iHighS, int &iHighV);

#endif