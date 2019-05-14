

#ifndef HOG_H_
#define HOG_H_




#endif /* HOG_H_ */
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
using namespace cv::ml;
#ifndef DETECTION_H_
#define DETECTION_H_

class detection {

public:
    detection();

    virtual ~detection();
    void SVMinitialising(String&);
    void applyinghog(HOGDescriptor&);





private:
    Ptr<SVM> svm;
    vector< float >  hog_detector;





};

#endif // DETECTION_H_
