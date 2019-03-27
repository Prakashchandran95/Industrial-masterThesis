#include <iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;
#ifndef CAMAQ_H_
#define CAMAQ_H_

class CamAq {

public:
    CamAq();

    virtual ~CamAq();
    void prepareImage(Mat&,Mat&);

    void applying(Mat&,Mat&,Mat&,bool&,Point&);







private:

    Mat image;
    Mat differenceImage,treshImage;



};
#endif /* CAMAQ_H_ */
