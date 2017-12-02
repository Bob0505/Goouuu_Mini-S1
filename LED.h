#ifndef _LED_H_
#define _LED_H_

#define LED_I	4
#define LED_R	12
#define LED_G	13
#define LED_B	14

#include <Arduino.h>
#include <stdint.h>

//#include "HardwareSerial.h"

void InitGPOs();
void ClearLED();
void tick(uint8_t Pin);
void GPIO_HL();
void PWM_Mode();

#endif	/*_LED_H_*/