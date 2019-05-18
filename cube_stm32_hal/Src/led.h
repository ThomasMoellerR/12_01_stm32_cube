
/******************************************************************************
*  File           :  led.h
*  Version        :  1
*  Last Changes   :  2019-05-17 16:59:18
******************************************************************************/

#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
*  Include Files
******************************************************************************/

#include "typ.h"
#include "main.h"


/******************************************************************************
*  Global Constants
******************************************************************************/

#define	LED_ON   	GPIOB->BSRR = 1 << 13
#define LED_OFF 	GPIOB->BSRR = 1 <<(13 + 16)

#define	Layer3_SET				GPIOC->BSRR = 1<<12
#define	Layer2_SET				GPIOC->BSRR = 1<<10
#define	Layer1_SET				GPIOD->BSRR = 1<<0
#define	Layer0_SET				GPIOC->BSRR = 1<<11

#define	SM16126_DAT_A_SET  		GPIOC->BSRR = 1<<8
#define	SM16126_DAT_B_SET  		GPIOE->BSRR = 1<<2
#define	SM16126_DAT_C_SET  		GPIOE->BSRR = 1<<3

#define	SM16126_CLK_SET   		GPIOC->BSRR = 1<<7
#define	SM16126_STK_SET    		GPIOC->BSRR = 1<<6
#define	SM16126_OE_SET    		GPIOD->BSRR = 1<<15

#define	Layer3_RESET   			GPIOC->BSRR = 1<<(12 + 16)
#define	Layer2_RESET   			GPIOC->BSRR = 1<<(10 + 16)
#define	Layer1_RESET   			GPIOD->BSRR = 1<<(0 + 16)
#define	Layer0_RESET   			GPIOC->BSRR = 1<<(11 + 16)

#define	SM16126_DAT_A_RESET		GPIOC->BSRR = 1<<(8 + 16)
#define	SM16126_DAT_B_RESET		GPIOE->BSRR = 1<<(2 + 16)
#define	SM16126_DAT_C_RESET		GPIOE->BSRR = 1<<(3 + 16)

#define	SM16126_CLK_RESET   	GPIOC->BSRR = 1<<(7 + 16)
#define	SM16126_STK_RESET		GPIOC->BSRR = 1<<(6 + 16)
#define	SM16126_OE_RESET    	GPIOD->BSRR = 1<<(15 + 16)

#define CUBE_SIZE 	12
#define rgb_SIZE 	(CUBE_SIZE * CUBE_SIZE * CUBE_SIZE)

//#define ScanTime 		14
//#define ScanFosc 		32
#define ScanTime 		14
#define ScanFosc 		17

/******************************************************************************
*  Global Type Definitions
******************************************************************************/

typedef struct
{
	uint8_t R;
	uint8_t G;
	uint8_t B;
}CUBE_BYTE;


/******************************************************************************
*  Global Variables
******************************************************************************/


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
extern uint8_t CUBE_MODE;
extern uint8_t Light_Red, Light_Green, Light_Blue;


extern unsigned char u8Color_Channels[3][1728];
extern unsigned char u8Color_Trans_Complete;

extern const uint8_t LayerChar[12];


/******************************************************************************
*  Global Function Prototypes
******************************************************************************/



extern void GPIO_Configuration(void);
extern void NVIC_Configuration(void);
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


extern void Sytem_Star(void);
extern void delay_STms(uint32_t num);

extern unsigned char u8Color_Channels[3][1728];
extern unsigned char u8Color_Trans_Complete;

/******************************************************************************
*  Changes        :
*
*
*
******************************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* __LED_H */

/******************************************************************************
*  END OF FILE    :  led.h
******************************************************************************/











