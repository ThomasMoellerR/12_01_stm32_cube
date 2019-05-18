//--------------------------------------------------------------
// File     : stm32_ub_spi2_slave.c
// Datum    : 01.02.2014
// Version  : 1.0
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.4
// GCC      : 4.7 2012q4
// Module   : GPIO, SPI, MISC
// Funktion : SPI-Slave-Funktionen (SPI-1)
//            Erstellt ein virtuelles SPI-RAM
//
// Hinweis  : mögliche Pinbelegungen
//            SPI2 : SCK :[PB10, PB13] 
//                   MOSI:[PB15, PC3]
//                   MISO:[PB14, PC2]
//                   NSS :[PB9 , PB12] (SlaveSelect)
//
// CMD-01   : lesend der ID vom Slave
//            Master : 0x01 ,Dummy,Dummy
//            Slave  : Dummy,0x32 ,0x07
//
// CMD-02   : schreiben von einem Byte ins RAM vom Slave
//            Master : 0x02 ,Adr  ,Daten
//            Slave  : Dummy,Dummy,Dummy
//  
// CMD-03   : lesen von einem Byte vom RAM vom Slave
//            Master : 0x03 ,Adr  ,Dummy
//            Slave  : Dummy,Dummy,Daten
//
//--------------------------------------------------------------

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_spi2_slave.h"
#include "System.h"
#include "stm32_ub_ext_int0.h"


uint8_t u8SPI_State_Machine = 0;
uint8_t u8DMA_Finished = 0;



//--------------------------------------------------------------
// interne Funktionen
//--------------------------------------------------------------




//--------------------------------------------------------------
// Globale Variabeln
//--------------------------------------------------------------
SPI2_SLAVE_MODE_t spi2_mode=SPI2_MODE_WAITING;
uint8_t spi2_ram_adr=0;
uint8_t spi2_ram[SPI2_RAM_SIZE+1];



//--------------------------------------------------------------
// Definition von SPI2
//--------------------------------------------------------------
SPI2_SDEV_t SPI2DEV = {
// PORT , PIN       , Clock              , Source 
  {GPIOB,GPIO_Pin_13,RCC_AHB1Periph_GPIOB,GPIO_PinSource13}, // SCK an PB13
  {GPIOB,GPIO_Pin_15,RCC_AHB1Periph_GPIOB,GPIO_PinSource15}, // MOSI an PB15
  {GPIOB,GPIO_Pin_14,RCC_AHB1Periph_GPIOB,GPIO_PinSource14}, // MISO an PB14
  {GPIOB,GPIO_Pin_12,RCC_AHB1Periph_GPIOB,GPIO_PinSource12}, // NSS an PB12
};



//--------------------------------------------------------------
// Init von SPI2 (als Slave)
// Return_wert :
//  -> ERROR   , wenn SPI schon mit anderem Mode initialisiert
//  -> SUCCESS , wenn SPI init ok war
//--------------------------------------------------------------
ErrorStatus UB_SPI2_Slave_Init(SPI2_SMode_t mode)
{



  GPIO_InitTypeDef  GPIO_InitStructure;

  // Clock Enable der Pins
  RCC_AHB1PeriphClockCmd(SPI2DEV.SCK.CLK, ENABLE);
  RCC_AHB1PeriphClockCmd(SPI2DEV.MOSI.CLK, ENABLE);
  RCC_AHB1PeriphClockCmd(SPI2DEV.MISO.CLK, ENABLE);
  RCC_AHB1PeriphClockCmd(SPI2DEV.NSS.CLK, ENABLE);

  // SPI Alternative-Funktions mit den IO-Pins verbinden
  GPIO_PinAFConfig(SPI2DEV.SCK.PORT, SPI2DEV.SCK.SOURCE, GPIO_AF_SPI2);
  GPIO_PinAFConfig(SPI2DEV.MOSI.PORT, SPI2DEV.MOSI.SOURCE, GPIO_AF_SPI2);
  GPIO_PinAFConfig(SPI2DEV.MISO.PORT, SPI2DEV.MISO.SOURCE, GPIO_AF_SPI2);
  GPIO_PinAFConfig(SPI2DEV.NSS.PORT, SPI2DEV.NSS.SOURCE, GPIO_AF_SPI2);

  // SPI als Alternative-Funktion mit PullDown
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;

  // SCK-Pin
  GPIO_InitStructure.GPIO_Pin = SPI2DEV.SCK.PIN;
  GPIO_Init(SPI2DEV.SCK.PORT, &GPIO_InitStructure);
  // MOSI-Pin
  GPIO_InitStructure.GPIO_Pin = SPI2DEV.MOSI.PIN;
  GPIO_Init(SPI2DEV.MOSI.PORT, &GPIO_InitStructure);
  // MISO-Pin
  GPIO_InitStructure.GPIO_Pin = SPI2DEV.MISO.PIN;
  GPIO_Init(SPI2DEV.MISO.PORT, &GPIO_InitStructure);
  // NSS-Pin
  GPIO_InitStructure.GPIO_Pin = SPI2DEV.NSS.PIN;
  GPIO_Init(SPI2DEV.NSS.PORT, &GPIO_InitStructure);




  // SPI
  SPI_InitTypeDef  SPI_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

  SPI_I2S_DeInit(SPI2);

  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  if((mode==SPI_SMODE_0_MSB) || (mode==SPI_SMODE_0_LSB)) {
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  }else if((mode==SPI_SMODE_1_MSB) || (mode==SPI_SMODE_1_LSB)) {
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  }else if((mode==SPI_SMODE_2_MSB) || (mode==SPI_SMODE_2_LSB)) {
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  }else {
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
  }
  SPI_InitStructure.SPI_NSS = SPI_NSS_Hard;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI2_VORTEILER;

  if((mode==SPI_SMODE_0_MSB) || (mode==SPI_SMODE_1_MSB) ||
     (mode==SPI_SMODE_2_MSB) || (mode==SPI_SMODE_3_MSB)) {
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  }
  else {
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_LSB;
  } 

  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);



  SPI_Cmd(SPI2, ENABLE);
















  NVIC_InitTypeDef  NVIC_InitStructure;
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // DMA
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
  DMA_DeInit(DMA1_Stream3);
  DMA_InitTypeDef DMA_InitStructure;
  DMA_StructInit(&DMA_InitStructure);
  DMA_InitStructure.DMA_BufferSize = SPI2_DMA_BUF_SIZE ;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_PeripheralBaseAddr =(uint32_t) (&(SPI2->DR)) ;        // Peripherie
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;

  // RX
  DMA_InitStructure.DMA_Channel = DMA_Channel_0 ;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory ;
  DMA_InitStructure.DMA_Memory0BaseAddr =(uint32_t)SPI2_RxBuf;					 // Speicher
  DMA_Init(DMA1_Stream3, &DMA_InitStructure);

  DMA_ITConfig(DMA1_Stream3, DMA_IT_TC, ENABLE);

  SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);

  DMA_Cmd(DMA1_Stream3,ENABLE);


  return(0);
}


void SPI2_IRQHandler(void)
{
	unsigned char temp = SPI_I2S_ReceiveData(SPI2);

}

void DMA1_Stream3_IRQHandler(void)
{
	DMA_ClearITPendingBit(DMA1_Stream3, DMA_IT_TCIF3);

	// Wenn 5184 Bytes emfpangen wurden
}

void SPI2_DMA_RX_ISR(void)
{


}

