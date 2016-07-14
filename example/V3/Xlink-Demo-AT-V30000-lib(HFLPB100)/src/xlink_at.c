/*
 * xlink_at.c
 *
 *  Created on: 2015年8月1日
 *      Author: XT800
 */

#include "xlink_demo.h"
#include "xlink_config.h"
#include "xlink_at.h"

extern XLINK_USER_CONFIG user_config;
extern AT_CONFIG g_atconfig;

static int process_at_help(int argc, char **argv);
static int process_at_setidkey(int argc, char **argv);
static int process_at_ver(int argc, char **argv);
static int process_at_repass(int argc, char **argv);
static int process_at_getStatus(int argc, char **argv);
static int process_at_getid(int argc, char **argv);
static int process_at_getmac(int argc, char **argv);
//static int process_at_setwifista(int argc, char **argv);
static int process_at_reboot(int argc, char **argv);
static int process_at_smart(int argc, char **argv);
static int process_at_debug(int argc, char **argv);
//static int process_at_setmac(int argc, char **argv);
//static int process_at_setIDkey_2(int argc, char **argv);
static int process_at_getTime(int argc, char **argv);
static int xlink_process_at_scan_enable(int argc, char **argv);
const xlink_at_cmd_t xlink_at_table[] = { //
		{ "AT+H", process_at_help, "AT+H get xlink at cmd information\r\n" }, //
				{ "AT+GETMAC#", process_at_getmac, "AT+GETMAC#    get device mac addr\r\n" }, //
				{ "AT+GETVER#", process_at_ver, "AT+GETVER#    get xlink at version\r\n" }, //
				{ "AT+GETSTA#", process_at_getStatus, "AT+GETSTATUS# get current system status (wifi sta,connect server sta)\r\n" }, //
				{ "AT+GETID#", process_at_getid, "AT+GETID#     get current product id\r\n" }, //
				{ "AT+REBOOT#", process_at_reboot, "AT+REBOOT#    reboot system\r\n" }, //
				{ "AT+REPASS#", process_at_repass, "AT+REPASS#  retSet system password 8888\r\n" }, //
				{ "AT+SMART#", process_at_smart, "AT+SMART#  start smartlink\r\n" }, //
				{ "AT+GETTIME#", process_at_getTime, "AT+GETTIME#  get current time\r\n" }, //
				//		{ "AT+SETMAC=", process_at_setmac, "AT+SETMAC=12byte MAC string\r\n" }, //
				{ "AT+DEBUG=", process_at_debug, "AT+DEBUG=ON|OFF\r\n" }, //
				{ "AT+SETIDKEY=", process_at_setidkey, "AT+SETIDKEY=product id,product key\r\n" }, //
				//{ "AT+SETWIFISTA=", process_at_setwifista, "AT+SETWIFISTA=ON|OFF\r\n" }, //
				//{ "AT+SETID=", process_at_setIDkey_2, "XXX" }, //
				{ "AT+SCAN=", xlink_process_at_scan_enable, "AT+SCAN=ON|OFF\r\n" }, //
				{ NULL, NULL, NULL } //
		};
static int xlink_process_at_scan_enable(int argc, char **argv)
{
	char *retBuf = NULL;
	int len = 0;
	if (argc == 2) {
		if (strncmp(argv[1], "ON", 2) == 0) {			
			XlinkPorcess_UDP_Enable();
			retBuf = "AT+SCAN=OK\r\n";
		} else if (strncmp(argv[1], "OFF", 3) == 0) {
			XlinkPorcess_UDP_Disable();
			retBuf = "AT+SCAN=OK\r\n";
		}
	} else {
		retBuf = "AT+SCAN=ERROR\r\n";
	}
	len = xlink_strlen(retBuf);
	XlinkUartSend((unsigned char *) retBuf, len);
	return __X_AT_OK__;
}

