/*
 * xlink_AppPassthrough.h
 *
 *  Created on: 2014年12月22日
 *      Author: john
 */

#ifndef XLINK_APPPASSTHROUGH_H_
#define XLINK_APPPASSTHROUGH_H_

#include "xlink_system.h"

extern XLINK_FUNC int xlink_demo_init(void);

extern XLINK_FUNC void xlink_demo_loop(void);
extern XLINK_FUNC void xlink_save_at_config(void);
extern XLINK_FUNC void xlink_recv_uart_data(unsigned char *data,unsigned int datalen);
extern XLINK_FUNC int XlinkUartSend(unsigned char *Buffer, unsigned short BufferLen);

#define XLINK_CONFIG_PRODUCTID_KEY   4
#define XLINK_ID_KEY_LENGTH          64

#define XLINK_UART_BUFFER_SIZE __XLINK_BUFFER_PIPE__

typedef union {
	unsigned char byte;
	struct {
		unsigned char isConnectedServer :1;
		unsigned char isConnectWIFI :1;
		unsigned char isNeedSend :1;
		unsigned char isSendUartData :1;
		unsigned char isNeedSendWifiSta:1;
		unsigned char isNeedSendServerSta:1;
		unsigned char res :2;
	} bit;
} XLINK_LOCAL_STA;

#define UART_PACK_MAX 5
#define UART_PACK_LEN 1024
typedef struct{
	uint8_t flag;
	uint16_t len;
	uint8_t  buf[UART_PACK_LEN];
}UART_SEND_PACK;
extern volatile  UART_SEND_PACK uart_send_pack[];
extern volatile int uart_send_pos;

extern XLINK_LOCAL_STA g_AllSta;



#endif /* XLINK_APPPASSTHROUGH_H_ */
