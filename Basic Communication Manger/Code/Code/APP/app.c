#include "app.h"
#include <util/delay.h>
#define  F_CPU 8000000ul
void APP_Init(void)
{
	sei();
	bcm_init(ID_1_);
	LCD_INIT();
	LED_INIT(pina0);
	LED_INIT(pina1);
	LED_INIT(pina2);
	LED_INIT(pina3);
}

void APP_Start(void)
{
	BCM_SetCallBack(BCM_Rece_t,Func_after_Receive);
	
	BCM_SetCallBack(BCM_Send_t,Func_after_Send);
	
	bcm_send_n("BCM Operating");

	bcm_receive(str);

}


void Func_after_Send(void)
{
	LED_ON(pina0);

}

void Func_after_Receive(void)
{
	LED_ON(pina1);

}