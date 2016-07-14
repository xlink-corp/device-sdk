/*
 * xlink_config.c
 *
 *  Created on: 2014年12月22日
 *      Author: john
 */

#include "xlink_config.h"
#include "xsdk_config.h"

#define XLINK_USR_BIN_ADDR_CFG 0 //length is: XLINK_CONFIG_BUFFER_SIZE__
#define XLINK_USR_BIN_ADDR_PDID  XLINK_CONFIG_BUFFER_SIZE__  //length is 64
#define XLINK_USR_BIN_ADDR_AT  (XLINK_USR_BIN_ADDR_PDID + 64)  //length is 50

static int XlinkConfigReadConfig(x_int8 *retbuffer, unsigned int buflen);
static int XlinkConfigWriteConfig(x_int8 *data, unsigned int len);

/**
 * Date: 2014 12 30
 * Description:
 * 		配置初始化
 * Parameters:
 * 		void
 * Return:
 * 		void
 */
//char buf[120];
void xlinkConfigInit(XLINK_USER_CONFIG *config) {
	config->readConfig = XlinkConfigReadConfig;
	config->writeConfig = XlinkConfigWriteConfig;
	XlinkGetDeviceMac(config->mac);

	//memset(buf,0,120);
}

/**
 * Date: 2014 12 30
 * Description:
 * 		读取配置信息
 * Parameters:
 * 		index    :配置索引下标
 * 		retbuffer:返回的数据
 * Return:
 * 		返回数据的长度
 */
static int XlinkConfigReadConfig(x_int8 *retbuffer, unsigned int buflen) {
	//memcpy(retbuffer,buf,buflen);
	x_int16 ret = hffile_userbin_read(XLINK_USR_BIN_ADDR_CFG, retbuffer, buflen);
	//int ret =buflen;
	return ret;
}

/**
 * Date: 2014 12 30
 * Description:
 * 		写配置信息
 * Parameters:
 * 		index :配置索引下标
 * 		data  :数据
 * 		len   :数据长度
 * Return:
 * 		返回写入数据的长度
 * 		0没有写入数据
 */
static int XlinkConfigWriteConfig(x_int8 *data, unsigned int len) {
	//memcpy(buf,data,len);
	x_int16 ret = hffile_userbin_write(XLINK_USR_BIN_ADDR_CFG, data, len);
	//int ret = len;
	return ret;
}

int XlinkWriteProductIDKEY(char *proid, char *proKey) {
	int index = XLINK_USR_BIN_ADDR_PDID;
	char product[65];
	memset(product, 0, 64);
	memcpy(product, proid, 32);
	memcpy(product + 32, proKey, 32);
	hffile_userbin_write(index, product, 64);
	return 0;
}

int XlinkReadProductIDKEY(char *proid, char *proKey) {
	int index = XLINK_USR_BIN_ADDR_PDID;
	char product[65];
	hffile_userbin_read(index, product, 64);
	memcpy(proid, product, 32);
	memcpy(proKey, product + 32, 32);
	return 0;
}

int XlinkWriteAtConfig(AT_CONFIG *config) {
	char buf[50];
	memset(buf, 0, 50);
	buf[0] = config->flag.byte;
	memcpy(buf + 1, config->macString, 12);
	hffile_userbin_write(XLINK_USR_BIN_ADDR_AT, buf, 50);
	return 50;
}

int XlinkReadAtConfig(AT_CONFIG *config) {
	char buf[50];
	memset(buf, 0, 50);
	hffile_userbin_read(XLINK_USR_BIN_ADDR_AT, buf, 50);
	config->flag.byte = buf[0];
	memcpy(config->macString, buf + 1, 12);
	config->macString[12]='\0';
	return 50;
}

/**
 * Date: 2014 12 30
 * Description:
 * 		将字符串的mac转为数字的mac
 * Parameters:
 * 		ch1    :字符mac
 * 		ch2    :字符mac
 * 		for_num:返回的数字的mac
 * Return:
 * 		void
 */
XLINK_FUNC void mac_to_hex(char ch_h, char ch_l, x_uint8 *for_num) {
	int t = 0;
	int int_data = 0;
	if (ch_h <= '9') {
		t = ch_h - '0';
	} else {
		t = ch_h - 'A' + 10;
	}
	if (ch_l <= '9') {
		int_data = t * 16 + (ch_l - '0');
	} else {
		int_data = t * 16 + (ch_l - 'A' + 10);
	}
	*for_num = (unsigned char) int_data;
}

/**
 * Date: 2014 12 30
 * Description:
 * 		得到本机的mac地址
 * Parameters:
 * 		mac    :返回的mac地址(数字的)
 * Return:
 *		返回mac字符串的长度
 */
x_int32 XlinkGetDeviceMac(x_uint8 *mac) {
	x_int8 buf[20] = { 0x00 };

	char *cmd = "AT+WSMAC\r\n";
	x_int32 ret = hfat_send_cmd(cmd, xlink_strlen(cmd), buf, 20);
	x_uint8 index = 4;
	for (x_uint8 i = 0; i < 6; i++) {
		char h = buf[index++];
		char l = buf[index++];
		mac_to_hex(h, l, mac++);
	}
	return ret - 4;
}

/**
 * Date: 2015 01 13
 * Description:
 * 		清除本机所有配置
 * Parameters:
 * 		void
 * Return:
 *		void
 */
XLINK_FUNC void XlinkConfigReset(void) {
//	char buf[XLINK_SIZE_17];
//	xlink_memset(buf, 0, XLINK_SIZE_17);
//	//XlinkConfigWriteConfig(XLINK_CONFIG_INDEX_DEVICE_ID, buf, XLINK_SIZE_17 - 1);
//	XlinkConfigWriteConfig(0, buf, XLINK_SIZE_17 - 1);
//	XlinkConfigWriteConfig(1, buf, XLINK_SIZE_17 - 1);
//	XlinkConfigWriteConfig(2, buf, XLINK_SIZE_17 - 1);
//	XlinkConfigWriteConfig(3, buf, XLINK_SIZE_17 - 1);
}

