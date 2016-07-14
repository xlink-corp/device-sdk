#include <hsf.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "xlink_demo.h"
#include "xlink_at.h"

#ifndef XLINK_FUNC
#define XLINK_FUNC
#endif

#ifdef __LPT100__
static int module_type= HFM_TYPE_LPT100;
const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HFM_NOPIN,//HF_M_PIN(2),	//HFGPIO_F_JTAG_TCK
	HFM_NOPIN,//HF_M_PIN(3),	//HFGPIO_F_JTAG_TDO
	HFM_NOPIN,//HF_M_PIN(4),	//HFGPIO_F_JTAG_TDI
	HFM_NOPIN,//HF_M_PIN(5),	//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	HF_M_PIN(39),	//HFGPIO_F_UART0_TX
	HF_M_PIN(40),	//HFGPIO_F_UART0_RTS
	HF_M_PIN(41),	//HFGPIO_F_UART0_RX
	HF_M_PIN(42),	//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,//HF_M_PIN(27),	//HFGPIO_F_SPI_MISO
	HFM_NOPIN,//HF_M_PIN(28),	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,//HF_M_PIN(29),	//HFGPIO_F_SPI_CS
	HFM_NOPIN,//HF_M_PIN(30),	//HFGPIO_F_SPI_MOSI
	
	HFM_NOPIN,	//HFGPIO_F_UART1_TX,
	HFM_NOPIN,	//HFGPIO_F_UART1_RTS,
	HFM_NOPIN,	//HFGPIO_F_UART1_RX,
	HFM_NOPIN,	//HFGPIO_F_UART1_CTS,
	
	HF_M_PIN(11),	//HFGPIO_F_NLINK
	HF_M_PIN(12),	//HFGPIO_F_NREADY
	HF_M_PIN(45),	//HFGPIO_F_NRELOAD
	HFM_NOPIN,	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,	//HFGPIO_F_SLEEP_ON
	
	HFM_NOPIN,//HF_M_PIN(18),	//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	//HFM_NOPIN,	//HFGPIO_F_USER_DEFINE

	HFM_NOPIN,
	HFM_NOPIN,
	HFM_NOPIN,

	HFM_NOPIN,
	HFM_NOPIN,

	HF_M_PIN(18),//connect server
	HFM_NOPIN,
	HFM_NOPIN,

	HFM_NOPIN,
	HFM_NOPIN,
};
#elif defined(__LPT200__)
static int module_type= HFM_TYPE_LPT200;
const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HF_M_PIN(2),	//HFGPIO_F_JTAG_TCK
	HF_M_PIN(3),	//HFGPIO_F_JTAG_TDO
	HF_M_PIN(4),	//HFGPIO_F_JTAG_TDI
	HF_M_PIN(5),	//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	HF_M_PIN(39),	//HFGPIO_F_UART0_TX
	HF_M_PIN(40),	//HFGPIO_F_UART0_RTS
	HF_M_PIN(41),	//HFGPIO_F_UART0_RX
	HF_M_PIN(42),	//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,//HF_M_PIN(27),	//HFGPIO_F_SPI_MISO
	HFM_NOPIN,//HF_M_PIN(28),	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,//HF_M_PIN(29),	//HFGPIO_F_SPI_CS
	HFM_NOPIN,//HF_M_PIN(30),	//HFGPIO_F_SPI_MOSI
	
	HFM_NOPIN,	//HFGPIO_F_UART1_TX,
	HFM_NOPIN,	//HFGPIO_F_UART1_RTS,
	HFM_NOPIN,	//HFGPIO_F_UART1_RX,
	HFM_NOPIN,	//HFGPIO_F_UART1_CTS,
	
	HF_M_PIN(43),	//HFGPIO_F_NLINK
	HF_M_PIN(44),	//HFGPIO_F_NREADY
	HF_M_PIN(45),	//HFGPIO_F_NRELOAD
	HFM_NOPIN,	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,	//HFGPIO_F_SLEEP_ON
		
	HF_M_PIN(7),		//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	//HFM_NOPIN,	//HFGPIO_F_USER_DEFINE

	HFM_NOPIN,
	HFM_NOPIN,
	HFM_NOPIN,

	HFM_NOPIN,
	HFM_NOPIN,

	HF_M_PIN(29),//connect server
	HFM_NOPIN,
	HFM_NOPIN,

	HFM_NOPIN,
	HFM_NOPIN,
};
#elif defined(__LPB100__)
static int module_type= HFM_TYPE_LPB100;
const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HF_M_PIN(2),	//HFGPIO_F_JTAG_TCK
	HF_M_PIN(3),	//HFGPIO_F_JTAG_TDO
	HF_M_PIN(4),	//HFGPIO_F_JTAG_TDI
	HF_M_PIN(5),	//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	HF_M_PIN(39),	//HFGPIO_F_UART0_TX
	HFM_NOPIN,//HF_M_PIN(40),	//HFGPIO_F_UART0_RTS
	HF_M_PIN(41),	//HFGPIO_F_UART0_RX
	HFM_NOPIN,//HF_M_PIN(42),	//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,//HF_M_PIN(27),	//HFGPIO_F_SPI_MISO
	HFM_NOPIN,//HF_M_PIN(28),	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,//HF_M_PIN(29),	//HFGPIO_F_SPI_CS
	HFM_NOPIN,//HF_M_PIN(30),	//HFGPIO_F_SPI_MOSI
	
	HFM_NOPIN,//HF_M_PIN(23),//HFM_NOPIN,	//HFGPIO_F_UART1_TX,
	HFM_NOPIN,	//HFGPIO_F_UART1_RTS,
	HF_M_PIN(8),	//HFGPIO_F_UART1_RX,
	HFM_NOPIN,	//HFGPIO_F_UART1_CTS,
	
	HF_M_PIN(43),	//HFGPIO_F_NLINK
	HF_M_PIN(44),	//HFGPIO_F_NREADY
	HF_M_PIN(45),	//HFGPIO_F_NRELOAD
	HFM_NOPIN,//HF_M_PIN(7),	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,//HF_M_PIN(8),	//HFGPIO_F_SLEEP_ON
		
	HFM_NOPIN,//HF_M_PIN(15),		//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	//HFM_NOPIN,	//HFGPIO_F_USER_DEFINE

	HFM_NOPIN,
	HFM_NOPIN,
	HFM_NOPIN,

	HFM_NOPIN,
	HFM_NOPIN,

	HF_M_PIN(18),//connect server
	HFM_NOPIN,
	HFM_NOPIN,

	HFM_NOPIN,
	HFM_NOPIN,
};
#elif defined(__LPB105__)
static int module_type= HFM_TYPE_LPB105;
const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HF_M_PIN(2),	//HFGPIO_F_JTAG_TCK
	HF_M_PIN(3),	//HFGPIO_F_JTAG_TDO
	HF_M_PIN(4),	//HFGPIO_F_JTAG_TDI
	HF_M_PIN(5),	//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	HF_M_PIN(39),	//HFGPIO_F_UART0_TX
	HFM_NOPIN,	//HFGPIO_F_UART0_RTS
	HF_M_PIN(41),	//HFGPIO_F_UART0_RX
	HFM_NOPIN,	//HFGPIO_F_UART0_CTS
	
	HF_M_PIN(27),	//HFGPIO_F_SPI_MISO
	HF_M_PIN(28),	//HFGPIO_F_SPI_CLK
	HF_M_PIN(29),	//HFGPIO_F_SPI_CS
	HF_M_PIN(30),	//HFGPIO_F_SPI_MOSI
	
	HFM_NOPIN,	//HFGPIO_F_UART1_TX,
	HFM_NOPIN,	//HFGPIO_F_UART1_RTS,
	HFM_NOPIN,	//HFGPIO_F_UART1_RX,
	HFM_NOPIN,	//HFGPIO_F_UART1_CTS,
	
	HF_M_PIN(11),	//HFGPIO_F_NLINK
	HF_M_PIN(44),	//HFGPIO_F_NREADY
	HF_M_PIN(45),	//HFGPIO_F_NRELOAD
	HFM_NOPIN,	//HFGPIO_F_SLEEP_RQ
	HFM_NOPIN,	//HFGPIO_F_SLEEP_ON
	
	HF_M_PIN(18),	//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	HFM_NOPIN,	//HFGPIO_F_USER_DEFINE
};
#elif defined(__LPB100U__)
static int module_type= HFM_TYPE_LPB100;
const int hf_gpio_fid_to_pid_map_table[HFM_MAX_FUNC_CODE]=
{
	HF_M_PIN(2),	//HFGPIO_F_JTAG_TCK
	HFM_NOPIN,	//HFGPIO_F_JTAG_TDO
	HFM_NOPIN,	//HFGPIO_F_JTAG_TDI
	HF_M_PIN(5),	//HFGPIO_F_JTAG_TMS
	HFM_NOPIN,		//HFGPIO_F_USBDP
	HFM_NOPIN,		//HFGPIO_F_USBDM
	HF_M_PIN(39),	//HFGPIO_F_UART0_TX
	HFM_NOPIN,//HF_M_PIN(40),	//HFGPIO_F_UART0_RTS
	HF_M_PIN(41),	//HFGPIO_F_UART0_RX
	HFM_NOPIN,//HF_M_PIN(42),	//HFGPIO_F_UART0_CTS
	
	HFM_NOPIN,//HF_M_PIN(27),	//HFGPIO_F_SPI_MISO
	HFM_NOPIN,//HF_M_PIN(28),	//HFGPIO_F_SPI_CLK
	HFM_NOPIN,//HF_M_PIN(29),	//HFGPIO_F_SPI_CS
	HFM_NOPIN,//HF_M_PIN(30),	//HFGPIO_F_SPI_MOSI
	
	HF_M_PIN(29),	//HFGPIO_F_UART1_TX,
	HFM_NOPIN,	//HFGPIO_F_UART1_RTS,
	HF_M_PIN(30),	//HFGPIO_F_UART1_RX,
	HFM_NOPIN,	//HFGPIO_F_UART1_CTS,	
	
	HF_M_PIN(43),	//HFGPIO_F_NLINK
	HF_M_PIN(44),	//HFGPIO_F_NREADY
	HF_M_PIN(45),	//HFGPIO_F_NRELOAD
	HF_M_PIN(7),	//HFGPIO_F_SLEEP_RQ
	HF_M_PIN(8),	//HFGPIO_F_SLEEP_ON
		
	HF_M_PIN(15),		//HFGPIO_F_WPS
	HFM_NOPIN,		//HFGPIO_F_RESERVE1
	HFM_NOPIN,		//HFGPIO_F_RESERVE2
	HFM_NOPIN,		//HFGPIO_F_RESERVE3
	HFM_NOPIN,		//HFGPIO_F_RESERVE4
	HFM_NOPIN,		//HFGPIO_F_RESERVE5
	
	//HFM_NOPIN,	//HFGPIO_F_USER_DEFINE

	HFM_NOPIN,
	HFM_NOPIN,
	HFM_NOPIN,

	HFM_NOPIN,
	HFM_NOPIN,

	HF_M_PIN(18),//connect server
	HFM_NOPIN,
	HFM_NOPIN,

	HFM_NOPIN,
	HFM_NOPIN,
};
#else
#error "invalid project !you must define module type(__LPB100__,__LPT100__,_LPT200__)"
#endif

