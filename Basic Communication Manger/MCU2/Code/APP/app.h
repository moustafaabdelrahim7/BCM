

#ifndef APP_H_
#define APP_H_
#include "../Service/bcm/bcm.h"
#include "../HAL/led/LED.h"
uint8_t	static *str[100]={0};

void APP_Start(void);
void APP_Init(void);
void Func_after_Send(void);
void Func_after_Receive(void);

#endif /* APP_H_ */