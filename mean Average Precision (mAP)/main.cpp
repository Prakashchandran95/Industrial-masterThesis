#include <iostream>
#include<sstream>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include<fstream>
#include<vector>
#include<string>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/objdetect.hpp"
#include <opencv2/ml.hpp>
using namespace std;
using namespace cv;


String face_cascade_name = "MYcascadeH2.xml";

CascadeClassifier face_cascade;
String window_name = "Capture - Face detection";

void  setpixels(Rect &a,Rect &b,int &numerator,int &num){


    if((a.x+a.width)>b.x && (a.x<(b.x+b.width))){
        if((a.y+a.height)>b.y && (a.y<(b.y+b.height))){
            int x1= a.x >= b.x ? a.x:b.x;
            int x2= (a.x+a.width) <=(b.x+b.width) ? (a.x+a.width):(b.x+b.width);
            int y1= a.y >= b.y ? a.y:b.y;
            int y2= (a.y+a.height) <=(b.y+b.height) ? (a.y+a.height):(b.y+b.height);
            double lap=(x2-x1)*(y2-y1);
            double uni=(a.width*a.height)+(b.width*b.height)-lap;
            if((lap/uni)>=0.5){
                numerator=numerator+1;
                num=1;
            }

        }}
}
void detectAndDisplay( Mat frame,vector<Rect>&reccord,int &truepositive,int &falsepositive, int &falsenegative,vector<double>&precision,vector<double>&recall)
{
    std::vector<Rect> faces;
    Mat frame_gray;
    frame.copyTo(frame_gray);
    // cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces

    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    vector<int>fn(reccord.size());
    for ( size_t i = 0; i < faces.size(); i++ )
    {
        Rect r = faces[i];
        int numerator=0;
        for ( size_t j= 0; j < reccord.size(); j++ )
        {
            int num=0;
            setpixels(r,reccord[j],numerator,num);
            fn[j]= fn[j]+num;
          //  cout<<fn[j]<<" , ";
        }
     //   cout<<endl;
        if(numerator>=1){
            truepositive=truepositive+1;
        }
        else{falsepositive=falsepositive+1;}
        precision.push_back(truepositive/(truepositive+falsepositive));
        recall.push_back(truepositive);

        /*     r.x += cvRound(r.width*0.1);
        r.width = cvRound(r.width*0.8);
        r.y += cvRound(r.height*0.07);
        r.height = cvRound(r.height*0.8);
        rectangle(frame, r.tl(), r.br(), Scalar(0,255,0), 3);*/
    }
    for ( size_t j= 0; j < reccord.size(); j++ ){
        if(fn[j]==0){
            falsenegative=falsenegative+1;
        }
    }
    // imshow( window_name, frame );
}



int main( void )
{
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
    int truepositive=0,falsepositive=0,falsenegative=0;
    vector<double> precision;
    vector<double> recall;
    vector<double> finalprecision;
    vector<double> finalrecall;
    string line;
    vector<string>seperated;
    ifstream textfile("info.txt");
    if(textfile.is_open()){
        while(getline(textfile,line))
        {
            seperated.push_back(line);
        }
        textfile.close();
    }
    else{
        cout<<"error opening text file"<<endl;
    }
    if (seperated.size() == 0) {
        printf("No positive training samples found, nothing to do!\n");
        return EXIT_SUCCESS;
    }
    for(int i=0;i<seperated.size();i++){
        int a1=seperated[i].find("/",0);
        string directory;
        directory.assign(seperated[i],0,a1+1);
        int a=seperated[i].find(" ",a1+1);
        string image;
        image.assign(seperated[i],a1+1,a-(a1+1));
        int ext= image.find(".jpg",0);
        int ext1= image.find(".png",0);
        int ext2= image.find(".bmp",0);
        if((ext >=1)||(ext1 >=1)||(ext2 >=1)){


            string path=string(directory);
            stringstream buff;
            buff<< path << image;
            Mat c=imread(buff.str(),IMREAD_GRAYSCALE);
            int b0=seperated[i].find(" ",a+1);
            string imagecount;
            imagecount.assign(seperated[i],a+1,b0-(a+1));
            int d=stoi(imagecount);

        //    cout<<d<<" : ";
            int b=b0;
            vector<Rect>reccord;
            int clarrificationcount=0;
            while(b<seperated[i].size())
            {

                int b1=seperated[i].find(" ",b+1);
                string dimensions1;
                dimensions1.assign(seperated[i],b+1,b1-(b+1));
                int x=stoi(dimensions1);
                int b2=seperated[i].find(" ",b1+1);
                string dimensions2;
                dimensions2.assign(seperated[i],b1+1,b2-(b1+1));
                int y=stoi(dimensions2);
                int b3=seperated[i].find(" ",b2+1);
                string dimensions3;
                dimensions3.assign(seperated[i],b2+1,b3-(b2+1));
                int w=stoi(dimensions3);
                int b4=seperated[i].find(" ",b3+1);
                string dimensions4;
                dimensions4.assign(seperated[i],b3+1,b4-(b3+1));
                int h=stoi(dimensions4);
                if(((c.size().height)>=(y+h-1))&&((c.size().width)>=(x+w-1))){
                    reccord.push_back(Rect(x, y, w-1, h-1));
        //            Mat img = c(Rect(x, y, w-1, h-1));
          //          imshow( "clarrification", img );
           //         waitKey(10);
                    clarrificationcount=clarrificationcount+1;
                    b=b4;
                }
            }
          //  cout<<clarrificationcount<<endl;
            detectAndDisplay( c,reccord,truepositive,falsepositive,falsenegative ,precision,recall);

        }
    }
    for(int i=1;i<recall.size();i++){
        recall[i]=(recall[i])/(truepositive+falsenegative);
    }
    double map=0,mapdenom=0;
    int ii=0;
    while(ii<recall.size()){
        int value=precision[ii];
        int value1;
        int value2=0;
        for(int j=ii+1;j<recall.size();j++){
            if(recall[ii]==recall[j]){
                value=recall[j]>=value? precision[j]:value;
                value1=j;
                value2=value2+1;
            }}
        if(value2>0){
            finalrecall.push_back(recall[value1]);
            finalprecision.push_back(value);
            ii=value1+1;
        }
        else{
            ii=ii+1;
        }

    }
    if(finalrecall.size()>0){
        for(int i=0;i<finalrecall.size();i++){

        //    mapdenom=((finalrecall[i]*10)+1)-mapdenom;

          //  map=map+((finalprecision[i]*mapdenom)/((finalrecall[finalrecall.size()-1]*10)+1) );
           // mapdenom=((finalrecall[i]*10)+1);
               map=map+(finalprecision[i]/finalprecision.size());

        }
    }
    else{
        for(int i=0;i<precision.size();i++){

         //   mapdenom=((recall[i]*10)+1)-mapdenom;

           // map=map+((precision[i]*mapdenom)/((recall[recall.size()-1]*10)+1));
           // mapdenom=((recall[i]*10)+1);
             map=map+(precision[i]/precision.size());

        }
    }

    cout<<"final mAp: "<<map<<endl;
    cout<<"total: "<<truepositive+falsenegative<<endl;

    cout<<"truepositive: "<<truepositive<<endl;
    cout<<"falseposititive: "<<falsepositive<<endl;
    cout<<"falsenegative: "<<falsenegative<<endl;

    return 0;

}
