#include "uart.h"
	/************************************************************************/
	/*					      Global Pointer To Functions	                */
	/************************************************************************/
static void (*UART_TRANS_Fptr)(void)=NULL_PTR;
static void (*UART_RECE_Fptr)(void)=NULL_PTR;


	/************************************************************************/
	/*	Name:UART_init
	
		Description:-It initializes the Peripherals With the required Type of sets From The Linking Config File
		
		Returns:-void
																			*/
	/************************************************************************/

void UART_init(enu_id_num_t ID_num)
{
	
	/************************************************************************/
	/*					      BaudRate				                        */
	/************************************************************************/
	
	if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_2400_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL =207;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRH = (uint8_t)(416>>8);
			UBRRL = (uint8_t)416;	
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_4800_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=103;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=207;
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_9600_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=51;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=103;
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_14400_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=34;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=68;
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_19200_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=25;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=51;
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_28800_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=16;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=34;
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_38400_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=12;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=25;
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_57600_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=8;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=16;
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_76800_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=8;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=12;
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_115200_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=3;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=8;
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_230400_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=1;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=3;
		}
	}
	else if (uart_lcfg_arr[ID_num].UART_BaudRate==UART_250000_BAUDRATE)
	{
		if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
		{
			UBRRL=1;
		}
		else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
		{
			UBRRL=3;
		}
	}
	/************************************************************************/
	/*						Speed Mode                                      */
	/************************************************************************/
	if (uart_lcfg_arr[ID_num].UART_Speed==UART_NORMAL_SPEED)
	{
		clear_bit(UCSRA,U2X);
	}
	else if (uart_lcfg_arr[ID_num].UART_Speed==UART_DOUBLE_SPEED)
	{
		set_bit(UCSRA,U2X);
	}

	/************************************************************************/
	/*						Parity Mode                                     */
	/************************************************************************/
	if (uart_lcfg_arr[ID_num].UART_Parity==NO_PARITY)
	{
		clear_bit(UCSRC,UPM0);
		clear_bit(UCSRC,UPM1);
	}
	else if (uart_lcfg_arr[ID_num].UART_Speed==EVEN_PARITY)
	{
		clear_bit(UCSRC,UPM0);
		set_bit(UCSRC,UPM1);
	}
	else if (uart_lcfg_arr[ID_num].UART_Speed==ODD_PARITY)
	{
		set_bit(UCSRC,UPM0);
		set_bit(UCSRC,UPM1);
	}

	/************************************************************************/
	/*						Stop Bit Number                                  */
	/************************************************************************/
	if (uart_lcfg_arr[ID_num].UART_StopBits==ONE_STOP_BIT)
	{
		clear_bit(UCSRC,USBS);
	}
	else if (uart_lcfg_arr[ID_num].UART_StopBits==TWO_STOP_BIT)
	{
		set_bit(UCSRC,USBS);
	}
	/************************************************************************/
	/*						Data Length                                     */
	/************************************************************************/
	if (uart_lcfg_arr[ID_num].UART_EnablePins==UART_5_BIT)
	{
		clear_bit(UCSRC,UCSZ0);
		clear_bit(UCSRC,UCSZ1);
	}
	else if (uart_lcfg_arr[ID_num].UART_DataSize==UART_6_BIT)
	{
		set_bit(UCSRC,UCSZ0);
		clear_bit(UCSRC,UCSZ1);
	}
	else if (uart_lcfg_arr[ID_num].UART_DataSize==UART_7_BIT)
	{
		clear_bit(UCSRC,UCSZ0);
		set_bit(UCSRC,UCSZ1);
	}
	else if (uart_lcfg_arr[ID_num].UART_DataSize==UART_8_BIT)
	{
		set_bit(UCSRC,UCSZ0);
		set_bit(UCSRC,UCSZ1);
	}


	/************************************************************************/
	/*						TX & RX Enable Mode                             */
	/************************************************************************/
	if (uart_lcfg_arr[ID_num].UART_EnablePins==UART_TX_ENABLE)
	{
		set_bit(UCSRB,TXEN);
	}
	else if (uart_lcfg_arr[ID_num].UART_EnablePins==UART_RX_ENABLE)
	{
		set_bit(UCSRB,RXEN);;
	}
	else if (uart_lcfg_arr[ID_num].UART_EnablePins==UART_TX_RX_ENABLE)
	{
		set_bit(UCSRB,TXEN);
		set_bit(UCSRB,RXEN);
	}
	
};






