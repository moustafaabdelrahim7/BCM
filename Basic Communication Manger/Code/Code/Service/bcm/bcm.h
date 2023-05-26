


#ifndef BCM_H_
#define BCM_H_
/********************************************Includes**************************************************************************/
#include "../../MCAL/uart/uart.h"
#include "../../HAL/led/LED.h"
/********************************************Enums******************************************************************************/
typedef enum
{
	Free=0,
	Sending,
	Receving,
	Sending_Done,
	Receving_Done
	}enu_system_status_t;
/*********************************************Structures**************************************************************************/



typedef struct
{
	enu_id_num_t	enu_id_num;
	
	}str_bcm_instance_t;
	
	
	
typedef enum
{
	BCM_Send_t=0,
	BCM_Rece_t
}enu_BCM_Callback_t;
/*********************************************Prototypes**************************************************************************************/
enu_system_status_t bcm_init(str_bcm_instance_t*ptr_str_bcm_instance);

enu_system_status_t	bcm_send(uint8_t Data);

enu_system_status_t	bcm_send_n(uint8_t * Data);

enu_system_status_t	bcm_receive(uint8_t *str);

void BCM_SetCallBack(enu_BCM_Callback_t enu_Callback,void(*FPTR)(void));

uint8_t get_flag(void);

void BCM_Dispatcher_Transmit_Handler(void);
void BCM_Dispatcher_Receive_Handler(void);


extern  volatile uint8_t Status;

#endif /* BCM_H_ */