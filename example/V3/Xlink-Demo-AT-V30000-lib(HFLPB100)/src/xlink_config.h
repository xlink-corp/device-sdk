/*
 * xlink_config.h
 *
 *  Created on: 2014年12月22日
 *      Author: john
 */

#ifndef XLINK_CONFIG_H_
#define XLINK_CONFIG_H_

#include "xlink_demo.h"
#include "xlink_at.h"

extern void xlinkConfigInit(XLINK_USER_CONFIG *config);

x_int32 XlinkGetDeviceMac(x_uint8 *mac);

extern int XlinkReadProductIDKEY(char *proid, char *proKey);
extern int XlinkWriteProductIDKEY(char *proid, char *proKey);
extern int XlinkWriteAtConfig(AT_CONFIG *config);
extern int XlinkReadAtConfig(AT_CONFIG *config);
XLINK_FUNC void mac_to_hex(char ch_h, char ch_l, x_uint8 *for_num);

#endif /* XLINK_CONFIG_H_ */
