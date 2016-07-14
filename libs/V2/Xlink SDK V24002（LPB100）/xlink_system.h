/*
 * xlink_system.h
 *
 *  Created on: 2014年12月19日
 *      Author: john
 *
 * 系统更改注意事项：
 *     1、次系统最多能够支持16个端点数据。
 *     2、当前数据端点flag[4] 定义了4个缓存空间。如需增加端点就需要增加flag的空间
 */

#ifndef XLINK_SYSTEM_H_
#define XLINK_SYSTEM_H_

#include "Xlink_Head_Adaptation.h"

extern XLINK_FUNC char *XlinkSystemVersion(void);

extern XLINK_FUNC x_bool XlinkSystemInit(char * product_id, char * product_key, XLINK_USER_CONFIG *config);

extern XLINK_FUNC void XlinkSystemSetWifiStatus(unsigned char status);

extern XLINK_FUNC void XlinkSystemLoop(xsdk_time_t c_time, x_int32 timeout_ms);

extern XLINK_FUNC void XlinkSystemSetLocalScanStatus(x_bool status);

extern XLINK_FUNC void XlinkSystemSetPassword(char *password);

extern XLINK_FUNC void XlinkSystemClearPassword(char *password);

extern XLINK_FUNC void XlinkSystemSetDeviceName(char *NameStr);
extern XLINK_FUNC void XlinkSystemSetDomain(const char *domain);

extern XLINK_FUNC void XlinkSystemReSet(void);

extern XLINK_FUNC void XlinkNetInit(void);

extern XLINK_FUNC x_int32 XlinkSendTcpPipe(const unsigned char * data,const unsigned int datalen, x_uint32 to_id);

extern XLINK_FUNC x_int32 XlinkSendTcpPipe2(const unsigned char * data,const unsigned int datalen);

extern XLINK_FUNC x_int32 XlinkSendUdpPipe(const unsigned char *data, const unsigned int datalen, xlink_addr *fromAddr);

extern XLINK_FUNC void XlinkGetServerTime(void);
extern XLINK_FUNC int XlinkGetSystemTime(XLINK_SYS_TIME *pTime);

extern XLINK_FUNC void XlinkSystemInitEvent(XLINK_SELECT *event);

extern XLINK_FUNC int XlinkSystemTcpLoop(void);
extern XLINK_FUNC int xsdk_system_getMacStr(char *RetMacBuffer, const int bufflen);

extern XLINK_FUNC int XlinkProTestSendData(const char *data,const unsigned char datalen,const unsigned char data_id,xlink_addr *toAddr);

extern XLINK_FUNC int XlinkProTestSendCloseRequest(xlink_addr *toAddr);

extern XLINK_FUNC int XlinkSystemProtesting(void);
extern XLINK_FUNC int XlinkSystemGetDeviceID(void);

extern XLINK_FUNC void Xlink_UpdateDataPoint(unsigned char* data, x_uint16 datalen,unsigned char flag);

extern XLINK_FUNC void XlinkSetACK(int accesskey);
extern XLINK_FUNC int XlinkGetACK(void);

extern XLINK_FUNC  void xlink_tcp_send_upgrade(unsigned char RetCode,unsigned short Upver,unsigned short currentVer) ;
#endif /* XLINK_SYSTEM_H_ */
