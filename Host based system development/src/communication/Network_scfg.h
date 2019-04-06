
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Network_cfg.h
 * Author: Jacek
 *
 * Created on 7 sierpnia 2016, 16:06
 */

#ifndef NETWORK_CFG_H
#define NETWORK_CFG_H

#ifdef __cplusplus
extern "C"
{
#endif

#define PHOTO_BUFFER_SIZE  256

#define SERVER_MAX_CONNECTIONS  6

//#define RPI_NETWORK_SERVER  FALSE
//#define RPI_NETWORK_SLAVE  TRUE


#define SERVER_IP	        "192.168.10.222" // and
#define RPI_M1_SLAVE1_IP	"192.168.10.11"
#define RPI_M1_SLAVE2_IP	"192.168.10.12"
#define RPI_M2_SLAVE1_IP	"192.168.10.13"
#define RPI_M2_SLAVE2_IP	"192.168.10.14"
#define RPI_M3_SLAVE1_IP	"192.168.10.15"
#define RPI_M3_SLAVE2_IP	"192.168.10.16"
#define ATMEGA_IP	        "192.168.10.17"

//#define SERVER_PORT		    52000
//#define RPI_PORT		    53000
//#define MASTER_PORT		52000
//#define SLAVE_1_PORT	    53000
//#define SLAVE_2_PORT	    54000

#define SLAVE_CONNECTION_TIMEOUT    1

#ifdef __cplusplus
}
#endif

#endif /* NETWORK_CFG_H */
