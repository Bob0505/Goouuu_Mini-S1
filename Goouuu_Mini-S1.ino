
/**
 * Goouuu Mini-S1 basic
 *
 * @author Bob Chen (bob-0505@gotmail.com)
 * @date 2 December 2017
 * github: https://github.com/Bob0505/
*/

// https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_Sensor.h>
// https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>
#include <DHT_U.h>
//#include "C:\WorkSpace\Code\Goouuu_Mini-S1\LED.h"
#include "LED.h"

#define SERIAL_BAUD 230400

#define DHTPIN  5		// Pin which is connected to the DHT sensor.
#define DHTTYPE	DHT22	// DHT 22 (AM2302)
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void DHT22_setup()
{
	// Initialize device.
	dht.begin();
	Serial.println("DHT22 Unified Sensor Example");
	// Print temperature sensor details.
	sensor_t sensor;
	dht.temperature().getSensor(&sensor);
	Serial.println("------------------------------------");
	Serial.println("Temperature");
	Serial.print  ("Sensor:       "); Serial.println(sensor.name);
	Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
	Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
	Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
	Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
	Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
	Serial.println("------------------------------------");
	// Print humidity sensor details.
	dht.humidity().getSensor(&sensor);
	Serial.println("------------------------------------");
	Serial.println("Humidity");
	Serial.print  ("Sensor:       "); Serial.println(sensor.name);
	Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
	Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
	Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
	Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
	Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
	Serial.println("------------------------------------");
	// Set delay between sensor readings based on sensor details.
	delayMS = sensor.min_delay / 1000;
	Serial.print  ("delayMS:   "); Serial.println(delayMS);  
	Serial.println("------------------------------------");
}

void DHT22_loop()
{
	static bool LED_STATUS;
	// Delay between measurements.
	delay(delayMS);
	digitalWrite(LED_G, LED_STATUS);	// turn the LED on (HIGH is the voltage level)
	LED_STATUS = !LED_STATUS;

	// Get temperature event and print its value.
	sensors_event_t event;
	dht.temperature().getEvent(&event);
	if (isnan(event.temperature)) {
		Serial.println("Error reading temperature!");
	}
	else {
		Serial.print("Temperature: ");
		Serial.print(event.temperature);
		Serial.println(" *C");
	}
	// Get humidity event and print its value.
	dht.humidity().getEvent(&event);
	if (isnan(event.relative_humidity)) {
		Serial.println("Error reading humidity!");
	}
	else {
		Serial.print("Humidity: ");
		Serial.print(event.relative_humidity);
		Serial.println("%");
	}
}

// the setup function runs once when you press reset or power the board
void setup()
{
	// initialize digital pin LED_BUILTIN as an output.
	//InitGPOs();
	//ClearLED();
	pinMode(LED_G, OUTPUT);

	Serial.begin(SERIAL_BAUD); Serial.println("\nHello World");
	Serial.println("[GPIO High Low]");

	//GPIO_HL();
	DHT22_setup();
}

// the loop function runs over and over again forever
void loop()
{
	//need to check
	//Serial.println("[GPIO PWM_Mode]");
	//PWM_Mode();

	DHT22_loop();
	Serial.println("--- ---");
}
