/*
 * Xlink_Head_Adaptation.h
 *
 *  Created on: 2015年3月9日
 *      Author: John
 */

#ifndef SRC_XLINK_HEAD_ADAPTATION_H_
#define SRC_XLINK_HEAD_ADAPTATION_H_
#ifdef  __cplusplus
extern "C" {
#endif
#include "xlink_type.h"

#define HF_SDK                  1//汉枫
#define HF_SDK_A21              0
#define MARVELL_SDK          	0//marvell
#define QCA4004             	0//高通4004
#define REALTEK              	0//realtek
#define REALTEK_8711            0
#define NL6621                  0//新岸线
#define __LWIP__ESP_8266     	0//
#define __HED_10W07SN__         0//联盛德
#define __MT7681__           	0
#define __LINUX__             	0
#define __STM32F107__           0

#define __LSD4WF_2MD05101__     0   //LI ER DA
#define __RTOS_STM32F103__      0
#define __RTOS_STM32F107__      0
#define __STM32F103_UIP__       0
#define __MXCHIP__             	0

#define __ALL_DEVICE__          0

#define __XDEBUG__           	1

#define __XLINK_VERSION__       33000

#define __XLINK_BUFFER_PIPE__   1024

#define __XLINK_STAND_HAIMAN__   0  //海曼科技部署

//#define TEST_SERVER 

#if HF_SDK
#include "xlink_HF.h"
#endif


#define XLINK_MAC_LEN_MAX 32
#define XLINK_MAC_LEN_MIN 1

typedef struct XLINK_CALLBACK_FUN {
	//接收服务器广播的回调函数
	void (*tcp_pipe2)(unsigned char * Buffer, unsigned int BufferLen, x_uint8 *opt);
	//接收APP通过服务器发送的数据的回调函数
	void (*tcp_pipe)(unsigned char * Buffer, unsigned int BufferLen, x_uint32 AppID, x_uint8 *opt);
	//接收APP通过本地发送的数据的回调函数
	void (*udp_pipe)(unsigned char * Buffer, unsigned int BufferLen,xlink_addr *fromAddr);

	//void (*udp_proTest)(const unsigned char *Buffer,const unsigned char BufferLen,const unsigned short data_id,xlink_addr *fromAddr);
	//SDK 内部写配置回调函数，需要将此数据写入flash
	int (*writeConfig)(char *Buffer, unsigned int BufferLen);
	//SDK 内部读本地的配置文件，需要读出flash的配置数据
	int (*readConfig)(char *Buffer, unsigned int BufferLen);
	//SDK 内部状态信息回调
	void (*status)(XLINK_APP_STATUS status);
	//SDK 收到服务器升级信息回调
	void (*upgrade)(XLINK_UPGRADE *data);
	//SDK 收到服务器同步时间信息回调
	void (*server_time)(XLINK_SYS_TIME *time_p);
	//SDK 内部日志输出回调
	xlink_debug_fn DebugPrintf;
	//WiFi类型
	unsigned char wifi_type;
	//WiFi版本
	unsigned short wifisoftVersion;
	x_uint8 mcuHardwareVersion; /*Hardware Version*/
	x_uint16 mcuHardwareSoftVersion;/*Software Version*/
	//端点的版本
	//unsigned short endpointVersion;//端点的版本
	//SDK 内部是否使用TCP公网连接
	unsigned char in_internet;
	//设备的MAC地址
    unsigned short maclen;
	unsigned char mac[XLINK_MAC_LEN_MAX];
    
    //硬件协议透传协议选择,0表示普通透传，1表示透传内容为硬件通讯协议。
    unsigned char pipetype;
    //设备类型
    unsigned short devicetype;



#if  __LWIP__ESP_8266 || __MT7681__ || __STM32F107__ || __STM32F103_UIP__ || __ALL_DEVICE__
    unsigned char *tcpRecvBuffer;
    unsigned int tcpRecvBuuferLength;
    int (*send_udp)(xlink_addr *addr, unsigned char *data, unsigned int datalen);
    int (*send_tcp)(unsigned char *data, unsigned int datalen);
    void (*setServerStatus)(unsigned char stat,unsigned char is80Port);
    void (*process_udp_data)(unsigned char * Buffer, unsigned int BufferLen, xlink_addr *addrBro);
    void (*process_tcp_data)(unsigned char * data, unsigned int datalen, x_uint32 bodylen);
#endif


	//V2 datapoint
	//datapoint format:[datapoint index:1byte][datalen:2bytes(H L)][data:datalen bytes]...
	void (*Xlink_SetDataPoint)(unsigned char *data, int datalen);//app->wifi,you can update datapoints by this buf
	void (*Xlink_GetAllDataPoint)(unsigned char *data, int *datalen);//add all datapoint data to the buf,The maximum length is XLINK_DATAPOINT_MAX_BYTES
} XLINK_USER_CONFIG;
extern XLINK_FUNC void XlinkPorcess_UDP_Enable(void);
extern XLINK_FUNC void XlinkPorcess_UDP_Disable(void);
extern XLINK_FUNC void XlinkReSetSDK(void);

#ifdef  __cplusplus
}
#endif
#endif /* SRC_XLINK_HEAD_ADAPTATION_H_ */
