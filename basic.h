#ifndef _BASIC_H_
#define _BASIC_H_

enum GPIOs
{
	GPIO00		= 0,	//			SPI_CS2
	UART0_TXD	= 1,	//UART0_TXD	SPI_CS1
	UART1_TXD	= 2,	//UART1_TXD	
	UART0_RXD	= 3,	//UART0_RXD	
	GPIO04		= 4,	//			I2C_SDA
	GPIO05		= 5,	//			I2C_SCL
	GPIO12		= 12,	//			HSPI_MISO
	GPIO13		= 13,	//UART0_CTS	HSPI_MOSI
	GPIO14		= 14,	//			HSPI_CLK
	GPIO15		= 15,	//UART0_RTS	HSPI_CS		MTDO
	GPIO16		= 16	//Deep sleep wakeup
};

#define LED_I		GPIO04
#define LED_R		GPIO12
#define LED_G		GPIO13
#define LED_B		GPIO14

#define DHT_PIN_A	GPIO00
#define DHT_PIN_B	GPIO05

#endif	/*_LED_H_*/