

#include "CamAq.h"
#include <raspicam_cv.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
using namespace cv;
using namespace raspicam;


CamAq::CamAq(){
	       sw=135;
			sh=70;
}
void CamAq::prepareImage(Mat& NewImage,Mat& OldImage)
{
    cvtColor(OldImage,OldImage,CV_BGR2GRAY);
    cvtColor(NewImage,NewImage,CV_BGR2GRAY);
    absdiff(OldImage,NewImage,differenceImage);
    threshold(differenceImage,treshImage,30,255,THRESH_BINARY);
    //threshold(NewImage,treshImage,30,255,THRESH_BINARY);
    blur(treshImage,treshImage,Size(30,10));
    threshold(treshImage,treshImage,30,255,THRESH_BINARY);


}

void CamAq::applying(Mat& NewImage,Mat& OldImage,Mat& img,bool& ismotiondetected,Point& p)
{

    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;

    NewImage.copyTo(image);
    prepareImage(NewImage, OldImage);
    findContours(treshImage,contours, hierarchy,CV_RETR_TREE,CV_CHAIN_APPROX_SIMPLE );

    if(contours.size()>0)
    {

        ismotiondetected=true;
        int minx=7500, maxx=0, miny=5000, maxy=0;

        for(int idx = 0 ; idx >= 0; idx = hierarchy[idx][0])
        {

            Rect k = boundingRect(contours[idx]);
            minx=(k.x<minx)?(k.x):minx;
            maxx=((k.x+k.width)>maxx)?(k.x+k.width):maxx;
            miny=(k.y<miny)?(k.y):miny;
            maxy=((k.y+k.height)>maxy)?(k.y+k.height):miny;


        }
        //  Rect r=Rect(minx,miny,(maxx-minx),(maxy-miny)) ;
        // cout<<image.size().width<<" : "<<image.size().height<<endl;
        Rect r;
        Point pa;

        if(((maxx-minx)<sw)||((maxy-miny)<sh)){
            if(((maxx-minx)<sw)){
                int a=sw-(maxx-minx);
                if((minx>a/2)){
                    r.x=(minx-(a/2));
                    if(((image.size().width-maxx)>a/2)){
                        pa.x=(maxx+(a/2));}
                    else{
                        pa.x=(maxx+(image.size().width-maxx));
                        r.x=r.x-((a/2)-(image.size().width-maxx));
                    }
                }
                else{r.x=0;
                    pa.x=maxx+(a/2)+((a/2)-minx);}
            }

            if(((maxy-miny)<sh)){
                int b=sh-(maxy-miny);
                if((miny>b/2)){
                    r.y=(miny-(b/2));
                    if(((image.size().width-maxy)>b/2)){
                        pa.y=(maxy+(b/2));}
                    else{
                        pa.y=(maxy+(image.size().height-maxy));
                        r.y=r.y-((b/2)-(image.size().height-maxy));
                    }
                }
                else{r.y=0;
                    pa.y= maxy+(b/2)+((b/2)-miny);}
            }
        }
        else{
            r.x=(minx>0)?(minx-1):minx;
            r.width=((maxx-minx)<639)?((maxx-minx)+1):(maxx-minx);
            r.y=(miny>0)?(miny-1):miny;
            r.height=((maxy-miny)<479)?((maxy-miny)+1):(maxy-miny);
        }
        //  r.x += cvRound(r.width*0.1);
        //  r.width = cvRound(r.width*0.8);
        // r.y += cvRound(r.height*0.07);
        // r.height = cvRound(r.height*0.8);
        //rectangle(image, r.tl(), r.br(), Scalar(255,255,255), 3);
        // Point pt1(r.x, r.y);
        //Point pt2((r.x+r.width), (r.y+r.height));
        //rectangle(image, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
        img = image(r);
        //p=point(r.x,r.y);
        p.x=r.x;
        p.y=r.y;

    }

}


CamAq::~CamAq() {
}