int xlink_process_at_cmd(unsigned char *data, unsigned int datalen) {
	int ret = 0;
	unsigned int cmd_length = 0;
	int index = 0;
	int argc = 0;
	char *chr = NULL, *strPtr = NULL;
	char argv[__X_CMD_PARAM_COUNT_ ][__X_CMD_SIZE_ ];
	char *argvPtr[__X_CMD_PARAM_COUNT_ ];
	for (; xlink_at_table[index].name != NULL ; index++) {
		cmd_length = strlen(xlink_at_table[index].name);
		if (cmd_length <= datalen) {
			if (strncmp((char*) data, xlink_at_table[index].name, cmd_length) == 0) {
				argc = 0;
				if (xlink_at_table[index].func) {
					memset(argv[argc], 0, __X_CMD_SIZE_);
					memcpy(argv[argc], xlink_at_table[index].name, cmd_length);
					argvPtr[argc] = argv[argc];
					argc++;
					if ((chr = strchr((char*) data, '=')) != NULL ) {
						strPtr = strtok(chr + 1, ",");
						if (strPtr) {
							cmd_length = strlen(strPtr);
							cmd_length = (cmd_length >= __X_CMD_SIZE_) ? __X_CMD_SIZE_ : cmd_length;
							memset(argv[argc], 0, __X_CMD_SIZE_);
							memcpy(argv[argc], strPtr, cmd_length);
							argvPtr[argc] = argv[argc];
							argc++;

							while ((strPtr = strtok(NULL, ",")) != NULL ) {
								cmd_length = strlen(strPtr);
								cmd_length = (cmd_length >= __X_CMD_SIZE_) ? __X_CMD_SIZE_ : cmd_length;
								memset(argv[argc], 0, __X_CMD_SIZE_);
								memcpy(argv[argc], strPtr, cmd_length);
								argvPtr[argc] = argv[argc];
								argc++;
								if (argc == 5)
									break;
							}
						}
					}
					ret = xlink_at_table[index].func(argc, argvPtr);
				}
				u_printf("\r\n---find cmd %s \r\n", xlink_at_table[index].name);
				ret = __X_AT_OK__;
				break;
			}
		}
	}

	return ret;
}

//static int process_at_setIDkey_2(int argc, char **argv) {
//	u_printf(" process_at_setIDkey_2 argc %d \r\n", argc);
//	int i = 0;
//	for (i = 0; i < argc; i++) {
//		u_printf("at param argv[%d]=%s\r\n", i, argv[i]);
//	}
//	return __X_AT_OK__;
//}

int xlink_send_uart_sta(void) {
	process_at_getStatus(NULL, 0);
	return 0;
}

int xlink_start_smart(void) {
	process_at_smart(NULL, 0);
	return 0;
}

static int process_at_help(int argc, char **argv) {
	int index = 0;
	char *help = "\r\n\r\n------------xlink AT help---------\r\n\r\n";
	XlinkUartSend((unsigned char*) help, strlen(help));
	for (; xlink_at_table[index].name != NULL ; index++) {
		XlinkUartSend((unsigned char*) xlink_at_table[index].doc, strlen(xlink_at_table[index].doc));
	}
	help = "\r\n\r\n------------xlink AT help END---------\r\n\r\n";
	XlinkUartSend((unsigned char*) help, strlen(help));

	return __X_AT_OK__;
}

static int process_at_reboot(int argc, char **argv) {
	hfsys_reset();
	return __X_AT_OK__;
}
static int process_at_setidkey(int argc, char **argv) {
	char*retBuffer = NULL;
	int length = 0;
	int i = 0;
	unsigned char temppid,tempkey;
	if (argc == 3) {
		if (strlen(argv[1]) == 32 && strlen(argv[2]) >= 32) {
			argv[1][32] = '\0';
			argv[2][32] = '\0';
			for (i = 0; i < 32; i++) {
				temppid = argv[1][i];
				tempkey = argv[2][i];
				
			if (temppid <= '9' && temppid >= '0') {
			} else if (temppid > 'f' || temppid < 'a') {
				retBuffer = "AT+RETIDKEY=ERROR\r\n";
				length = strlen(retBuffer);
				XlinkUartSend((unsigned char *) retBuffer, length);
				return __X_AT_OK__;
			}		
			if (tempkey <= '9' && tempkey >= '0') {
			} else if (tempkey > 'f' || tempkey < 'a') {
				retBuffer = "AT+RETIDKEY=ERROR\r\n";
				length = strlen(retBuffer);
				XlinkUartSend((unsigned char *) retBuffer, length);
				return __X_AT_OK__;
			}
		
//				if (temppid <= '9' && temppid >= '0' && tempkey <= '9' && tempkey >= '0') {
//				} else if ((temppid >= 'a' || temppid <= 'f' )&& (tempkey >= 'a' || tempkey <= 'f')) {
//						retBuffer = "AT+RETIDKEY=ERROR\r\n";
//						length = strlen(retBuffer);
//						XlinkUartSend((unsigned char *) retBuffer, length);
//					return __X_AT_OK__;
//				}
			}
			XlinkWriteProductIDKEY(argv[1], argv[2]);
			xlink_msleep(5);
			retBuffer = "AT+RETIDKEY=OK\r\n";
			length = strlen(retBuffer);
			XlinkUartSend((unsigned char *) retBuffer, length);
			xlink_msleep(50);
			process_at_reboot(0, NULL );
			return __X_AT_OK__;
		}

	}
	retBuffer = "AT+RETIDKEY=ERROR\r\n";
	length = strlen(retBuffer);
	XlinkUartSend((unsigned char *) retBuffer, length);
	return __X_AT_OK__;
}

