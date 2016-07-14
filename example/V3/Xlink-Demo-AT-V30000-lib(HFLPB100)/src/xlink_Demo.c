/*
 * xlink_AppPassthrough.c
 *
 *  Created on: 2014年12月22日
 *      Author: john
 */

#include "xlink_demo.h"
#include "xlink_config.h"
#include "xlink_at.h"
#include "stdarg.h"
#include "xlink_ota_hf.h"
#include "airkissv2.h"

#ifndef XLINK_FUNC
#define XLINK_FUNC
#endif

#define TICKS_DIFF(cur, prev) ((cur) >= (prev)) ? ((cur)-(prev)) : ((0xFFFFFFFF-(prev))+(cur)+1)

#define  XLINK_PRODUCT_ID  "ca36dd09c98e4dab878d503b787c43af"
#define XLINK_PRODUCT_KEY  "21bbc1c21e9d42dd8ddd7d66227b6ac2"

//#define  XLINK_PRODUCT_ID  "7b9dfe1148cf4901a8b2579869a01dda"
//#define XLINK_PRODUCT_KEY  "9a2f67a15d0f4add8f5388635269abf6"

XLINK_USER_CONFIG user_config;

//#define PWM3		(HFGPIO_F_USER_DEFINE+5)
//#define PWM4		(HFGPIO_F_USER_DEFINE+6)
//#define PWM5		(HFGPIO_F_USER_DEFINE+7)

//全局变量

XLINK_LOCAL_STA g_AllSta;
AT_CONFIG g_atconfig;

char m_pID[33];

uint8_t Isconnectserver = 0;

//datapoint V2
typedef enum 
{
	DP_BYTE = 0x00,
	DP_INT16 = 0x10,
	DP_UINT16 = 0x20,
	DP_INT32 = 0x30,
	DP_UINT32 = 0x40,
	DP_INT64 = 0x50,
	DP_UINT64 = 0x60,
	DP_FLOAT = 0x70,
	DP_DOUBLE = 0x80,
	DP_STRING = 0x90,
}DATAPOINTTYPE;
typedef struct 
{
	uint8_t temperature;
	uint8_t pressure;
	uint16_t id;
	uint32_t num;
	char*  name;
}MYDATAPOINT;
char* MyName = "电饭锅electric cooker";
MYDATAPOINT mydp;

//volatile UART_SEND_PACK uart_send_pack[UART_PACK_MAX];
//volatile int uart_send_pos = 0;

#define UARTBUF_MAX_LEN 2048
volatile uint8_t uartbuf[UARTBUF_MAX_LEN];
volatile uint16_t uartbufhead = 0;
volatile uint16_t uartbufwear = 0;

volatile uint8_t tcpsendbuf[1024];
volatile uint16_t tcpsenbuflen = 0;

void UartBufAddData(uint8_t *s ,uint16_t len);
void UartBufOutData(uint8_t *s ,uint16_t *len);

static XLINK_FUNC void xlink_demo_work_init(void);


XLINK_FUNC void xlink_recv_uart_data(unsigned char *data, unsigned int datalen) {
	int ret = 0;
	if (datalen > 3 && datalen < 100) {
		if (data[0] == 'A' && data[1] == 'T' && data[2] == '+') {
			unsigned char at_buffer[100];
			memset(at_buffer, 0, 100);
			memcpy(at_buffer, data, datalen);
			at_buffer[datalen] = '\0';
			ret = xlink_process_at_cmd(at_buffer, datalen);
			if (ret != 0) {
				return;
			}
		}
	}
	UartBufAddData(data,datalen);
}

void pipe1_call(unsigned char * data, unsigned int datalen, x_uint32 device_id, x_uint8 *opt) {
	//u_printf("recv tcp pipe package len %d  deviceid %d \r\n", datalen, device_id);
	XlinkUartSend(data, datalen);
}

static void udp_pipe_call(unsigned char *data, unsigned int datalen, xlink_addr *addr) {
	//u_printf("recv udp pipe package len %d  \r\n", datalen);
	XlinkUartSend(data, datalen);
}

