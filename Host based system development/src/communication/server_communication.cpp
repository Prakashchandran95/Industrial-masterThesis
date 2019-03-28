#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "server_communication.h"
#include "Network_scfg.h"
#include <sys/stat.h>

#include <string.h>
#include <sstream>
#include <iostream>
#include <fstream>


#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


using namespace std;
using namespace cv;




/*Socket handles*/
static int sockfd_server, newsockfd_server;
static int sockfd_server2, newsockfd_server2;
/*Server settings*/
static struct sockaddr_in serv_addr;
static struct sockaddr_in serv_addr2;

/*Client settings*/
static socklen_t clilen,clilen2;
static struct sockaddr_in cli_addr, cli_addr2;

/*Server hostname*/
struct hostent *server, *server2;

/*--------------------------------------------------------------*/

/*Slave connection*/
int server_create(int RPI_PORT)
{

	if (RPI_PORT < 2) {
		fprintf(stderr,"ERROR, incorrect port number\n");
		return -1;
	}

	/*Socket creation*/
	sockfd_server= socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd_server< 0){

		fprintf(stderr,"ERROR, no socket created!\n");
		return -1;
	}


	/* Dawid -> fork */

	int reuse=1;
	//if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(char *)&reuse, sizeof(int))==0){
	if(setsockopt(sockfd_server, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))==-1){
		cout << "SO_REUSEADDR error: " << setsockopt << endl;
	}

	//  if(setsockopt(sockfd_server, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse))==-1){
	//      cout << "SO_REUSEPORT error: " << setsockopt << endl;
	//  }

	/* END Dawid -> fork */




	/*Clears server address*/
	bzero((char *) &serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(RPI_PORT);

	if (bind(sockfd_server, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){

		fprintf(stderr,"ERROR, settings not binded\n");
		return -1;
	}

	listen(sockfd_server, SERVER_MAX_CONNECTIONS);
	clilen = sizeof(cli_addr);

	return 0;
}

int server_create2(int RPI_PORT)
{

	if (RPI_PORT < 2) {
		fprintf(stderr,"ERROR, incorrect port number\n");
		return -1;
	}

	/*Socket creation*/
	sockfd_server2= socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd_server2< 0){

		fprintf(stderr,"ERROR, no socket created!\n");
		return -1;
	}


	/* Dawid -> fork */

	int reuse=1;
	//if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,(char *)&reuse, sizeof(int))==0){
	if(setsockopt(sockfd_server2, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse))==-1){
		cout << "SO_REUSEADDR error: " << setsockopt << endl;
	}

	//  if(setsockopt(sockfd_server, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse))==-1){
	//      cout << "SO_REUSEPORT error: " << setsockopt << endl;
	//  }

	/* END Dawid -> fork */




	/*Clears server address*/
	bzero((char *) &serv_addr2, sizeof(serv_addr2));

	serv_addr2.sin_family = AF_INET;
	serv_addr2.sin_addr.s_addr = INADDR_ANY;
	serv_addr2.sin_port = htons(RPI_PORT);

	if (bind(sockfd_server2, (struct sockaddr *) &serv_addr2, sizeof(serv_addr2)) < 0){

		fprintf(stderr,"ERROR, settings not binded\n");
		return -1;
	}

	listen(sockfd_server2, SERVER_MAX_CONNECTIONS);
	clilen2 = sizeof(cli_addr2);

	return 0;
}


int  server_await_connection(void){

	newsockfd_server = accept(sockfd_server,(struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd_server < 0){

		return -1;
	}
	else{

		return 0;
	}

	int pid=fork();
	if (pid < 0){
		fprintf(stderr, "error on fork");
	}
	else{
		close(sockfd_server);
	}


}

int  server_await_connection2(void){

	newsockfd_server2 = accept(sockfd_server2,(struct sockaddr *) &cli_addr2, &clilen2);

	if (newsockfd_server2 < 0){

		return -1;
	}
	else{

		return 0;
	}

	int pid=fork();
	if (pid < 0){
		fprintf(stderr, "error on fork");
	}
	else{
		close(sockfd_server2);
	}

}

int server_send(void* pointer, int size){

	int bytes_sent;

	bytes_sent = write(newsockfd_server,pointer,size);

	if(bytes_sent<0){

		fprintf(stderr,"ERROR, data not sent\n");
		return -1;

	}
	else{

		return 0;
	}
}


int server_send2(void* pointer, int size){

	int bytes_sent;

	bytes_sent = write(newsockfd_server2,pointer,size);

	if(bytes_sent<0){

		fprintf(stderr,"ERROR, data not sent\n");
		return -1;

	}
	else{

		return 0;
	}
}

int server_receive(void* pointer, int size){

	int bytes_read;

	bytes_read = read(newsockfd_server, pointer, size);

	if(bytes_read<0){

		fprintf(stderr,"ERROR, data not read \n");
		return -1;

	}
	else{

		return 0;
	}

}


int server_receive2(void* pointer, int size){

	int bytes_read;

	bytes_read = read(newsockfd_server2, pointer, size);

	if(bytes_read<0){

		fprintf(stderr,"ERROR, data not read \n");
		return -1;

	}
	else{

		return 0;
	}

}

int server_receive_photo(unsigned char* pointer, int size){

	int total_samples = size;
	char photo_buffer[PHOTO_BUFFER_SIZE];
	// char response_buffer[10];
	int status=0;
	int counter=0, i=0;

	while(total_samples>PHOTO_BUFFER_SIZE){


		status+=read(newsockfd_server, photo_buffer, PHOTO_BUFFER_SIZE);
		for(i=0;i<PHOTO_BUFFER_SIZE;i++){

			*(pointer+counter)=*(photo_buffer+i);
			counter++;
			total_samples--;
		}
		send(newsockfd_server, "MAM.......", 10,0);
	}
	if(total_samples>0){

		status+=read(newsockfd_server, photo_buffer, total_samples);
		for(i=0;i<total_samples;i++){

			*(pointer+counter)=*(photo_buffer+i);
			counter++;
		}
	}

	if(status==size){

		return 0;
	}
	else{

		return -1;
	}

}

void server_close(void){


	close(newsockfd_server);
	///	close(sockfd_server);


}

void server_close2(void){


	close(newsockfd_server2);
	///	close(sockfd_server);


}


int server_send_photo(Mat image)
{

	int  imgSize = image.total()*image.elemSize();

	send(newsockfd_server, image.data, imgSize, 0);

	//cout << "wysłano !" << endl;

}




