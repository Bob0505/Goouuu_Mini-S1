
/**
 * Goouuu Mini-S1 basic
 *
 * @author Bob Chen (bob-0505@gotmail.com)
 * @date 2 December 2017
 * github: https://github.com/Bob0505/
*/

#include "basic.h"
#include "LED.h"

// https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_Sensor.h>
// https://github.com/adafruit/DHT-sensor-library
#include <DHT.h>
#include <DHT_U.h>
//#include "C:\WorkSpace\Code\Goouuu_Mini-S1\LED.h"
#include <ESP8266WiFi.h>
//https://github.com/JChristensen/Timer
#include <Timer.h>

#define SERIAL_BAUD 230400

//*-- IoT Information
#define SSID	"AP_Name"
#define PASS	"AP_Password"
#define HOST	"api.thingspeak.com" // ThingSpeak IP Address: 184.106.153.149
#define PORT	80
// using GET to send data
// GET /update?key=[THINGSPEAK_KEY]&field1=[data 1]&filed2=[data 2]...;
String GET = "GET /update?key=5BL7QOK501MKJTW8";

#define DHTTYPE	DHT22	// DHT 22 (AM2302)
DHT_Unified DHT_A(DHT_PIN_A, DHTTYPE);
DHT_Unified DHT_B(DHT_PIN_B, DHTTYPE);
uint32_t delayMS;

Timer Task_250ms;
Timer Task_5s;
Timer Task_60s;

static RET_STATUS G_Status;

void DHT22_setup(DHT_Unified dht)
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

void Wifi_setup()
{
    // Connecting to a WiFi network
    Serial.print("Connect to ");
    Serial.println( SSID );
    WiFi.begin( SSID, PASS );

    // wait connect WiFi SSID
    while( WiFi.status() != WL_CONNECTED )
    {
        delay(500);
        Serial.print( "." );
    }
    Serial.println( "" );

    Serial.println( "WiFi connected" );
    Serial.println( "IP address: " );
    Serial.println( WiFi.localIP() );
}

RET_STATUS DHT22_loop(DHT_Unified dht, float* temp, float* humi)
{
	RET_STATUS Status = RET_SUCCESS;
	// Delay between measurements.
	//delay(delayMS);

	// Get temperature event and print its value.
	sensors_event_t event;
	dht.temperature().getEvent(&event);
	if (isnan(event.temperature)) {
		Serial.println("Error reading temperature!");
		//SET_BIT(Status, b_RET_DHT22_TEMP_ERROR);
		Status|= (1 << b_RET_DHT22_TEMP_ERROR);
	}
	else {
		//Serial.print("Temperature: ");
		//Serial.print("Temp: ");
		//Serial.print(event.temperature);
		//Serial.println(" *C");
		*temp = event.temperature;
	}
	// Get humidity event and print its value.
	dht.humidity().getEvent(&event);
	if (isnan(event.relative_humidity)) {
		Serial.println("Error reading humidity!");
		//SET_BIT(Status, b_RET_DHT22_HUMI_ERROR);
		Status|= (1 << b_RET_DHT22_HUMI_ERROR);
	}
	else {
		//Serial.print("Humidity: ");
		//Serial.print("Humi: ");
		//Serial.print(event.relative_humidity);
		//Serial.println("%");
		*humi = event.relative_humidity;
	}

	return Status;
}

RET_STATUS Wifi_loop(float temp_A, float humi_A, float temp_B, float humi_B)
{
	RET_STATUS Status = RET_SUCCESS;

	// setting ESP8266 as Client
	WiFiClient client;
	if( !client.connect( HOST, PORT ) )
	{
		Serial.println( "connection failed" );
		//SET_BIT(Status, b_RET_WIFI_HUMI_ERROR);
		Status|= (1 << b_RET_WIFI_CNT_ERROR);
	}
	else
	{
		String getStr = GET + "&field1=" + String(temp_A) + 
							  "&field2=" + String(humi_A) +
							  "&field3=" + String(temp_B) + 
							  "&field4=" + String(humi_B) +
							  " HTTP/1.1\r\n";;
		client.print( getStr );
		client.print( "Host: api.thingspeak.com\n" );
		client.print( "Connection: close\r\n\r\n" );

		delay(10);
		client.stop();
	}

	return Status;
}

RET_STATUS UpdateTemp()
{
	RET_STATUS Status = RET_SUCCESS;

	float temp_A, humi_A, temp_B, humi_B;
	//need to check
	//Serial.println("[GPIO PWM_Mode]");
	//PWM_Mode();

	Serial.println("[A]");
	Status  = DHT22_loop(DHT_A, &temp_A, &humi_A);
	Serial.print("  Temp: ");	Serial.print(temp_A);	Serial.println(" *C");
	Serial.print("  Humi: ");	Serial.print(humi_A);	Serial.println(" %");

	Serial.println("[B]");
	Status |= DHT22_loop(DHT_B, &temp_B, &humi_B);
	Serial.print("  Temp: ");	Serial.print(temp_B);	Serial.println(" *C");
	Serial.print("  Humi: ");	Serial.print(humi_B);	Serial.println(" %");

	if(Status == RET_SUCCESS)
	{
		Serial.println("Upload data to thingspeak...");
		Status = Wifi_loop(temp_A, humi_A, temp_B, humi_B);
	}

	return Status;
}

void Update_LED()
{
	static bool LED_STATUS;

	if(G_Status == RET_SUCCESS)
	{
		digitalWrite(LED_I, LED_STATUS);	// turn the LED on (HIGH is the voltage level)
		LED_STATUS = !LED_STATUS;
	} else {
		digitalWrite(LED_I, HIGH);
	}
}

void task_250ms()
{
	Update_LED();
}

void task_5s()
{
	static uint8_t cnt = 0;

	Serial.print("*");
	if(cnt>=5)
		Serial.println("");
}

void task_60s()
{
	Serial.println("");

	G_Status = UpdateTemp();
	Serial.print("G_Status: ");	Serial.println(G_Status);

	Serial.println("--- ---");
}

// the setup function runs once when you press reset or power the board
void setup()
{
	// initialize digital pin LED_BUILTIN as an output.
	//InitGPOs();
	//ClearLED();
	pinMode(LED_I, OUTPUT);
	pinMode(LED_I, HIGH);
	Serial.begin(SERIAL_BAUD); Serial.println("\nHello World");

	//Serial.println("[GPIO High Low]");
	//GPIO_HL();

	DHT22_setup(DHT_A);
	DHT22_setup(DHT_B);

	Wifi_setup();

	Task_250ms.every(250, task_250ms);
	Task_5s.every(5*1000, task_5s);
	Task_60s.every(60*1000, task_60s);
	
	G_Status = RET_SUCCESS;
	task_60s();
}

// the loop function runs over and over again forever
void loop()
{
	Task_250ms.update();
	Task_5s.update();
	Task_60s.update();
}
