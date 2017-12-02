
//#include "C:\WorkSpace\Code\Goouuu_Mini-S1\LED.h"
#include "LED.h"

const uint8_t PinArray[] = {LED_I, LED_R, LED_G, LED_B};

void InitGPOs()
{
	for(uint8_t idx=0;idx < sizeof(PinArray)/sizeof(uint8_t);idx++)
	{
		pinMode(PinArray[idx], OUTPUT);
	}
}

void ClearLED()
{
	for(uint8_t idx=0;idx < sizeof(PinArray)/sizeof(uint8_t);idx++)
	{
		digitalWrite(PinArray[idx], HIGH);
	}
}

void tick(uint8_t Pin)
{
  //toggle state
  bool state = digitalRead(Pin); // get the current state of GPIO1 pin

  digitalWrite(Pin, state);     // set pin to the opposite state
  delay(500);
  digitalWrite(Pin, !state);
  delay(100);
}

void GPIO_HL()
{
	for(uint8_t idx=0;idx < sizeof(PinArray)/sizeof(uint8_t);idx++)
	{
		tick(PinArray[idx]);
	}
}

void PWM_Mode()
{
	const uint8_t LED_PWM_MAX = 70, gap = 10, PWM_MAX = 255;
	uint8_t val;

	for (val=0; val<gap*(LED_PWM_MAX/gap); val+=gap)
	{
		//Serial.print(val);  Serial.print(" => ");  Serial.println(PWM_MAX-val);
		analogWrite (LED_R, PWM_MAX-val);
		analogWrite (LED_G, PWM_MAX-val);
		analogWrite (LED_B, PWM_MAX-val);
		delay (500);
	}
}
