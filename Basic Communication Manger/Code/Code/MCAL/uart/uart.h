 
#ifndef UART_H_
#define UART_H_

/************************************************************************************************************************************************
																	 Includes
*************************************************************************************************************************************************/
#include "../../UTILS/STD_TYPES.h"
#include "../../UTILS/UTILES.h"
#include "../MEMORYMAP.h"

/******************************************************************End Of Includes***************************************************************************/

/********************************************************************Macros And Extern**************************************************************************/
#define NUM_Of_ID	3


/********************************************************************End Of MAcros************************************************************************************/

/*******************************************************************************************************************************************************
																Enums
********************************************************************************************************************************************************/
/*Channel ID*/
typedef enum
{
	ID_1_=0,
	ID_2_,
	ID_3_
	}enu_id_num_t;



typedef enum
{
	Uart_tx_t=0,
	Uart_rx_t
}enu_Callback_t;


/*Speed*/
typedef enum
{
	UART_NORMAL_SPEED,
	UART_DOUBLE_SPEED
}EN_UART_Speed_Type;
/*********************************************/
/*Parity*/
typedef enum
{
	NO_PARITY,
	EVEN_PARITY,
	ODD_PARITY
}EN_UART_Parity_Type;
/*******************************************/
/*Synchronism*/
typedef enum
{
	ASYNCH,
	SYNCH
}EN_UART_Synchronism_Type;
/*******************************************/
/*Stop Bits*/
typedef enum
{
	ONE_STOP_BIT,
	TWO_STOP_BIT
}EN_UART_StopBit_Type;
/*******************************************/
/*Data Size*/
typedef enum
{
	UART_5_BIT=5,
	UART_6_BIT,
	UART_7_BIT,
	UART_8_BIT,
	UART_9_BIT
}EN_UART_DataSize_Type;
/******************************************/
/*Stop Bits*/
typedef enum
{
	_4_MHZ=4000000ul,
	_8_MHZ=8000000ul,
	_16_MHZ=16000000ul
}EN_UART_Freq_Type;
/*******************************************/
/*Enable Type*/
typedef enum
{
	UART_TX_ENABLE,
	UART_RX_ENABLE,
	UART_TX_RX_ENABLE
}EN_UART_TX_RX_Enable_Type;
/*******************************************/
/*Disable Type*/
typedef enum
{
	UART_TX_DISABLE,
	UART_RX_DISABLE,
	UART_TX_RX_DISABLE
}EN_UART_TX_RX_Disable_Type;
/*********************************************/
/*INT Enable*/
typedef enum
{
	UART_TX_INT_ENABLE,
	UART_RX_INT_ENABLE
}EN_UART_TX_RX_Int_Enable_Type;
/**********************************************/
/*INT Disable*/
typedef enum
{
	UART_TX_INT_DISABLE,
	UART_RX_INT_DISABLE
}EN_UART_TX_RX_Int_Disable_Type;
/************************************************/
/*BaudRate*/
typedef enum
{
	UART_2400_BAUDRATE,
	UART_4800_BAUDRATE,
	UART_9600_BAUDRATE,
	UART_14400_BAUDRATE,
	UART_19200_BAUDRATE,
	UART_28800_BAUDRATE,
	UART_38400_BAUDRATE,
	UART_57600_BAUDRATE,
	UART_76800_BAUDRATE,
	UART_115200_BAUDRATE,
	UART_230400_BAUDRATE,
	UART_250000_BAUDRATE
}EN_UART_BaudRate_Type;
/***************************************************/


typedef struct
{
	EN_UART_Speed_Type			    UART_Speed;
	EN_UART_Parity_Type			    UART_Parity;
	EN_UART_StopBit_Type		    UART_StopBits;
	EN_UART_DataSize_Type		    UART_DataSize;
	EN_UART_TX_RX_Enable_Type	    UART_EnablePins;
	EN_UART_BaudRate_Type			UART_BaudRate;

}ST_UART_LConfig_Type;

/************************************************************End Of Enums*************************************************************************/



/****************************************************prototypes************************************************************/

void UART_init(enu_id_num_t ID_num);
void UART_transmit(uint8_t data);
uint8_t UART_receive(void);
uint8_t UART_receive_NoBlock(void);
void UART_transmit_NoBlock(uint8_t data);
void UART_receive_String_NoBlock(uint8_t*str);
void UART_SetCallBack(enu_Callback_t enu_Callback,void(*FPTR)(void));
void UART_TX_INTENABLE(void);
void UART_RX_INTENABLE(void);
void UART_TX_INTDISABLE(void);
void UART_RX_INTDISABLE(void);
extern ST_UART_LConfig_Type uart_lcfg_arr[NUM_Of_ID];
#endif /* UART_H_ */