#ifndef  __System_H__
#define __System_H__

#include "stm32f4xx.h"


#include "led.h"
#include "timer.h"

#include "malloc.h"

#include "stm32_ub_spi2_slave.h"



extern void Sytem_Star(void);
extern void delay_STms(uint32_t num);








extern unsigned char u8Color_Channels[3][1728];
extern unsigned char u8Color_Trans_Complete;



#endif