static int process_at_ver(int argc, char **argv) {
	unsigned char buf[200];
	char *temp = NULL;
	memset(buf, 0, 200);
	temp = XlinkSystemVersion();
	if (temp) {
		sprintf((char*) buf, "AT+RETVER=at ver=1.%d  App %d build %s %s %s \r\n", AT_VERSION,user_config.wifisoftVersion , __DATE__,__TIME__,temp);
		XlinkUartSend(buf, strlen((char*) buf));
	} else {
		memcpy(buf, "AT+RETVER=get version failed\r\n", strlen("AT+RETVER=get version failed\r\n"));
		XlinkUartSend(buf, strlen((char*) buf));
	}
	return __X_AT_OK__;
}

//重置密码
static int process_at_repass(int argc, char **argv) {
	char *retBuffer = NULL;
	int len = 0;
    
    XlinkReSetSDK();
    
	retBuffer = "AT+RETPASS=OK\r\n";
	len = strlen(retBuffer);
	XlinkUartSend((unsigned char *) retBuffer, len);
    
    hfsys_reset();
	return __X_AT_OK__;
}

static int process_at_getStatus(int argc, char **argv) {
	unsigned char retBuffer[25] = { 0x00 };

	int retlen = sprintf((char*) retBuffer, "AT+RETSTA=%d,%d\r\n", g_AllSta.bit.isConnectWIFI, g_AllSta.bit.isConnectedServer);

	XlinkUartSend(retBuffer, retlen);

	return __X_AT_OK__;
}

//AT+GETID#
static int process_at_getid(int argc, char **argv) {
	unsigned char retBuffer[50] = { 0x00 };
	extern char m_pID[33];
	int len = sprintf((char*) retBuffer, "AT+RETID=%s\r\n", m_pID);
	XlinkUartSend(retBuffer, len);
	return __X_AT_OK__;
}
void hex_to_string(char *string, unsigned char *mac) {
	signed char hig = 0;
	signed char low = 0;
	unsigned char iter = 0;
	unsigned char index = 0;
	for (iter = 0; iter < 6; iter++) {
		hig = (mac[iter] & 0xf0) >> 4;
		low = (mac[iter] & 0x0f);
		if (0 <= hig && hig <= 9) {
			string[index++] = hig + '0';
		} else {
			string[index++] = hig - 10 + 'A';
		}
		if (0 <= low && low <= 9) {
			string[index++] = low + '0';
		} else {
			string[index++] = low - 10 + 'A';
		}
	}
	string[index] = '\0';
}
//AT+GETMAC#
static int process_at_getmac(int argc, char **argv) {
	char retBuffer[25] = { 0x00 };
	int retLength = sprintf(retBuffer, "AT+RETMAC=%02X%02X%02X%02X%02X%02X\r\n", user_config.mac[0], user_config.mac[1], user_config.mac[2], user_config.mac[3], user_config.mac[4],
			user_config.mac[5]);
	XlinkUartSend((unsigned char*) retBuffer, retLength);
	return __X_AT_OK__;
}

//AT+SETWIFISTA
//static int process_at_setwifista(int argc, char **argv) {
//	char *retBuffer = NULL;
//	int sendlen = 0;
//	do {
//		if (argc == 2) {
//			if (strncmp(argv[1], "ON", 2) == 0) {
//				g_atconfig.flag.bit.isSendSta = 1;
//				xlink_save_at_config();
//				retBuffer = "AT+RETWIFISTA=ON-OK\r\n";
//				break;
//			} else if (strncmp(argv[1], "OFF", 3) == 0) {
//				g_atconfig.flag.bit.isSendSta = 0;
//				xlink_save_at_config();
//				retBuffer = "AT+RETWIFISTA=OFF-OK\r\n";
//				break;
//			}
//		}
//		retBuffer = "AT+RETWIFISTA=ERROR\r\n";

