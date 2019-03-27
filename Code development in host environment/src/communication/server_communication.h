/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   server_communication.h
 * Author: Jacek
 *
 * Created on 14 sierpnia 2016, 11:55
 */
#include <opencv2/opencv.hpp>
//#include <opencv2/opencv>


#ifndef SERVER_COMMUNICATION_H
#define SERVER_COMMUNICATION_H

#ifdef __cplusplus
extern "C"
{
#endif


/*Server creation*/
int server_create(int);
int server_create2(int);
/*Server waits for connection*/
int server_await_connection(void);
int server_await_connection2(void);
/*Server sending*/
int server_send(void* pointer, int size);
int server_send2(void* pointer, int size);
/*Server receiving*/
int server_receive(void* pointer, int size);
int server_receive2(void* pointer, int size);
/*Server receiving photo*/
int server_receive_photo(unsigned char* pointer, int size);

/*Close server*/
void server_close(void);
void server_close2(void);
int server_send_photo(cv::Mat image);

#ifdef __cplusplus
}
#endif

#endif /* SERVER_COMMUNICATION_H */

