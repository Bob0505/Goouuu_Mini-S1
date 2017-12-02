#ifndef _LED_H_
#define _LED_H_

#include <Arduino.h>
#include <stdint.h>

//#include "HardwareSerial.h"

void InitGPOs();
void ClearLED();
void tick(uint8_t Pin);
void GPIO_HL();
void PWM_Mode();

#endif	/*_LED_H_*/