//	} while (0);
//	sendlen = strlen(retBuffer);
//	XlinkUartSend((unsigned char*) retBuffer, sendlen);
//	return __X_AT_OK__;
//}

static int process_at_smart(int argc, char **argv) {
	char buf[20];
	char *cmdS = "AT+SMTLK\r\n";
	char *retcmds = "AT+RETSMART=OK\r\n";
	memset(buf, 0, 20);
	sprintf(buf, "%s", retcmds);
	XlinkUartSend((unsigned char*) buf, strlen(retcmds));
	msleep(20);
	hfat_send_cmd(cmdS, xlink_strlen(cmdS), buf, 20);
	return __X_AT_OK__;
}

static int process_at_debug(int argc, char **argv) {
	char *cmdS = NULL;
	char *retBuf = NULL;
	int len = 0;
	if (argc == 2) {
		if (strncmp(argv[1], "ON", 2) == 0) {
			char buf[20];
			cmdS = "AT+NDBGL=1\r\n";
			hfat_send_cmd(cmdS, xlink_strlen(cmdS), buf, 20);
			retBuf = "AT+RETDEBUG=OK\r\n";
		} else if (strncmp(argv[1], "OFF", 3) == 0) {
			char buf[20];
			cmdS = "AT+NDBGL=0\r\n";
			hfat_send_cmd(cmdS, xlink_strlen(cmdS), buf, 20);
			retBuf = "AT+RETDEBUG=OK\r\n";
		}
	} else {
		retBuf = "AT+RETDEBUG=ERROR\r\n";
	}
	len = xlink_strlen(retBuf);
	XlinkUartSend((unsigned char *) retBuf, len);
	return __X_AT_OK__;
}

static int process_at_getTime(int argc, char **argv) {
	unsigned char retBuffer[50] = { 0x00 };
	XLINK_SYS_TIME m_c_time;
	int ret = XlinkGetSystemTime(&m_c_time);
	ret = sprintf((char*)retBuffer, "AT+RETTIME=%04d-%02d-%02d %01d %02d:%02d:%02d %04d\r\n", m_c_time.year, m_c_time.mon, m_c_time.day, m_c_time.week, m_c_time.hour, m_c_time.min, m_c_time.sec,
			m_c_time.zones);
	XlinkUartSend((unsigned char *) retBuffer, ret);
	return __X_AT_OK__;
}

//int process_at_setmac(int argc, char **argv) {
//	//AT+SETMAC=AAAAAAAAAAAA
//	unsigned char retBuffer[50] = { 0x00 };
//	unsigned char currentMAC[20] = { 0x00 };
//	int len = 0, isOK = 0;
//	if (datalen > 21) {
//		if (data[9] == '=') {
//			sprintf((char*) currentMAC, "%02X%02X%02X%02X%02X%02X", user_config.mac[0], user_config.mac[1], user_config.mac[2], user_config.mac[3], user_config.mac[4], user_config.mac[5]);
//			if (memcmp(data + 10, currentMAC, 12) != 0) {
//				memcpy(g_atconfig.macString, data + 10, 12);
//				g_atconfig.macString[12] = '\0';
//				g_atconfig.flag.bit.isSetMac = 1;
//				XlinkWriteAtConfig(&g_atconfig);
//				len = sprintf((char*) retBuffer, "AT+RETSETMAC=OK+%s\r\n", g_atconfig.macString);
//				isOK = 1;
//			} else {
//				len = sprintf((char*) retBuffer, "AT+RETSETMAC=OK+%s ----\r\n", g_atconfig.macString);
//			}
//		} else {
//			len = sprintf((char*) retBuffer, "AT+RETSETMAC=ERROR\r\n");
//		}
//	} else {
//		len = sprintf((char*) retBuffer, "AT+RETSETMAC=ERROR\r\n");
//	}
//	XlinkUartSend((unsigned char *) retBuffer, len);
//	return __X_AT_OK__;
//}

