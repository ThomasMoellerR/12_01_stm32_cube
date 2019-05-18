//--------------------------------------------------------------
// File     : stm32_ub_spi2_slave.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32F4_UB_SPI2_SLAVE_H
#define __STM32F4_UB_SPI2_SLAVE_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "misc.h"



//--------------------------------------------------------------
// Defines
//--------------------------------------------------------------
#define  SPI2_RAM_SIZE   0xFF    // RAM Größe in Byte (1 bis 255)

#define  SPI2_CMD_RD_ID    0x01  // Read-ID Command
#define  SPI2_CMD_WR_BYTE  0x02  // Write Byte Command
#define  SPI2_CMD_RD_BYTE  0x03  // Read Byte Command


#define  SPI2_ID0          0x32  // ID Byte0
#define  SPI2_ID1          0x07  // ID Byte1




//--------------------------------------------------------------
// SPI-Mode
//--------------------------------------------------------------
typedef enum {
  SPI_SMODE_0_MSB = 0,  // CPOL=0, CPHA=0 (MSB-First)
  SPI_SMODE_1_MSB,      // CPOL=0, CPHA=1 (MSB-First)
  SPI_SMODE_2_MSB,      // CPOL=1, CPHA=0 (MSB-First)
  SPI_SMODE_3_MSB,      // CPOL=1, CPHA=1 (MSB-First)
  SPI_SMODE_0_LSB,      // CPOL=0, CPHA=0 (LSB-First)
  SPI_SMODE_1_LSB,      // CPOL=0, CPHA=1 (LSB-First)
  SPI_SMODE_2_LSB,      // CPOL=1, CPHA=0 (LSB-First)
  SPI_SMODE_3_LSB       // CPOL=1, CPHA=1 (LSB-First)
}SPI2_SMode_t;


//--------------------------------------------------------------
// SPI-Clock (beim Slave nicht Wichtig)
// Grundfrequenz (SPI2)= APB1 (APB1=42MHz)
// Mögliche Vorteiler = 2,4,8,16,32,64,128,256
//--------------------------------------------------------------

//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_2   // Frq = 21 MHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_4   // Frq = 10,5 MHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_8   // Frq = 5.25 MHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_16  // Frq = 2.625 MHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_32  // Frq = 1.3125 MHz
#define SPI2_VORTEILER     SPI_BaudRatePrescaler_64  // Frq = 656.2 kHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_128 // Frq = 328.1 kHz
//#define SPI2_VORTEILER     SPI_BaudRatePrescaler_256 // Frq = 164.0 kHz




//--------------------------------------------------------------
// Struktur eines SPI-Pins
//--------------------------------------------------------------
typedef struct {
  GPIO_TypeDef* PORT;     // Port
  const uint16_t PIN;     // Pin
  const uint32_t CLK;     // Clock
  const uint8_t SOURCE;   // Source
}SPI2_PIN_t; 


//--------------------------------------------------------------
// Struktur vom SPI-Device
//--------------------------------------------------------------
typedef struct {
  SPI2_PIN_t  SCK;        // SCK-Pin
  SPI2_PIN_t  MOSI;       // MOSI-Pin
  SPI2_PIN_t  MISO;       // MISO-Pin
  SPI2_PIN_t  NSS;        // NSS-Pin
}SPI2_SDEV_t;


//--------------------------------------------------------------
typedef enum {
  SPI2_MODE_WAITING =0,    // warte auf Befehle
  SPI2_MODE_RD_ID0,        // ID0 lesen
  SPI2_MODE_RD_ID1,        // ID1 lesen
  SPI2_MODE_WR_ADR,        // Adresse (zum schreiben)
  SPI2_MODE_WR_DATA,       // Daten (zum schreiben)
  SPI2_MODE_RD_ADR,        // Adresse (zum lesen)
  SPI2_MODE_RD_DATA        // Daten (zum lesen)
}SPI2_SLAVE_MODE_t;




//--------------------------------------------------------------
// Globale Funktionen
//--------------------------------------------------------------
ErrorStatus UB_SPI2_Slave_Init(SPI2_SMode_t mode);

extern void Configure_SPI_DMA(void);



#define  SPI2_DMA_BUF_SIZE   5184
uint8_t SPI2_RxBuf[SPI2_DMA_BUF_SIZE]; // Zwischenspeicher




//--------------------------------------------------------------
#endif // __STM32F4_UB_SPI2_SLAVE_H
