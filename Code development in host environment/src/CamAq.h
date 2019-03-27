
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

using namespace raspicam;
using namespace std;
using namespace cv;
#ifndef CAMAQ_H_
#define CAMAQ_H_

class CamAq {

public:
    CamAq();

    virtual ~CamAq() ;
    void prepareImage(Mat&,Mat&);

    void applying(Mat&,Mat&,Mat&,bool&,Point&);







private:

    Mat image;
    Mat differenceImage,treshImage;
    int sw,sh;// minimum size



};
#endif /* CAMAQ_H_ */
