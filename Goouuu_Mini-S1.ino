
/**
 * Goouuu Mini-S1 basic
 *
 * @author Bob Chen (bob-0505@gotmail.com)
 * @date 2 December 2017
 * github: https://github.com/Bob0505/
*/

#define SERIAL_BAUD 230400

#define LED_I	4
#define LED_R	12
#define LED_G	13
#define LED_B	14

uint8_t PinArray[] = {LED_I, LED_R, LED_G, LED_B};

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

  digitalWrite(Pin, LOW);     // set pin to the opposite state
  delay(500);
  digitalWrite(Pin, HIGH);
  delay(100);
}

void GPIO_HL()
{
	ClearLED();
	delay(500);

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
		Serial.print(val);  Serial.print(" => ");  Serial.println(PWM_MAX-val);
		analogWrite (LED_R, PWM_MAX-val);
		analogWrite (LED_G, PWM_MAX-val);
		analogWrite (LED_B, PWM_MAX-val);
		delay (500);
	}
}

// the setup function runs once when you press reset or power the board
void setup()
{
	// initialize digital pin LED_BUILTIN as an output.
	for(uint8_t idx=0;idx < sizeof(PinArray)/sizeof(uint8_t);idx++)
	{
		pinMode(PinArray[idx], OUTPUT);
	}
	ClearLED();

	Serial.begin(SERIAL_BAUD); Serial.println("\nHello World");
}

// the loop function runs over and over again forever
void loop()
{
	Serial.println("[GPIO High Low]");
	GPIO_HL();

	//need to check
	//Serial.println("[GPIO PWM_Mode]");
	//PWM_Mode();

	Serial.println("--- ---");
}
