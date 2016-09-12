/*
 * xlink_at.h
 *
 *  Created on: 2015年8月1日
 *      Author: XT800
 */

#ifndef XLINK_AT_H_
#define XLINK_AT_H_

#define __X_AT_OK__ 5
#define __X_CMD_SIZE_ 33
#define __X_CMD_PARAM_COUNT_  5
#define AT_VERSION   2

typedef struct xlink_at_cmd {
	const char * name;
	int (*func)(int, char **argv);
	const char * doc;
} xlink_at_cmd_t;

extern int xlink_process_at_cmd(unsigned char *data, unsigned int datalen);
extern int xlink_send_uart_sta(void);
extern int xlink_start_smart(void);

typedef struct {
	union {
		unsigned char byte;
		struct {
			unsigned char isSendSta :1;
			unsigned char isSetMac :1;
			unsigned char res :6;
		} bit;
	} flag;
	char macString[13];
} AT_CONFIG;

#endif /* XLINK_AT_H_ */
