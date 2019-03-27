

#include "video.h"
#include <iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <raspicam_cv.h>




using namespace std;
using namespace cv;
using namespace raspicam;
videomain::videomain(){

}

void videomain::mainvideo(Mat& ink){

	ink.copyTo(image);

}

videomain::~videomain() {
}

