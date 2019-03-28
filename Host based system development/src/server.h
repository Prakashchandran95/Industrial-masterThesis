

#ifndef SERVER_H_
#define SERVER_H_


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "video.h"

using namespace cv;

extern pthread_mutex_t lock;
extern Mat image;
extern videomain raspi;


void server (void );
void create_RPI_server(pthread_t&, int&);


#endif /* SERVER_H_ */
