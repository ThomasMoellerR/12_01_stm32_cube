#include "system.h"



#define TIMERSR 	(TIM_IT_Update ^ 0xffff)




const uint8_t LayerChar[12] = {11,10,9,8,7,6,5,4,3,2,1,0};

void TIM4_IRQHandler(void)
{
	static uint8_t Layer = 0;							
	static uint8_t Digit = 0;							
	if ((TIM4->SR & TIM_IT_Update) != (uint16_t)RESET && 
		(TIM4->DIER & TIM_IT_Update) != (uint16_t)RESET)	
	{
		TIM4->SR = TIMERSR;									

		if (++Layer >= 12)									
		{
			Layer = 0;									
			if (++Digit >= 8)								
				Digit = 0;									
			
			TIM4->ARR = ScanTimeData[Digit];			
		}
		
		SM16126_OE_SET;
		LayerChoose(LayerChar[Layer]);
		Set_row(Layer,Digit);
		
		SM16126_OE_RESET;
	}
}




void delay_STms(uint32_t num)
{
	uint32_t i,j;
	for(i = 0; i < num; i++)
		for(j = 0; j < 168000; j++)
		{}
}




void Sytem_Star(void)
{
	int i = 0;
	setAll(0,0,0);
	for(i = 0; i < 12; i++)
	{
		if(i)
			setPlaneX(i - 1, 0, 0, 0);
		setPlaneX(i, 255, 0, 0);
		delay_ms(50);
	}
	setAll(0,0,0);
	for(i = 0; i < 12; i++)
	{
		if(i)
			setPlaneY(i - 1, 0, 0, 0);
		setPlaneY(i, 0, 255, 0);
		delay_ms(50);
	}
	setAll(0,0,0);
	for(i = 0; i < 12; i++)
	{
		if(i)
			setPlaneZ(i - 1, 0, 0, 0);
		setPlaneZ(i, 0, 0, 255);
		delay_ms(50);
	}
}


unsigned char u8Color_Channels[3][1728];
unsigned char u8Color_Trans_Complete = 0;


