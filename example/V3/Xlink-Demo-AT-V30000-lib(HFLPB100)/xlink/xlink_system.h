/*
 * xlink_system.h
 *
 *  Created on: 2014骞�2鏈�9鏃�
 *      Author: john
 *
 * 绯荤粺鏇存敼娉ㄦ剰浜嬮」锛�
 *     1銆佹绯荤粺鏈�鑳藉鏀寔16涓鐐规暟鎹�
 *     2銆佸綋鍓嶆暟鎹鐐筬lag[4] 瀹氫箟浜�涓紦瀛樼┖闂淬�濡傞渶澧炲姞绔偣灏遍渶瑕佸鍔爁lag鐨勭┖闂�
 */

#ifndef XLINK_SYSTEM_H_
#define XLINK_SYSTEM_H_
#ifdef  __cplusplus
extern "C" {
#endif
#include "Xlink_Head_Adaptation.h"

#if __ALL_DEVICE__
    enum TCP_ {
        E_TCP_SUCCESS, E_TCP_CONTINUE, //
        E_TCP_HEAD_ERROR, //
        E_TCP_NO_MEM,
        E_TCP_READ_MEM_ERROR,
    };
#endif

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

extern XLINK_FUNC void Xlink_Close_Net(void);

extern XLINK_FUNC int XlinkProcessTCPData(void);
extern XLINK_FUNC int XlinkPushData(unsigned char * data, x_int16 datalen);
extern XLINK_FUNC void XlinkProcessUdpData( unsigned char * Buffer, unsigned int BufferLen, xlink_addr *addr);
#if __ALL_DEVICE__
extern void XLINK_FUNC setServerStatus_(unsigned char stat,unsigned char is80Port);
#endif
#ifdef  __cplusplus
}
#endif
#endif /* XLINK_SYSTEM_H_ */