/**
 * Date: 2014 12 30
 * Description:
 * 		app状态回调函数
 * Parameters:
 * 		status :状态
 * Return:
 * 		void
 */
static XLINK_FUNC void app_status(XLINK_APP_STATUS status) {

	switch (status) {
//	case XLINK_WIFI_STA_PRO_TESTCOMPLETE:
//		break;
	case XLINK_WIFI_STA_APP_CONNECT: /*用户连接*/
		//u_printf("****new app connect****\r\n");
		break;
	case XLINK_WIFI_STA_APP_DISCONNECT:/*用户离开*/
		//u_printf("**** app disconnect****\r\n");
		break;
	case XLINK_WIFI_STA_APP_TIMEOUT:/*通讯超时*/
		//u_printf("**** app timeout****\r\n");
		break;
	case XLINK_WIFI_STA_CONNECT_SERVER:
		//u_printf("**** tcp connect to server success****\r\n");
		
		break;
	case XLINK_WIFI_STA_DISCONNCT_SERVER:
		hfgpio_fset_out_high(HFGPIO_F_STATE);
		Isconnectserver = 0;
		u_printf("**** tcp  disconnect server ****\r\n");
		if (g_AllSta.bit.isConnectedServer == 1) {
			g_AllSta.bit.isConnectedServer = 0;
			g_AllSta.bit.isNeedSend = 1;
		}
		break;
	case XLINK_WIFI_STA_LOGIN_SUCCESS:
		u_printf("**** device login success****\r\n");
		g_AllSta.bit.isConnectedServer = 1;
		g_AllSta.bit.isNeedSend = 1;
		g_AllSta.bit.isNeedSendServerSta = 1;
		hfgpio_fset_out_low(HFGPIO_F_STATE);
	Isconnectserver = 1;
		break;
	}

}

static void xlinkSetUartRate384(void) {
//	int i =0;
//	for (i =0 ;i< UART_PACK_MAX;i++) {
//		uart_send_pack[i].flag = 0;
//	}
	
	char buffer[64];
	hfat_send_cmd("AT+UART\r\n", sizeof("AT+URAT\r\n"), buffer, 64);
	if (strcmp(buffer + 4, "115200,8,1,None,NFC") != 0) {
		//ret =
		hfat_send_cmd("AT+UART=115200,8,1,NONE,NFC,0\r\n", sizeof("AT+UART=115200,8,1,NONE,NFC,0\r\n"), buffer, 64);
		
		msleep(1000);
		hfsys_softreset();
	}
	hfat_send_cmd("AT+UARTFL=512\r\n", sizeof("AT+UARTFL=512\r\n"), buffer, 64);
	char *cmdS = "AT+UARTFT=100\r\n";
	hfat_send_cmd(cmdS, xlink_strlen(cmdS), buffer, 64);
	cmdS = "AT+NDBGL=0\r\n";
	hfat_send_cmd(cmdS, xlink_strlen(cmdS), buffer, 64);
	
//	char *macStr = "AT+WSMAC=8888,ACCF2359DDA2\r\n";
//	hfat_send_cmd(macStr, xlink_strlen(macStr), buffer, 64);
	
	char *cmdMode = "AT+WMODE=APSTA\r\n";
	hfat_send_cmd(cmdMode, xlink_strlen(cmdMode), buffer, 64);
}

XLINK_FUNC void xlink_save_at_config(void) {
	XlinkWriteAtConfig(&g_atconfig);
}

XLINK_FUNC int xlink_demo_init(void) {
	xlinkSetUartRate384();
	g_atconfig.flag.byte = 0;
	XlinkReadAtConfig(&g_atconfig);
	xlink_demo_work_init();
	return 1;
}

XLINK_FUNC int XlinkUartSend(unsigned char *Buffer, unsigned short BufferLen) {
	g_AllSta.bit.isSendUartData = 1;
	hfuart_send(HFUART0, (char*) Buffer, BufferLen, 5);
	return BufferLen;
}

static char log_buf[200];
int xlink_debug_fn_x(const char* format, ...) {
	xlink_memset(log_buf, 0, 200);
	va_list args;
	va_start(args, format);
	vsnprintf(log_buf, 200, format, args);
	va_end(args);
	u_printf("\r\n==>::%s\r\n", log_buf);
	return 0;
}


