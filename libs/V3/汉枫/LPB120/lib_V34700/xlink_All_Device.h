#ifndef __XLINK_ALL_DEVICE_H_
#define __XLINK_ALL_DEVICE_H_

#include "hsf.h"

#define   XLINK_FUNC   USER_FUNC

#define   xlink_strlen(x)           strlen((char*)(x)) //
#define   xlink_strcmp(x,t)         strcmp((char*)(x),(char*)(t)) //
#define   xlink_strncmp(x,t,z)      strncmp((char*)(x),(char*)(t),z) //
#define   xlink_memset(x,d,t)       memset(x,d,t)  //
#define   xlink_memcpy(x,d,l)       memcpy(x,d,l) //
#define   xlink_msleep(n)           //xlink_delay(n);//us绾?
#define   xlink_sprintf             sprintf
#define   xlink_malloc(x)           hfmem_malloc(x)
#define   xlink_free(x)             hfmem_free(x)
#define   xlink_close(x)            //xclose(x)
#define   xlink_printf              printf

typedef  unsigned int xsdk_time_t;
//typedef  unsigned char uint8_t;


struct in_address {
	unsigned int s_addr;
};

typedef union {
	unsigned int ip;
	struct {
		unsigned char byte0 :8;
		unsigned char byte1 :8;
		unsigned char byte2 :8;
		unsigned char byte3 :8;
	}bit;
}IPAddr;

struct sockaddr_in {
	uip_ipaddr_t  addr;
	int socket;
	unsigned short sin_port;
	unsigned int sin_family;
	struct in_address sin_addr;
};

typedef struct sockaddr_in xlink_addr;
typedef struct {
volatile	 int sockfd;
}xlink_tcp_socket_info_t;

extern volatile xlink_tcp_socket_info_t xlink_tcp_socket_info;

#endif


