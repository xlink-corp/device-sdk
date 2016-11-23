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
#include "xlink_All_Device.h"


#define __ALL_DEVICE__          1
#define __XDEBUG__           	1
#define __XLINK_VERSION__       34700
#define __XLINK_BUFFER_PIPE__   1024


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
		
		//TCP服务器消息通知
		void (*tcp_notify)(unsigned short messagetpye,unsigned char * data, unsigned int datalen);
		//TCP pipe数据发送回调,handle与发送handle对应，val为0表示失败，1表示成功
		void (*tcp_pipe_send_cb)(unsigned short handle,unsigned char val);
		//TCP pipe2数据发送回调,handle与发送handle对应，val为0表示失败，1表示成功
		void (*tcp_pipe2_send_cb)(unsigned short handle,unsigned char val);
		//udp pipe数据发送回调,handle与发送handle对应，val为0表示失败，1表示成功
		void (*udp_pipe_send_cb)(unsigned short handle,unsigned char val);
		//TCP 数据端点更新发送回调,handle与发送handle对应，val为0表示失败，1表示成功
		void (*tcp_datapoint_send_cb)(unsigned short handle,unsigned char val);

		unsigned char *tcpRecvBuffer;
		unsigned int tcpRecvBuuferLength;
		int (*send_udp)(xlink_addr *addr, unsigned char *data, unsigned int datalen);
		int (*send_tcp)(unsigned char *data, unsigned int datalen);
		void (*setServerStatus)(unsigned char stat,unsigned char is80Port);
		void (*process_udp_data)(unsigned char * Buffer, unsigned int BufferLen, xlink_addr *addrBro);
		void (*process_tcp_data)(unsigned char * data, unsigned int datalen, x_uint32 bodylen);

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