static void upgrade_task(XLINK_UPGRADE *data) {
	char urlBuf[256];
	if (data->urlLength <= 0 || data->urlstr == NULL ) {
		u_printf("\r\n----get upgrade url failed\r\n");
		return;
	}
	memset(urlBuf, 0, 256);
	memcpy(urlBuf, data->urlstr, data->urlLength);
	xlink_update_as_http(urlBuf,"wifixx",data);
}

XLINK_FUNC void static time_callback(XLINK_SYS_TIME *time) {
	u_printf("xlink updata current time\r\n");
}

static void SetDataPiont(unsigned char *data, int datalen)
{
    //XlinkUartSend(data, datalen);
}
static void GetAllDataPiont(unsigned char *data, int *datalen)
{
	//XLINK_DATAPOINT_MAX_BYTES
	int i = 0;
	
	data[i++] = 0;
	data[i++] = DP_BYTE;
	data[i++] = 1;
	data[i++] = mydp.temperature;
	
	data[i++] = 1;
	data[i++] = DP_BYTE;
	data[i++] = 1;
	data[i++] = mydp.pressure;
	
	data[i++] = 2;
	data[i++] = DP_INT16;
	data[i++] = 2;
	data[i++] = (mydp.id >> 8) & 0xff;
	data[i++] = (mydp.id >> 0) & 0xff;
	
	data[i++] = 3;
	data[i++] = DP_INT32;
	data[i++] = 4;
	data[i++] = (mydp.num >> 24) & 0xff;
	data[i++] = (mydp.num >> 16) & 0xff;
	data[i++] = (mydp.num >> 8) & 0xff;
	data[i++] = (mydp.num >> 0) & 0xff;
	
	data[i++] = 4;
	data[i++] = DP_STRING;
	data[i++] = strlen(mydp.name);
	memcpy(&data[i],mydp.name,strlen(mydp.name));
	i = i + strlen(mydp.name);
	
	*datalen = i;
}
static XLINK_FUNC void xlink_demo_work_init(void) {

	int i = 0;
	char proKey[33];
	unsigned char temp;
	user_config.tcp_pipe2 = NULL;
	user_config.tcp_pipe = pipe1_call;
	user_config.udp_pipe = udp_pipe_call;
	user_config.status = app_status;
	user_config.wifi_type = 1;
	user_config.DebugPrintf = xlink_debug_fn_x;
	user_config.in_internet = 1;
    
	user_config.wifisoftVersion = 2;
	user_config.upgrade = upgrade_task;
	user_config.server_time = time_callback;	
    
    user_config.mcuHardwareSoftVersion = 1;
    user_config.mcuHardwareVersion = 1;
	
	//datapoint must be initialized,if use V2:set callback ,if use V1:set NULL.
	user_config.Xlink_GetAllDataPoint = GetAllDataPiont;
	user_config.Xlink_SetDataPoint = SetDataPiont;
    
    user_config.pipetype = 0;
    user_config.devicetype = 0x0001;

	xlinkConfigInit(&user_config);
	user_config.maclen = 6;

	hfnet_set_udp_broadcast_port_valid(5986, 5988);
	XlinkReadProductIDKEY(m_pID, proKey);
	m_pID[32] = '\0';
	proKey[32] = '\0';


	for (i = 0; i < 32; i++) {
		temp = m_pID[i];
		if (temp <= '9' && temp >= '0') {
		} else if (temp > 'f' || temp < 'a') {
			memcpy(m_pID, XLINK_PRODUCT_ID, 32);
			memcpy(proKey, XLINK_PRODUCT_KEY, 32);
			break;
		}
	}
	for (i = 0; i < 32; i++) {
		temp = proKey[i];
		if (temp <= '9' && temp >= '0') {
		} else if (temp > 'f' || temp < 'a') {
			memcpy(m_pID, XLINK_PRODUCT_ID, 32);
			memcpy(proKey, XLINK_PRODUCT_KEY, 32);
			break;
		}
	}

	if (XlinkSystemInit(m_pID, proKey, &user_config) == 0) {
	} else {
		
//		XlinkSystemSetPassword("8888");
		XlinkGetServerTime();
		//XlinkSystemSetWifiStatus(0);
	}
	
	//my datapoint init
	mydp.id = 12888;
	mydp.num = 10000000;
	mydp.name = MyName;
	mydp.pressure = 50;
	mydp.temperature = 123;
    
    XlinkPorcess_UDP_Enable();

	//not connect to server
	hfgpio_fset_out_high(HFGPIO_F_STATE);
    
}