const hfat_cmd_t user_define_at_cmds_table[] = { { NULL, NULL, NULL, NULL } //the last item must be null
};

void USER_FUNC airkiss_domain_lop(void *args);

static void show_reset_reason(void) {
	uint32_t reset_reason = 0;

	reset_reason = hfsys_get_reset_reason();

#if 1
	u_printf("reset_reasion:%08x\n", reset_reason);
#else	
	if(reset_reason&HFSYS_RESET_REASON_ERESET)
	{
		u_printf("ERESET\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_IRESET0)
	{
		u_printf("IRESET0\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_IRESET1)
	{
		u_printf("IRESET1\n");
	}
	if(reset_reason==HFSYS_RESET_REASON_NORMAL)
	{
		u_printf("RESET NORMAL\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_WPS)
	{
		u_printf("RESET FOR WPS\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_SMARTLINK_START)
	{
		u_printf("RESET FOR SMARTLINK START\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_SMARTLINK_OK)
	{
		u_printf("RESET FOR SMARTLINK OK\n");
	}
	if(reset_reason&HFSYS_RESET_REASON_WPS_OK)
	{
		u_printf("RESET FOR WPS OK\n");
	}
#endif

	return;
}

void app_init(void) {
	u_printf("app_init\n");
}

XLINK_FUNC void work_phtread(void *args) {
	int ret = xlink_demo_init();
	if (ret == 0) {
		while (1) {
			msleep(1000);
		}
	}
	xlink_demo_loop();
}

XLINK_FUNC void work_phtread_tcp_client(void *args) {
	
	while(1){
			XlinkSystemTcpLoop();
			msleep(2*1000);
	}
}


static int hfsys_event_callback(uint32_t event_id, void * param) {
	int ret = 0;
	switch (event_id) {
	case HFE_WIFI_STA_CONNECTED:
		u_printf("wifi sta connected!!\n");
		g_AllSta.bit.isConnectWIFI = 1;
		xlink_send_uart_sta();
		XlinkSystemSetWifiStatus(1);
		break;
	case HFE_WIFI_STA_DISCONNECTED:
		u_printf("wifi sta disconnected!!\n");
		g_AllSta.bit.isConnectWIFI = 0;
		xlink_send_uart_sta();
	  XlinkSystemSetWifiStatus(0);
		break;
	case HFE_DHCP_OK:
		XlinkSystemSetWifiStatus(1);
		break;
	case HFE_SMTLK_OK:
		u_printf("smtlk ok!\n");
		break;
	case HFE_CONFIG_RELOAD:
		u_printf("reload!\n");
		break;
	default:
		break;
	}
	return ret;
}

static int USER_FUNC uart_recv_callback(uint32_t event,char *data,uint32_t len,uint32_t buf_len)
{
	HF_Debug(DEBUG_LEVEL_LOW,"[%d]uart recv %d bytes data %d\n",event,len,buf_len);
	xlink_recv_uart_data((unsigned char *)data,len);
	return len;
}

///main
int XLINK_FUNC app_main(void) {

	//time_t now=time(NULL);
//	hfdbg_set_level(DEBUG_LEVEL);
	//XlinkUartSend("App start .\r\n", sizeof("App start .\r\n"));
	HF_Debug(DEBUG_LEVEL, "sdk version(%s),the app_main start time is %s %s\n", hfsys_get_sdk_version(), __DATE__, __TIME__);

	if (hfgpio_fmap_check(module_type) != 0) {
		while (1) {
			HF_Debug(DEBUG_ERROR, "gpio map file error\n");
			msleep(1000);
		}
		//return 0;
	}
	
	show_reset_reason();

	g_AllSta.byte = 0;
	if (hfsys_register_system_event((hfsys_event_callback_t) hfsys_event_callback) != HF_SUCCESS) {
		u_printf("register system event fail\n");
	}

	while (!hfnet_wifi_is_active()) {
		msleep(50);
		//XlinkUartSend("msleep.\r\n", sizeof("msleep.\r\n"));
	}
	//XlinkUartSend("hfnet_wifi_is_active.\r\n", sizeof("hfnet_wifi_is_active.\r\n"));
#if 1
	int up_result=0;
	up_result = hfupdate_auto_upgrade(0);
	if(up_result<0)
	{
		u_printf("no entry the auto upgrade mode\n");
	}
	else if(up_result==0)
	{
		u_printf("upgrade success\n");
	}
	else
	{
		u_printf("upgrade fail %d\n",up_result);
	}
#endif
	
	if (hfnet_start_assis(ASSIS_PORT) != HF_SUCCESS) {
		HF_Debug(DEBUG_WARN, "start httpd fail\n");
	}

	if (hfnet_start_httpd(HFTHREAD_PRIORITIES_MID) != HF_SUCCESS) {
		HF_Debug(DEBUG_WARN, "start httpd fail\n");
	}
	
	if(hfnet_start_uart(HFTHREAD_PRIORITIES_LOW,(hfnet_callback_t)uart_recv_callback)!=HF_SUCCESS)
	{
		HF_Debug(DEBUG_WARN,"start uart fail!\n");
	}

//    XlinkUartSend("system init V1.\r\n", 14);
	hfthread_create(work_phtread, "xlink_loop", 1024, NULL, HFTHREAD_PRIORITIES_NORMAL, NULL, NULL );
	hfthread_create(work_phtread_tcp_client, "xlink_loop_tcp", 128, NULL, HFTHREAD_PRIORITIES_NORMAL, NULL, NULL );
#ifndef __LPT200__
	hfthread_create(airkiss_domain_lop, "airkiss_domain_lop", 512, NULL, HFTHREAD_PRIORITIES_NORMAL, NULL, NULL );
#endif
	return 1;
}

