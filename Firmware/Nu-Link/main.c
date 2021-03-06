#include <stdio.h>
#include "NUC100Series.h"

#include "DAP_config.h"
#include "DAP.h"

#include "hid.h"

void main (void) 
{
	// set pll out 48Mhz, set cpu clock 48Mhz
	SYS_UnlockReg();
	CLK_EnableXtalRC(CLK_PWRCON_XTL12M_EN_Msk);
	CLK_WaitClockReady(CLK_CLKSTATUS_XTL12M_STB_Msk);
	CLK_SetCoreClock(48000000);
	CLK_EnableModuleClock(USBD_MODULE);
	CLK_SetModuleClock(USBD_MODULE, 0, CLK_CLKDIV_USB(1));
	
	
	DAP_Setup();
	
	USBD_Open(&gsInfo, HID_ClassRequest, NULL);
	HID_Init();
	balabala_hid_init();
	USBD_Start();
	NVIC_EnableIRQ(USBD_IRQn);	
	
	while(1)
	{
		usbd_hid_process();
	}
}
