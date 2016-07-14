#ifndef _XLINK_TYPE_
#define _XLINK_TYPE_

#define xlink_true 0x01
#define xlink_false 0x00

#define xlink_success 0x00
#define xlink_error  0x01

#define XLINK_SIZE_17 17
#define XLINK_SIZE_33 33
#define XLINK_MAC_SIZE 6

typedef unsigned char x_bool;
typedef char x_int8;
typedef unsigned char x_uint8;
typedef short x_int16;
typedef unsigned short x_uint16;
typedef int x_int32;
typedef unsigned int x_uint32;
typedef int x_float32;
typedef long x_long32;

#undef NULL
#if defined(__cplusplus)
#define NULL 0
#else
#define NULL ((void *)0)

#endif


typedef int (*xlink_debug_fn)(const char* format, ...);

typedef struct XLINK_SELECT {
	int fd;
	int (*recv_event)(int fd);
} XLINK_SELECT;


typedef enum XLINK_WIFI_STATUS {
	XLINK_WIFI_CONNECTING, //connect wifi
	XLINK_WIFI_CONNECT_TIMEROUT, //connect wifi timeout
	XLINK_WIFI_CONNECT_SUCCESS, //connect wifi success
	XLINK_WIFI_DISCONNECT, //
	XLINK_WIFI_GET_IPADDRING, //
	XLINK_WIFI_GET_IPADDR_SUCCESS, //
} XLINK_WIFI_STATUS;

typedef enum XLINK_ERROR {
	XLINK_ERROR_UDP_CREATE, //
	XLINK_ERROR_EVENT_TIMEOUT, //
	XLINK_ERROR_UART_OPEN_FAILED, //
	XLINK_ERROR_NOT_WORK_TATUS, //
} XLINK_ERROR;

/**
 * flash 存储结构
 */
typedef struct XLINK_CONFIG_T {
	union {/*保存配置信息*/
		unsigned char All;
		struct {
			unsigned char isActivation :1;/*是否激活*/
			unsigned char isUpgrade :1;/*是否升级*/
			unsigned char isSaveDevicekey :1;/*是否保存了device key*/
			unsigned char isAppSetName :1;/*APP更改名字*/
			unsigned char isChangedPassword :1;/*是否修改密码*/
			unsigned char isSetPassword :1;/*是否已经设定密码*/
			unsigned char isAppSetPasswork :1;/*是否是APP已经设定密码,App设定密码后设备不能修改密码*/
			unsigned char res :1;
		} Bit;
	} flag;
	unsigned char  Deviceid[4];/*保存Deviceid*/
	unsigned short CurrentSoftVersion;
} xlink_SdkConfig;




//typedef enum XLINK_DATA_TYPE {
//	XLINK_NONE = 0, //
//	XLINK_BYTE = 1,/*1byte*/
//	XLINK_INT16 = 2,/*2byte*/
//	XLINK_INT32 = 3, /*4byte*/
//} XLINK_DATA_TYPE;

//typedef struct XLINK_DATAPOINT {
//	XLINK_DATA_TYPE type;/*数据类型*/
//	unsigned char index; /*索引下标*/
//	unsigned char used; /*是否有意义*/
//	unsigned char flag; /*在网络通信中标识*/
//	unsigned short DataSize;/*此数据的大小  字符串类型每次修改数据需要在字符串长度上+2 （加上标识数据长度的2yte）*/
//	unsigned int v_data;
//} XLINK_DATAPOINT;

typedef enum XLINK_APP_STATUS {
	XLINK_WIFI_STA_PRO_TESTCOMPLETE=0X02,//产测完成
	XLINK_WIFI_STA_CONNECT_SERVER = 0X04,  //链接上云服务器
	XLINK_WIFI_STA_DISCONNCT_SERVER = 0X08,  //与云服务器断开链接
	XLINK_WIFI_STA_APP_CONNECT = 0X10,  //APP连接
	XLINK_WIFI_STA_APP_DISCONNECT = 0X20,  //APP 断开连接
	XLINK_WIFI_STA_APP_TIMEOUT = 0X40,  //APP 超时
	XLINK_WIFI_STA_LOGIN_SUCCESS = 0X80,  //登录公网服务器成功
} XLINK_APP_STATUS;

/**
 * 接收到服务器推送升级信息
 */
typedef struct XLINK_UPGRADE_FUN {
	unsigned int fileSize;
	char *checkStr;
	unsigned int checkStrLength;
	char *urlstr;
	unsigned short urlLength;
	unsigned char mCheckFlag;
	unsigned char mHardVersion;
	unsigned short mSoftVersion;
    unsigned short mCurrentVersion;
	unsigned char isWifi;
} XLINK_UPGRADE;

typedef struct XLINK_TIME {
	unsigned short year;
	unsigned char mon;
	unsigned char day;
	unsigned char week;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
	short zones;
} XLINK_SYS_TIME;




#endif