XLINK_FUNC void xlink_demo_loop(void) {

	time_t lop = 0, updateDP = 0;
	int temp = 0;
	uint8_t data[50];
	int datalen = 0;
	
	//启动发送一个状态
	g_AllSta.bit.isNeedSend =1;
	while (1) {
		time_t t = time(NULL);
		g_AllSta.bit.isSendUartData = 0;

		XlinkSystemLoop(t, 30);
		
		tcpsenbuflen = 800;
		UartBufOutData((uint8_t *)tcpsendbuf,(uint16_t *)(&tcpsenbuflen));
		if (tcpsenbuflen >0 ) {
			XlinkSendTcpPipe2((void *)tcpsendbuf, tcpsenbuflen);
			XlinkSendUdpPipe((void *)tcpsendbuf, tcpsenbuflen, NULL);
		}

		if (g_AllSta.bit.isSendUartData == 0) {
			if (g_AllSta.bit.isNeedSend == 1) {
				g_AllSta.bit.isNeedSend = 0;
				xlink_send_uart_sta();
			}
		}


		temp = TICKS_DIFF(t,lop);
		if (temp > 600) {
			lop = t;
			XlinkGetServerTime();
		}
		
		//datapoint
//		temp = TICKS_DIFF(t,updateDP);
//		if (temp > 2) {
//			updateDP = t;
//			if (Isconnectserver) {
//				mydp.pressure++;
//				mydp.temperature++;
//                mydp.id++;
//                mydp.num++;
//				GetAllDataPiont(data,&datalen);
//                
//				Xlink_UpdateDataPoint(data, datalen,0);
//			}
//		}
		msleep(30);
	}
}

void UartBufAddData(uint8_t *s ,uint16_t len)
{
	int i = 0;
	for (i = 0; i < len; i++) {
		if ((uartbufwear + 1) < UARTBUF_MAX_LEN) {
			if ((uartbufwear + 1) != uartbufhead) {
				uartbufwear++;
				uartbuf[uartbufwear] = s[i];
			}
			else {
				//add null
				return;
			}
		}
		else if(uartbufhead != 0) {
			uartbufwear = 0;
			uartbuf[uartbufwear] = s[i];
		}
		else {
			//add null
			return;
		}
	}	
}
void UartBufOutData(uint8_t *s ,uint16_t *len)
{
	int tem = 0;	
	int i = 0;
	for (i = 0; i < *len; i++) {
		if ((uartbufhead + 1) < UARTBUF_MAX_LEN) {
			if ((uartbufhead) != uartbufwear) {
				uartbufhead++;
				s[tem++] = uartbuf[uartbufhead];
			}
			else {
				//add null
				*len = tem;
				return;
			}
		}
		else if(uartbufwear != 0) {
			uartbufhead = 0;
			s[tem++] = uartbuf[uartbufhead];
		}
		else {
			//add null
			*len = tem;
			return;
		}
	}
	*len = tem;	
}
 #ifndef __LPT200__
extern airkiss_config_t akconf;


