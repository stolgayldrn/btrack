#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <string>
#include <iostream>
#include "helpers2.h"
#include "Tracker.h"

 int main(int argc, char* argv[])
{
	cv::VideoCapture cap(1);

	if (!cap.isOpened())
	{
		std::cout << "Cannot open the web cam" << std::endl;
		return -1;
	}

	while (true)
	{
		cv::Mat imgOriginal;
		bool bSuccess = cap.read(imgOriginal);
		if (!bSuccess)
		{
			std::cout << "Cannot read a frame from video" << std::endl;
			break;
		}
		
		tracker(95, 115, 115, 115, 155, 155, imgOriginal, "Blue", 10);
		tracker(0, 170, 130, 4, 255, 255, imgOriginal, "RedLight", 10);
		tracker(170, 110, 110, 179, 255, 255, imgOriginal, "RedDark", 10);
	
		cv::imshow("Original", imgOriginal);

		if (cv::waitKey(30) == 27)
		{
			std::cout << "Esc pressed by user" << std::endl;
			break;
		}
	}
	return 0;
}

/*int iLowH = 0;	int iLowS = 0;	int iLowV = 0;
int iHighH = 179;	int iHighS = 255;	int iHighV = 255;
createControlMenu(iLowH, iLowS, iLowV, iHighH, iHighS, iHighV);*/

/*tracker(150, 105, 190, 175, 160, 255, imgOriginal, "Purple", 4);
tracker(40, 51, 220, 75, 94, 255, imgOriginal, "Yellow", 4);
tracker(94, 102, 171, 109, 176, 255, imgOriginal, "LightBlue", 4);
tracker(103, 155, 140, 116, 255, 141, imgOriginal, "NavyBlue", 4);
tracker(7, 150, 200, 15, 255, 255, imgOriginal, "Orange", 4);
tracker(60, 145, 160, 80, 195, 240, imgOriginal, "Green", 4);
tracker(0, 0, 191, 179, 25, 255, imgOriginal, "White", 4);
tracker(iLowH, iLowS, iLowV, iHighH, iHighS, iHighV, imgOriginal, "ObjFromControl",3);
//*/
