#include "Tracker.h"

void markTheTrackedObject(cv::Mat& cameraFeed, std::string objName, int x, int y)
{
	cv::circle(cameraFeed, cv::Point(x, y), 20, cv::Scalar(0, 255, 0), 2);
	cv::line(cameraFeed, cv::Point(x, y), cv::Point(x, y - 25), cv::Scalar(0, 255, 0), 2);
	cv::line(cameraFeed, cv::Point(x, y), cv::Point(x, y + 25), cv::Scalar(0, 255, 0), 2);
	cv::line(cameraFeed, cv::Point(x, y), cv::Point(x + 25, y), cv::Scalar(0, 255, 0), 2);
	cv::line(cameraFeed, cv::Point(x, y), cv::Point(x - 25, y), cv::Scalar(0, 255, 0), 2);
	cv::putText(cameraFeed, objName.c_str(), cv::Point(x, y), 1, 1, cv::Scalar(0, 0, 255), 2);
}
void searchForMovement(cv::Mat thresholdImage, cv::Mat &cameraFeed, std::string objName, const unsigned int objNum)
{
	cv::Mat temp;
	thresholdImage.copyTo(temp); 
	
	bool objectDetected = false;
	std::vector<theObject> teamObjects(objNum*2);
	//std::vector<int> xpos(objNum), ypos(objNum);
	std::vector<std::vector<cv::Point>> contours;
	std::vector<cv::Vec4i> hierarchy;

	cv::findContours(temp, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	if (contours.size() > 0) objectDetected = true;
	else objectDetected = false;

	if (objectDetected)
	{
		for (unsigned int c = 0; c < objNum*2; c++)
		{
			if (contours.size()> c){
				cv::Rect objectBoundingRectangle = cv::Rect(0, 0, 0, 0);
				std::vector<std::vector<cv::Point>> ConVec;
				ConVec.push_back(contours.at(contours.size() - 1 - c));
				objectBoundingRectangle = cv::boundingRect(ConVec.at(0));
				//xpos[c] = objectBoundingRectangle.x + objectBoundingRectangle.width / 2;
				//ypos[c] = objectBoundingRectangle.y + objectBoundingRectangle.height / 2;
				theObject tempObj;
				tempObj.xpos = objectBoundingRectangle.x;
				tempObj.ypos = objectBoundingRectangle.y;
				tempObj.width = objectBoundingRectangle.width;
				tempObj.height = objectBoundingRectangle.width;
				teamObjects[c] = tempObj;
			}
			else break;
			//markTheTrackedObject(cameraFeed, objName + "_" + int2string(c), xpos[c], ypos[c]);
			markTheTrackedObject(cameraFeed, objName + "_" + int2string(c), teamObjects[c].xpos, teamObjects[c].ypos);
		}
	}
}

void tracker(int iLowH, int iLowS, int iLowV, int iHighH, int iHighS, int iHighV, cv::Mat imgOriginal, std::string objName, const unsigned int objNum)
{
	cv::Mat imgHSV, imgThresholded;
	cv::cvtColor(imgOriginal, imgHSV, cv::COLOR_BGR2HSV);
	cv::inRange(imgHSV, cv::Scalar(iLowH, iLowS, iLowV), cv::Scalar(iHighH, iHighS, iHighV), imgThresholded);
	//opening
	cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement((cv::MORPH_ELLIPSE), cv::Size(5, 5)));
	cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement((cv::MORPH_ELLIPSE), cv::Size(5, 5)));
	//cloasing
	cv::dilate(imgThresholded, imgThresholded, cv::getStructuringElement((cv::MORPH_ELLIPSE), cv::Size(25, 25)));
	cv::erode(imgThresholded, imgThresholded, cv::getStructuringElement((cv::MORPH_ELLIPSE), cv::Size(25, 25)));

	searchForMovement(imgThresholded, imgOriginal, objName.c_str(), objNum);

	cv::imshow("Thresholded Image" + objName, imgThresholded);
}

void createControlMenu(int &iLowH, int &iLowS, int &iLowV, int &iHighH, int &iHighS, int &iHighV)
{
	cv::namedWindow("Control", CV_WINDOW_NORMAL);

	cv::createTrackbar("LowH", "Control", &iLowH, 179);
	cv::createTrackbar("HighH", "Control", &iHighH, 179);

	cv::createTrackbar("LowS", "Control", &iLowS, 255);
	cv::createTrackbar("HighS", "Control", &iHighS, 255);

	cv::createTrackbar("LowV", "Control", &iLowV, 255);
	cv::createTrackbar("HighV", "Control", &iHighV, 255);
}
