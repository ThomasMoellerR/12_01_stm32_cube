#ifndef _LED_H
#define _LED_H

#include "stm32f4xx.h"
#include "stdlib.h"

#define	LED_ON   	GPIOB->BSRRH = 1 << 13   
#define LED_OFF 	GPIOB->BSRRL = 1 << 13  

    //快速IO 高电平
#define	Layer3_SET				GPIOC->BSRRL = 1<<12    
#define	Layer2_SET				GPIOC->BSRRL = 1<<10    
#define	Layer1_SET				GPIOD->BSRRL = 1<<0    	
#define	Layer0_SET				GPIOC->BSRRL = 1<<11    
		
#define	SM16126_DAT_A_SET  		GPIOC->BSRRL = 1<<8    
#define	SM16126_DAT_B_SET  		GPIOE->BSRRL = 1<<2    
#define	SM16126_DAT_C_SET  		GPIOE->BSRRL = 1<<3    

#define	SM16126_CLK_SET   		GPIOC->BSRRL = 1<<7    
#define	SM16126_STK_SET    		GPIOC->BSRRL = 1<<6    
#define	SM16126_OE_SET    		GPIOD->BSRRL = 1<<15    

    //快速IO 低电平
#define	Layer3_RESET   			GPIOC->BSRRH = 1<<12    
#define	Layer2_RESET   			GPIOC->BSRRH = 1<<10    
#define	Layer1_RESET   			GPIOD->BSRRH = 1<<0    	
#define	Layer0_RESET   			GPIOC->BSRRH = 1<<11   
		
#define	SM16126_DAT_A_RESET		GPIOC->BSRRH = 1<<8    
#define	SM16126_DAT_B_RESET		GPIOE->BSRRH = 1<<2    
#define	SM16126_DAT_C_RESET		GPIOE->BSRRH = 1<<3    

#define	SM16126_CLK_RESET   	GPIOC->BSRRH = 1<<7    
#define	SM16126_STK_RESET		GPIOC->BSRRH = 1<<6    
#define	SM16126_OE_RESET    	GPIOD->BSRRH = 1<<15  


typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}CUBE_BYTE;

#define CUBE_SIZE 	12
#define rgb_SIZE 	(CUBE_SIZE * CUBE_SIZE * CUBE_SIZE)
extern CUBE_BYTE 	rgbCUBE12[CUBE_SIZE * CUBE_SIZE * CUBE_SIZE];

extern const uint8_t DigitChar[8];
extern const uint16_t ScanTimeData[8];

extern uint8_t tf_readStop;
extern uint8_t tf_readRead;
extern uint8_t tf_readflag;

extern uint8_t fft_flag;
extern uint8_t flickerFlag;
extern uint8_t fft_MODE;
extern uint8_t BrightnessFlag;
extern uint8_t ADC_MODE;
extern uint8_t CUBE_MODE;							//光立方的显示模式
extern uint8_t Light_Red, Light_Green, Light_Blue;	//夜灯颜色变量


//#define ScanTime 		14							//定义最小的扫描时间
//#define ScanFosc 		32							//定义扫描频率,168M时钟
#define ScanTime 		14							//定义最小的扫描时间
#define ScanFosc 		17							//定义扫描频率,168M时钟

extern void GPIO_Configuration(void);          		//初始化GPIOx的输出
extern void NVIC_Configuration(void);				//中断优先级的分组设置 
extern void OFF_ALL(void);
extern void Set_row(uint8_t layer, uint8_t byBIT);
extern void LayerChoose(uint8_t dat);

extern void delay_ms(uint32_t num);
extern void ClearRGB(uint8_t rank_r, uint8_t rank_g, uint8_t rank_b);
extern void SetPoint(uint8_t x, uint8_t y, uint8_t z, uint8_t R, uint8_t G, uint8_t B);
extern void setPlaneX(uint8_t x, uint8_t R, uint8_t G, uint8_t B);
extern void setPlaneY(uint8_t y, uint8_t R, uint8_t G, uint8_t B);
extern void setPlaneZ(uint8_t z, uint8_t R, uint8_t G, uint8_t B);
extern void setAll(uint8_t R, uint8_t G, uint8_t B);


#endif

