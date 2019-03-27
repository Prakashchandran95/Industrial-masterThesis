/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   slave_communication.h
 * Author: Jacek
 *
 * Created on 14 sierpnia 2016, 11:55
 */

#include <iostream>
#include <string>

#ifndef SLAVE_COMMUNICATION_H
#define SLAVE_COMMUNICATION_H

#ifdef __cplusplus
extern "C"
{
#endif

/*Slave connection*/
int slave_create(std::string IP, int SERVER_PORT);

/*Slave sending*/
int slave_send(void* pointer, int size);

/*Slave sending photo*/
int slave_send_photo(unsigned char* pointer, int size);

/*Slave receiving*/
int slave_receive(void* pointer, int size);

/*Close slave*/
void slave_close(void);

/*checking status */
int isConnected (void);
int isNotConnected (void);

/*Error handling*/
void communication_error(const char *msg);

#ifdef __cplusplus
}
#endif

#endif /* SLAVE_COMMUNICATION_H */
