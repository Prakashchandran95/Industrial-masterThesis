
#include "motion.h"
#include <iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <time.h>
using namespace std;
using namespace cv;


String face_cascade_name = "MYcascadeH2.xml";


CascadeClassifier face_cascade;
void visualisingoutput(Mat& image,bool& ismotiondetected)
{

    if(ismotiondetected==true){
       //  cout<<"motion detected"<<endl;

        if((image.size().height>0)&&(image.size().width>0)){
            vector<Rect> found;


            face_cascade.detectMultiScale(image, found, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
            if(found.size()>0){
         //       cout<<"detected object is: human"<<endl;
                size_t i;
                for (i=0; i<found.size(); i++)
                {
                    Rect r = found[i];
                    r.x += cvRound(r.width*0.1);
                    r.width = cvRound(r.width*0.8);
                    r.y += cvRound(r.height*0.07);
                    r.height = cvRound(r.height*0.8);
                    rectangle(image, r.tl(), r.br(), Scalar(0,255,0), 3);

                }

            }

            else{cout<<"detected object is: alien object"<<endl;}
            namedWindow( "motiondetected", WINDOW_AUTOSIZE );
            imshow("motiondetected", image);
            waitKey(1);
        }
    }

}
int main() {

    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
    int old_image_index=-1 ;
    Point p;
    float s=0,s1=0;
     time_t start, end;
     int framecount=0;
    int new_image_index = 0;
    bool ismotiondetected=false;
    Mat imagePack[2];
    Mat image,OldImage,NewImage;
    CamAq motion;

    VideoCapture cap(-1);
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

    if (!cap.isOpened()){
        cout<<"error in camera"<<endl;
    }
    time(&start);
    int i=0;
    while (i<1)
    {

        cap >> imagePack[new_image_index];
        if(old_image_index>=0)
        {
            NewImage=imagePack[new_image_index];
            OldImage=imagePack[old_image_index];
            framecount=framecount+1;
            motion.applying(NewImage,OldImage,image,ismotiondetected,p);

            visualisingoutput(image,ismotiondetected);
            time(&end);
            s=end-start;
            s1=s-s1;
           // cout<<"for motion alt2: "<<"starting time: "<<start<<" , time taken for the pixels upto now from the starting time: "<<end<<" , time taken for pixel upto now from zero: "<< s<<" , time taken for individual pixel:  "<<s1<<" count:"<<framecount<<endl;
           // cout<<"for motion alt_tree: "<<"starting time: "<<start<<" , time taken for the pixels upto now from the starting time: "<<end<<" , time taken for pixel upto now from zero: "<< s<<" , time taken for individual pixel:  "<<s1<<" count:"<<framecount<<endl;
           //    cout<<"for motion self_trained: "<<"starting time: "<<start<<" , time taken for the pixels upto now from the starting time: "<<end<<" , time taken for pixel upto now from zero: "<< s<<" , time taken for individual pixel:  "<<s1<<" count:"<<framecount<<endl;
            cout<<"for motion lbp: "<<"starting time: "<<start<<" , time taken for the pixels upto now from the starting time: "<<end<<" , time taken for pixel upto now from zero: "<< s<<" , time taken for individual pixel:  "<<s1<<" count:"<<framecount<<endl;
            s1=s;

        }
        if(framecount==103){

            double seconds = difftime (end, start);
            double fps  = framecount / seconds;
            cout<<"fps :"<<fps<<endl;
            i=3;
        }

        new_image_index= new_image_index+1;
        old_image_index=old_image_index+1;

        if(new_image_index>1)
        {new_image_index=0;}

        if(old_image_index>1)
        {old_image_index=0;}

    }

    return 0;
}

