/*
 * video.h
 *
 *  Created on: May 22, 2018
 *      Author: intema
 */
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <raspicam_cv.h>
#include <iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include "server.h"
#include "CamAq.h"

using namespace raspicam;
using namespace std;
using namespace cv;
using namespace cv::ml;
#ifndef VIDEO_H_
#define VIDEO_H_
class videomain {

public:
	videomain();
	  virtual ~videomain();
	 void  mainvideo(Mat&);

    Mat image;

private:


};




#endif /* VIDEO_H_ */