void USER_FUNC airkiss_domain_lop(void *args) {
//airkiss
#define  DEVICE_TYPE    "gh_d62c3dfd12ac"
    int ret = -1;
		xlink_set_fd ak_fd_set;
		struct timeval timeoutal;
	
		uint32_t  akcounttime = 0;
		unsigned char ak_buf[200];
		unsigned short  ak_buf_len = 200;   

    const int port=12476;
    uint32_t sin_len;  
    char message[256];  
    int revmessagelen = 0;  

    int deviceid = 0;
		char strdeviceid[20];
	
		/* server addr */
    struct sockaddr_in addrto;  
		/* client addr */
    int socket_descriptor;  
    struct sockaddr_in sin;  
		
		const int opt = 1;
	
		//debug airkiss version
		u_printf("airkiss_version is %s\r\n",airkiss_version());
		
		//get device id
    deviceid = XlinkSystemGetDeviceID();
    while(deviceid == 0) {
        msleep(1000);
        deviceid = XlinkSystemGetDeviceID();
    }    
    sprintf(strdeviceid,"%d",deviceid);
    u_printf("******************************device id is %s****************************\r\n",strdeviceid); 

    /* server addr */
    memset(&addrto,0, sizeof(struct sockaddr_in));  
    addrto.sin_family=AF_INET;  
    addrto.sin_addr.s_addr=0xffffffff;  
    addrto.sin_port=htons(port);  

		/* client addr */
    memset(&sin,0,sizeof(sin));  
    sin.sin_family=AF_INET;  
    sin.sin_addr.s_addr=htonl(INADDR_ANY);  
    sin.sin_port=htons(port);  
    sin_len=sizeof(sin);  
		
    //socket       
		socket_descriptor=xlink_socket(AF_INET,SOCK_DGRAM,0); 
		while(socket_descriptor <1) {
			u_printf("udp creat fail!\r\n");
			msleep(2000);
			socket_descriptor =xlink_socket(AF_INET,SOCK_DGRAM,0); 	
		}
    xlink_setsockopt(socket_descriptor, SOL_SOCKET, SO_BROADCAST, (char *)&opt, sizeof(opt));	
    bind(socket_descriptor,(struct sockaddr *)&sin,sizeof(sin));  	
		
		//set upd
		FD_SET(socket_descriptor, &ak_fd_set);
		timeoutal.tv_sec = 0;
		timeoutal.tv_usec = 30000;
		
    while(1)
    {  
				msleep(70);
				//send login packet
        akcounttime++;
        if (akcounttime >= 30) {
            ak_buf_len = sizeof(ak_buf);
            ret = airkiss_lan_pack(AIRKISS_LAN_SSDP_NOTIFY_CMD,DEVICE_TYPE,strdeviceid,0,0,ak_buf,&ak_buf_len,&akconf);
            if (ret != AIRKISS_LAN_PAKE_READY) {
               u_printf("t Pack lan packet error!\r\n");
            }
            else {
							if(sendto(socket_descriptor, ak_buf, ak_buf_len,0,(struct sockaddr*)&addrto,sizeof(addrto)) != 0) 
							{
								 u_printf("t Send message success.\r\n"); 
							}
							else {
								 u_printf("t Send message failed.\r\n");
							}
            }
            akcounttime = 0;
        }
			
				//recevie packet
				ret = xlink_select(socket_descriptor + 1, &ak_fd_set, NULL, NULL, &timeoutal);
        if ((ret > 0) && FD_ISSET(socket_descriptor, &ak_fd_set)) {
					//data is ready
					revmessagelen = recvfrom(socket_descriptor,message,sizeof(message) - 1,0,(struct sockaddr *)&sin,&sin_len); 
					if (revmessagelen > 0) {             
							ret = airkiss_lan_recv(message,revmessagelen,&akconf);
							if (ret == AIRKISS_LAN_SSDP_REQ) {	
								ak_buf_len = sizeof(ak_buf);
								ret = airkiss_lan_pack(AIRKISS_LAN_SSDP_RESP_CMD,DEVICE_TYPE,strdeviceid,0,0,ak_buf,&ak_buf_len,&akconf);
								if (ret != AIRKISS_LAN_PAKE_READY) {
									u_printf("Pack lan packet error!\r\n");
								}
								else 
								{
									if(sendto(socket_descriptor, ak_buf, ak_buf_len,0,(struct sockaddr*)&sin,sizeof(sin)) != 0) 
									{
										u_printf("Send message success.\r\n");  
									}
									else {
										u_printf("Send message failed.\r\n"); 
									}
								}
							}
							else {
								u_printf("Pack is not ssdq req!\r\n");
							}
					}		
				}					
    }    
}
#endif
