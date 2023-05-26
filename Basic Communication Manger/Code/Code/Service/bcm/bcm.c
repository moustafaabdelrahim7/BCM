#include "bcm.h"
#include "../../HAL/lcd/LCD.h"

static void (*BCM_Send_Fptr)(void)=NULL_PTR;
static void (*BCM_RECE_Fptr)(void)=NULL_PTR;

	/************************************************************************/
	/*						Includes                                        */
	/************************************************************************/
#include "../../MCAL/uart/uart.h"

	/************************************************************************/
	/*						Data Base                                       */
	/************************************************************************/

/*uint8_t*PSendData=0,*PRecievedData=0;*/
uint8_t*ptr_arr_send[50]={0};
uint8_t*ptr_arr_rece[50]={0};
	
	/************************************************************************/
	/*						Global Flags And Enums                          */
	/************************************************************************/
uint8_t static send_flag=0,rece_flag=0;
volatile uint8_t Status=Free;
 
	/************************************************************************/
	/*	Name:Bcm_Init
	
		Description:-It initializes The Requires Medium Using an Id 
		
		Returns:-Status Regarding The Specific Communication
																			*/
	/************************************************************************/
enu_system_status_t bcm_init(str_bcm_instance_t*ptr_str_bcm_instance)
{
	
	UART_init(ptr_str_bcm_instance->enu_id_num);
	
}
/******************************************************************************************************************************/
	/************************************************************************/
	/*	Name:Bcm_Send
	
		Description:-It Sends On Byte in an asynchronism Mode 
		
		Returns:-Status Regarding The Specific Communication
																			*/
	/************************************************************************/
enu_system_status_t	bcm_send(uint8_t Data)
{
	UART_transmit_NoBlock(Data);
}

/*********************************************************************************************************************************/
	/************************************************************************/
	/*	Name:Bcm_Send_n
	
		Description:-It is capable of sending a string "With Max Size Of 65000" in an asynchronism Mode 
		
		Returns:-Status Regarding The Specific Communication
																			*/
	/************************************************************************/
enu_system_status_t	bcm_send_n(uint8_t * Data)
{
	static uint8_t i=0;

	if (send_flag==0)
	{
			UART_TX_INTENABLE();
			ptr_arr_send[i]=Data;
			UART_transmit_NoBlock(Data[i]);
			UART_SetCallBack(Uart_tx_t,BCM_Dispatcher_Transmit_Handler);
/*			Status=Sending;*/
			send_flag=1;	
			i++;	
/*			return Sending;*/
	}
	else
	{
		ptr_arr_send[i]=Data;
		i++;
/*		Status=Free;*/

	}

}
/**************************************************************************************************************************************/
	/************************************************************************/
	/*	Name:Bcm_receive
	
		Description:-It is capable of receiving any length of data  in an asynchronism Mode 
		
		Returns:-Status Regarding The Specific Communication
																			*/
	/************************************************************************/
enu_system_status_t	bcm_receive(uint8_t *str)
{
	static uint8_t i=0;
	if (rece_flag==0)
	{
		UART_RX_INTENABLE();
		ptr_arr_rece[i]=str;
		UART_SetCallBack(Uart_rx_t,BCM_Dispatcher_Receive_Handler);
		rece_flag++;
		i++;
	}
	else
	{
		ptr_arr_rece[i]=str;
		i++;	
	}
}
/*************************************************************************************************************************************/
	/************************************************************************/
	/*	Name:Get_Flag
	
		Description:-a getter function to return the flag for the app layer
		
		Returns:-Status Regarding The Specific Communication
																			*/
	/************************************************************************/
uint8_t get_flag(void)
{
	return Status;
}
/*************************************************************************************************************************************/
	/************************************************************************/
	/*	Name:BCM_Dispatcher_Transmit_Handler
	
		Description:-It handles the Transmit operation without any data corruption 
		
		Returns:-Status Regarding The Specific Communication
																			*/
	/************************************************************************/
void BCM_Dispatcher_Transmit_Handler(void)
{
static	uint8_t ptr=0;
	
		static uint8_t index=1;
		if (ptr_arr_send[ptr][index]!=0)
		{
			UART_transmit_NoBlock(ptr_arr_send[ptr][index]);
			index++;
		}
		else if (ptr_arr_send[ptr+1]!=0)
		{
		UART_transmit_NoBlock('#');
		index=0;
		ptr++;
		UART_transmit_NoBlock(ptr_arr_send[ptr][index]);
		index++;
		}
		else
		{
			if (BCM_Send_Fptr!=NULL_PTR)
			{
				BCM_Send_Fptr();
			}
			else	 
			{
				/*do Nothing*/
			}
			index=1;
			send_flag=0;
			UART_transmit_NoBlock('#');
			/*Status=Sending_Done;*/
			UART_TX_INTDISABLE();
		
		}
	
}
/*********************************************************************************************************************************************************/
	/*	Name:BCM_Dispatcher_Receive_Handler
	
		Description:-It handles the receive operation without any data corruption 
		
		Returns:-Status Regarding The Specific Communication
																			*/
	/************************************************************************/
void BCM_Dispatcher_Receive_Handler(void)
{

		static uint8_t i=0,ptr=0;
	    ptr_arr_rece[ptr][i]=UART_receive_NoBlock();
		if(ptr_arr_rece[ptr][i]!=0x23)
		{
		i++;
		}
		else if(ptr_arr_rece[ptr+1]!=0)
		{

			ptr++;
			i=0;
			ptr_arr_rece[ptr][i++]=UART_receive_NoBlock();
			Status=Receving_Done;
		}
		else
		{
			if (BCM_RECE_Fptr!=NULL_PTR)
			{
				BCM_RECE_Fptr();
			}
			else	 
			{
				/*do Nothing*/
			}
			
		
			i=0;
			rece_flag=0;
			Status=Receving_Done;
			UART_RX_INTDISABLE();	
		}

	
}

/***********************************************************************************************************************************************/

void BCM_SetCallBack(enu_BCM_Callback_t enu_Callback,void(*FPTR_8)(void))
{
	if (enu_Callback==BCM_Send_t)
	{
		BCM_Send_Fptr=FPTR_8;
	}
	else if (enu_Callback==BCM_Rece_t)
	{
		BCM_RECE_Fptr=FPTR_8;
	}
}