/******************************************************************************************************************/
	/************************************************************************/
	/*	Name:UART_transmit
	
		Description:-It sends a byte synchronously 
		
		Returns:-void
																			*/
	/************************************************************************/
	
void UART_transmit(uint8_t data)
{
	while (!read_bit(UCSRA,UDRE));
	UDR=data;

}










	/************************************************************************/
	/*	Name:UART_receive
	
		Description:-It receives a byte synchronously 
		
		Returns:-void
																			*/
	/************************************************************************/
uint8_t UART_receive(void)
{
	while (!read_bit(UCSRA,RXC));
	return UDR;
}










	/************************************************************************/
	/*	Name:UART_transmit_NoBlock
	
		Description:-It sends a byte asynchronously 
		
		Returns:-void
																			*/
	/************************************************************************/

void UART_transmit_NoBlock(uint8_t data)
{

	UDR=data;

}











	/************************************************************************/
	/*	Name:UART_receive_NoBlock
	
		Description:-It receives a byte asynchronously 
		
		Returns:-void
																			*/
	/************************************************************************/
	
uint8_t UART_receive_NoBlock(void)
{

	return UDR;
}









	/************************************************************************/
	/*	Name:UART_TX_INTENABLE
	
		Description:-It enables the transmit complete interrupt 
		
		Returns:-void
																			*/
	/************************************************************************/

void UART_TX_INTENABLE(void)
{
	set_bit(UCSRB,TXCIE);
}







	/************************************************************************/
	/*	Name:UART_RX_INTENABLE
	
		Description:-It enables the receive complete interrupt 
		
		Returns:-void
																			*/
	/************************************************************************/
void UART_RX_INTENABLE(void)
{
	set_bit(UCSRB,RXCIE);
}













	/*	Name:UART_TX_INTDISABLE
	
		Description:-It disables the transmit complete interrupt 
		
		Returns:-void
																			*/
	/************************************************************************/
	
void UART_TX_INTDISABLE(void)
{
	clear_bit(UCSRB,TXCIE);
}









	/************************************************************************/
	/*	Name:UART_RX_INTENABLE
	
		Description:-It disables the receive complete interrupt 
		
		Returns:-void
																			*/
	/************************************************************************/
	
void UART_RX_INTDISABLE(void)
{
	clear_bit(UCSRB,RXCIE);
}







	/************************************************************************/
	/*	Name:UART_SetCallBack
	
		Description:-It sets a callback function in the ISR
		
		Returns:-void
																			*/
	/************************************************************************/
void UART_SetCallBack(enu_Callback_t enu_Callback,void(*FPTR)(void))
{
	if (enu_Callback==Uart_tx_t)
	{
		UART_TRANS_Fptr=FPTR;
	}
	else if (enu_Callback==Uart_rx_t)
	{
		UART_RECE_Fptr=FPTR;
	}
	
}

/***********************************************/

ISR(UART_TX_vect)
{

	
	if (UART_TRANS_Fptr!=NULL_PTR)
	{
		UART_TRANS_Fptr();	
	}
	else
	{
		/*do Nothing*/
	}

	
}


/*************************************************/
ISR(UART_RX_vect)
{
	if (UART_RECE_Fptr!=NULL_PTR)
	{
		UART_RECE_Fptr();
	}
	else
	{
		/*do Nothing*/
	}

}