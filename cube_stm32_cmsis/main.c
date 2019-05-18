#include "system.h"

int main(void)
{
	SystemInit();

    GPIO_Configuration();
	NVIC_Configuration();

	Timer4_Init(ScanFosc, ScanTime);

	UB_SPI2_Slave_Init(SPI_SMODE_2_MSB);
	UB_Ext_INT0_Init();

	setAll(0, 0, 0);

	SetPoint(1, 0, 0, 255, 0, 0);


    while(1)
    {
    	int cnt = 0;
    	for (int i = 0; i < 1728; i++) rgbCUBE12[i].R = SPI2_RxBuf[cnt++];
    	for (int i = 0; i < 1728; i++) rgbCUBE12[i].G = SPI2_RxBuf[cnt++];
    	for (int i = 0; i < 1728; i++) rgbCUBE12[i].B = SPI2_RxBuf[cnt++];
    }
}
