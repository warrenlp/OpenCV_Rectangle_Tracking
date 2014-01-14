//============================================================================
// Name        : OpenCV_Rectangle_Tracking.cpp
// Author      : Warren Parsons
// Version     : Rev 1.0

// Description : Hello World in C++, Ansi-style
//============================================================================

#include "RectangleDetector.h"

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

    for (;;)
    {
        cap >> frame;

        if( frame.empty() )
        {
        	cout << "Couldn't load frame" << endl;
        	continue;
        }

        detector.FindSquares(frame, squares, colorSquares);
        detector.DrawSquares(frame, squares);

        if (cv::waitKey(30) > 0)
            break;
    }

    return 0;
}
