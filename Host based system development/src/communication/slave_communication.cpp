/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "slave_communication.h"
#include "Network_scfg.h"
#include <sys/types.h>

#include <iostream>
#include <string>

using namespace std;

/*Socket handle*/
static int sockfd;

/*Server settings*/
static struct sockaddr_in serv_addr;

/*Server hostname*/
static struct hostent *server;

/*--------------------------------------------------------------*/

/*Slave connection*/
int slave_create(std::string IP, int SERVER_PORT){

	int timeout=SLAVE_CONNECTION_TIMEOUT;

	/*socket creation*/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){

		//error("ERROR opening socket");
		fprintf(stderr,"ERROR, no socket created\n");
		return -1;
	}

	/*Get server hostname*/
	server = gethostbyname(IP.c_str());
	if (server == NULL) {
		fprintf(stderr,"ERROR, no such host\n");
		return -1;
	}

	/*Connection settings*/
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr,server->h_length);
	serv_addr.sin_port = htons(SERVER_PORT);

	/*Connect*/
	while(timeout>0){
		if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){

			timeout--;
		}
		else{
			return 0;
		}

	}

	//fprintf(stderr,"ERROR, no connection\n");
	return -1;

}

int slave_send(void* pointer, int size){


	bool in = isConnected();
	if(in)
	{

		int bytes_sent;
		bytes_sent = send(sockfd, pointer, size, 0 );


		if(bytes_sent<=0){

			fprintf(stderr,"ERROR, data not sent\n");
			return -1;

		}
		else
		{
			return 0;
		}

	}
	else
	{
		return -1;
	}

}

int slave_send_photo(unsigned char* pointer, int size){

	int total_samples = size;
	char photo_buffer[PHOTO_BUFFER_SIZE];
	char response_buffer[10];
	int status=0;
	int counter=0, i=0;

	while(total_samples>PHOTO_BUFFER_SIZE){

		for(i=0;i<PHOTO_BUFFER_SIZE;i++){

			*(photo_buffer+i)=*(pointer+counter);
			counter++;
			total_samples--;
		}
		status+=send(sockfd, photo_buffer, PHOTO_BUFFER_SIZE,0);
		read(sockfd,response_buffer,10);
	}
	if(total_samples>0){

		for(i=0;i<total_samples;i++){

			*(photo_buffer+i)=*(pointer+counter);
			counter++;
		}
		status+=send(sockfd, photo_buffer, total_samples,0);
	}
	if(status==size){

		return 0;
	}
	else{

		return -1;
	}

}

int slave_receive(void* pointer, int size){

	int bytes_read;

	bytes_read = read(sockfd, pointer, size);

	if(bytes_read<0){

		fprintf(stderr,"ERROR, data not read\n");
		return -1;

	}
	else{

		return 0;
	}

}

void slave_close(void){

	close(sockfd);
}

void communication_error(const char *msg)
{
	perror(msg);
	exit(1);
}


int isConnected (void)
{
	int err = 0;
	socklen_t size = sizeof (err);
	int check = getsockopt (sockfd, SOL_SOCKET, SO_ERROR, &err, &size);

	if (check != 0)
	{
		cout << "Disconnected" << endl;
	}


	if (err==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}

}


int isNotConnected (void)
{
	int err = 0;
	socklen_t size = sizeof (err);
	int check = getsockopt (sockfd, SOL_SOCKET, SO_ERROR, &err, &size);

	if (check != 0)
	{
		cout << "Disconnected." << endl;
	}

	return err;

}

