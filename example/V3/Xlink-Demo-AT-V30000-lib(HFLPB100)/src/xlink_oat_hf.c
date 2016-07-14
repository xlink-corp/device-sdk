/*
 * xlink_oat_hf.c
 *
 *  Created on: 2015年9月12日
 *      Author: XT800
 */

#include "xlink_ota_hf.h"
#include "hsf.h"
#include <md5.h>

#ifndef USER_FUNC
#define USER_FUNC
#endif

void USER_FUNC update_timer_callback( hftimer_handle_t htimer )
{
	if(hfgpio_fpin_is_high(HFGPIO_F_NLINK))
		hfgpio_fset_out_low(HFGPIO_F_NLINK);
	else
		hfgpio_fset_out_high(HFGPIO_F_NLINK);
}


int USER_FUNC xlink_update_as_http(char *purl,char *type,XLINK_UPGRADE *data)
{
	httpc_req_t http_req;
	char *content_data=NULL;
	char *temp_buf=NULL;
	parsed_url_t url= {0};
	http_session_t hhttp=0;
	int total_size,read_size=0;
	int rv=0;
	tls_init_config_t *tls_cfg=NULL;
	char *test_url=purl;
	hftimer_handle_t upg_timer=NULL;
	struct MD5Context md5_ctx;
	uint8_t digest[16]= {0};
	HFUPDATE_TYPE_E upg_type;

	bzero(&http_req,sizeof(http_req));
	http_req.type = HTTP_GET;
	http_req.version=HTTP_VER_1_1;

	if(strcasecmp(type,"wifi")==0)
	{
		upg_type = HFUPDATE_WIFIFW;
	}
	else{
		upg_type = HFUPDATE_SW;
	}
	if((temp_buf = (char*)hfmem_malloc(256))==NULL)
	{
		u_printf("no memory\n");
		rv= -HF_E_NOMEM;
		goto exit;
	}
	bzero(temp_buf,sizeof(temp_buf));
	if((rv=hfhttp_parse_URL(test_url,temp_buf , 256, &url))!=HF_SUCCESS)
	{
		goto exit;
	}else{
		u_printf("---up---:%s\r\n",temp_buf);
	}

	if((rv=hfhttp_open_session(&hhttp,test_url,0,tls_cfg,3))!=HF_SUCCESS)
	{
		u_printf("http open fail\n");
		goto exit;
	}

	hfsys_disable_all_soft_watchdogs();
	hfupdate_start(upg_type);
	http_req.resource = url.resource;
	hfhttp_prepare_req(hhttp,&http_req,HDR_ADD_CONN_CLOSE);
	hfhttp_add_header(hhttp,"Range","bytes=0");
	if((rv=hfhttp_send_request(hhttp,&http_req))!=HF_SUCCESS)
	{
		u_printf("http send request fail\n");
		goto exit;
	}

	content_data = (char*)hfmem_malloc(256);
	if(content_data==NULL)
	{
		rv= -HF_E_NOMEM;
		goto exit;
	}
	total_size=0;
	bzero(content_data,256);

	if((upg_timer = hftimer_create("UPG-TIMER",100,true,1,update_timer_callback,0))==NULL)
	{
		u_printf("create timer 1 fail\n");
		goto exit;
	}

	hftimer_start(upg_timer);
	MD5Init(&md5_ctx);
	while((read_size=hfhttp_read_content(hhttp,content_data,256))>0)
	{
		hfupdate_write_file(upg_type, total_size,content_data, read_size);
		MD5Update(&md5_ctx,(uint8_t*)content_data,read_size);
		total_size+=read_size;
		u_printf("download file:[%d] [%d]\r",total_size,read_size);
	}
	MD5Final(digest,&md5_ctx);
	u_printf("read_size:%d digest is ",total_size);
	u_printf("%02x%02x%02x%02x",digest[0],digest[1],digest[2],digest[3]);
	u_printf("%02x%02x%02x%02x",digest[4],digest[5],digest[6],digest[7]);
	u_printf("%02x%02x%02x%02x",digest[8],digest[9],digest[10],digest[11]);
	u_printf("%02x%02x%02x%02x\n",digest[12],digest[13],digest[14],digest[15]);

	if(hfupdate_complete(upg_type,total_size)!=HF_SUCCESS)
	{
		u_printf("update software fail\n");
	}
    else {
        msleep(500);
        hfsys_reset();
    }
	exit:
	if(upg_timer!=NULL)
	{
		hftimer_delete(upg_timer);
		hftimer_delete(upg_timer);
	}
	if(temp_buf!=NULL)
	hfmem_free(temp_buf);
	if(content_data!=NULL)
	hfmem_free(content_data);
	if(hhttp!=0)
	hfhttp_close_session(&hhttp);
	hfgpio_fset_out_low(HFGPIO_F_NREADY);
	hfsys_enable_all_soft_watchdogs();
	return rv;
}
