#include "hog.h"
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
#include "server.h"
#include "CamAq.h"
#include <thread>
#include <unistd.h>
#include "video.h"
//#include "rpiServo.h"



using namespace std;
using namespace cv;
using namespace raspicam;
using namespace cv::ml;
String face_cascade_name="Hogfacepartdetection(64,128).xml";
videomain rspi;
//rpiServo servo;
//connection parameters between camera and servo
//const int delayUs = 2000000;
int center=90,coverage=62,camwidth,camheight;//xparallel=0,yparallel=0;
void visualisingoutput(HOGDescriptor& myhog,Mat& image,bool& ismotiondetected,Point& p)
{
	vector<Rect> found;
	if((image.size().height>0)&&(image.size().width>0)){
		myhog.detectMultiScale(image, found, 0, Size(8,8), Size(32,32), 1.05, 6);
		if(ismotiondetected==true){
			cout<<"motion detected"<<endl;
			if(found.size()>0){
				cout<<"detected object is: human"<<endl;
				size_t i;
				for (i=0; i<found.size(); i++)
				{
					Rect r = found[i];
					r.x += cvRound(r.width*0.1);
					r.width = cvRound(r.width*0.8);
					r.y += cvRound(r.height*0.07);
					r.height = cvRound(r.height*0.8);
					rectangle(image, r.tl(), r.br(), Scalar(0,255,0), 3);
					// Point pt1(r.x, r.y);
					//Point pt2((r.x+r.width), (r.y+r.height));
					//rectangle(img, pt1, pt2, Scalar(0, 255, 0), 2, 8, 0);
					Point points((r.x+(r.width)/2)+p.x,(r.y+(r.height)/2)+p.y);
					//Point points((points1.x+1)*(640/w),(points1.y+1)*(480/h));

				//	unsigned int  xcord=(unsigned int)((center+(coverage/2))-((points.x)*(coverage/camwidth)));
				//	unsigned int  ycord=(unsigned int)((center-(coverage/2))+((points.y)*(coverage/camheight)));
					/*stringstream ss1;
					ss1 << points.x;
			        string str1 = ss1.str();
					stringstream ss2;
					ss2 << points.y;
					string str2 = ss2.str();
					string coordinates;
					coordinates.append(str1);
					coordinates.append(",");
					coordinates.append(str2);
				    ofstream arduino;
                    arduino.open( "/dev/ttyACM0");
                    if(arduino.is_open()){
                        arduino << coordinates;
                        arduino.close();
                    }
                    else{cout<<"trouble in opening Arduino"<<endl;}
					 */
				//	servo.setAngle(180); // set servo to centre
					//usleep(delayUs);
					//servo.setAngle(xcord);
					//usleep(delayUs);
					//servo.setAngle(ycord);
					//usleep(delayUs);

					//cout<<"points: "<<coordinates<<endl;
					//cout<<"points: "<<p.x<<","<<p.y<<endl;

				}
				// namedWindow( "motiondetection & identification", WINDOW_AUTOSIZE );
				//imshow("motiondetection & identification", image);
				//waitKey(10);
				rspi.mainvideo(image);

			}

			else{cout<<"detected object is: alien object"<<endl;}
		}
	}

}

int main() {

	thread t1(server) ;
	t1.detach();

	Point p;
	int old_image_index=-1 ;
	int new_image_index = 0;
	bool ismotiondetected=false;
	Mat imagePack[2];
	Mat image,OldImage,NewImage;
	CamAq motion;
	HOGDescriptor myhog; // Use standard parameters here
	detection face;
	cout<<"hii1 ";
	cout<<"hii3";
	face.SVMinitialising(face_cascade_name);
	cout<<"hii2";
	raspicam::RaspiCam_Cv Camera;
	Camera.set(CV_CAP_PROP_FRAME_HEIGHT, 1080);  // 1080
	Camera.set(CV_CAP_PROP_FRAME_WIDTH, 1920); //1920

	Camera.set(CV_CAP_PROP_FORMAT, CV_8UC1);

	if(!Camera.open())
	{
		cout << "ERROR, could not open camera" << endl;

	}
	while(Camera.open()){
		Camera.grab();
		Camera.retrieve(imagePack[new_image_index]);
		   camwidth=imagePack[new_image_index].size().width;
		   camheight=imagePack[new_image_index].size().height;
		if(old_image_index>=0)
		{
			NewImage=imagePack[new_image_index];
			OldImage=imagePack[old_image_index];
			motion.applying(NewImage,OldImage,image,ismotiondetected,p);
			face.applyinghog(myhog);

			visualisingoutput(myhog,image,ismotiondetected,p);

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
/*int main() {
	rpiServo servo;
	cout<<"hii1";
	servo.setAngle(90); // set servo to centre
	cout<<"hii2";
    usleep(delayUs);
    cout<<"hii3";
    return 0;
}
*/
