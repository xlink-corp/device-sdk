/*
 * xlink_HF.h
 *
 *  Created on: 2015年9月6日
 *      Author: XT800
 */

#ifndef XLINK_HF_H_
#define XLINK_HF_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <HSF.H>
#include <STDLIB.H>
#include <STRING.H>
#include <STDIO.H>
#include <hfsys.h>
#include <hfnet.h>
#include <hfuart.h>

#define  XLINK_FUNC   //USER_FUNC

#define   xlink_strlen(x)      strlen(x)
#define   xlink_strcmp(x,t)    strcmp((char*)(x),(char*)(t))
#define   xlink_strncmp(x,t,z) strncmp((char*)(x),(char*)(t),z)
#define   xlink_memset(x,d,t)  memset(x,d,t)
#define   xlink_memcpy(x,d,l)  memcpy(x,d,l)
#define   xlink_msleep(n)      msleep(n)

#define   xlink_sprintf        sprintf

#define   xlink_socket         socket
#define   xlink_bind           bind
#define   xlink_connect        connect
#define   xlink_setsockopt     setsockopt
#define   xlink_recv           recv
#define   xlink_recvfrom       recvfrom
#define   xlink_sendto         sendto
#define   xlink_send           send
#define   xlink_close(x)      close(x)
#define   xlink_set_fd        fd_set
#define   xlink_select(a,b,c,d,e)       hfuart_select(a,b,c,d,e)


typedef time_t xsdk_time_t;
typedef struct sockaddr_in xlink_addr;


#ifdef  __cplusplus
}
#endif
#endif /* XLINK_HF_H_ */
