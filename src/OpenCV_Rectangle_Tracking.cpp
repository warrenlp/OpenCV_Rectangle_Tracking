//============================================================================
// Name        : OpenCV_Rectangle_Tracking.cpp
// Author      : Warren Parsons
// Version     : Rev 1.0

// Description : Hello World in C++, Ansi-style
//============================================================================

#include "RectangleDetector.h"
#include "OpenCVTimer.h"

#include <iostream>
using namespace std;

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char *argv[])
{
    //std::string url("rtsp://admin:root@192.168.0.4:554/play2.sdp");
    //std::string url("http://admin:root@192.168.0.4/video/mjpg.cgi");
    std::string url("http://root:pass@192.168.0.19/axis-cgi/mjpg/video.cgi");

    cv::VideoCapture cap(url);

    if (!cap.isOpened())
    {
        std::cout << "Could not read or open url: " << url << std::endl;
        return -1;
    }

    vector<vector<cv::Point> > squares;
    vector<vector<cv::Point> > colorSquares[3];

    cv::Mat frame;
    CRectangleDetector detector;
    COpenCVTimer findSquaresTimer(10);
    COpenCVTimer drawSquaresTimer(10);
    double aveRunTime = 0.0;

    for (;;)
    {
        cap >> frame;

        if( frame.empty() )
        {
        	cout << "Couldn't load frame" << endl;
        	continue;
        }

        findSquaresTimer.startTimer();
        detector.FindSquares(frame, squares, colorSquares);
        findSquaresTimer.stopTimer();

        aveRunTime = findSquaresTimer.getAverageTime();

        cout << "Average run time for FindSquares(): " << aveRunTime << "s"<< endl;

        drawSquaresTimer.startTimer();
        detector.DrawSquares(frame, squares);
        drawSquaresTimer.stopTimer();

        aveRunTime = drawSquaresTimer.getAverageTime();

        cout << "Average run time for DrawSquares(): " << aveRunTime << "s"<< endl;

        if (cv::waitKey(30) > 0)
            break;
    }

    return 0;
}
