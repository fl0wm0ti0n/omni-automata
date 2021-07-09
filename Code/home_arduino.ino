// @file           home_arduino.ino
// @author         flow@p0cki.net
// @date           12.2016
// @brief          main routine

#include "constants.h"
#if (NodeMCUV3 == true)
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#endif

#include "FastLED.h"
#include <DHT.h>
#include "motionSensor.h"
#include "analogOut.h"
#include "dhtSensor.h"
#include "gasSensor.h"
#include "logger.h"
#include "decisions.h"
#include "neopixel.h"
#include "directionEncoder.h"

//*******************************************************
//********************* DECLARATION *********************
//*******************************************************

// Objekte welche sofort benötigt werden.
logger Logging_one(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, "Logging1");
analogOut LightStripe_one("lightstripe 1", PIN_PWM_2);
neopixel WS2812Stripe("WS2812", PIN_WS2812_1, NUM_LEDS_1);
motionSensor Motionsensor_one("motionsensor 1", PIN_MOTION_1);
dhtSensor DHTSensor_one("dhtsensor 1", PIN_HUM_1);
//decisions LightUpStripe(lightOn,"LichtAnAus");
decisions ChangeColor(colorChange, "FarbeNachTemp");
//directionEncoder encoder_one("RichtungsEncoder", PIN_ENCODER_SW, PIN_ENCODER_CLK, PIN_ENCODER_DT);
//gasSensor gasSensor("gassensor 1 - MQ135", PIN_GAS_MQ135_1);
//gasSensor gasSensor2("gassensor 2 - MQ7", PIN_GAS_MQ7_1);

// Variablen deklarieren in denen die Startzeiten
// der einzelnen Zeitfunktionen gespeichert werden
unsigned long startzeit_1 = 0;
unsigned long startzeit_2 = 0;
unsigned long startzeit_3 = 0;
unsigned long startzeit_4 = 0;
unsigned long startzeit_5 = 0;

void motionCheckForLight()
{
	Logging_one.writeLog("Call - motionCheckForLight", extremedebug);
	bool motionResult = Motionsensor_one.getValue(Logging_one);
	//bool motionResult = encoder_one.getSwitchLongValue(Logging_one);
	LightStripe_one.SlowlyIncreaseOrDecreaseValue(motionResult, DEFAULT_MAXVALUE, Logging_one);
}

void motionCheckForNeopixel()
{
	Logging_one.writeLog("Call - motionCheckForNeopixel", extremedebug);
	int motionResult = Motionsensor_one.getValue(Logging_one);
	WS2812Stripe.SlowlyIncreaseOrDecreaseBrightness(DEFAULT_ALLLEDS, motionResult, DEFAULT_MAXVALUE, Logging_one);
}

void dhtCheck()
{
	Logging_one.writeLog("Call - dhtCheck", extremedebug);
	bool motionResult = Motionsensor_one.getValue(Logging_one);
	float hum = DHTSensor_one.getHumValueOnlyIfChanged(Logging_one);
	float temp = DHTSensor_one.getTempValueOnlyIfChanged(Logging_one);
	
	if (motionResult == true)
	{ 
			WS2812Stripe.setHue(DEFAULT_ALLLEDS, ChangeColor.colorTemperaturChange(temp, hum, Logging_one), Logging_one);
	}
}

	//*******************************************************
	//************************ SETUP ************************
	//*******************************************************
void setup()
{
	Logging_one.writeLog("Setup Begin", debug);
	WS2812Stripe.InitNeoPixel(DEFAULT_MAXVALUE, DEFAULT_MAXVALUE, Logging_one);
	//encoder_one.setClickValue(0.5, Logging_one);
	WS2812Stripe.setStep(0.05);
	Logging_one.writeLog("Setup End", debug);
}

	//*******************************************************
	//************************ LOOP *************************
	//*******************************************************
void loop()
{
	/*// Alle 1 Millisekunden...
	if (millis() - startzeit_4 >= laufzeit_1)
	{
		startzeit_4 = millis();
		WS2812Stripe.colorshift(encoder_one.getEncoderValue(Logging_one), true, Logging_one);
	}*/

	// Alle 100 Millisekunden...
	if (millis() - startzeit_1 >= laufzeit_100)
	{
		startzeit_1 = millis();
		motionCheckForLight();
	}

	// Alle 500 Millisekunden...
	if (millis() - startzeit_2 >= laufzeit_500)
	{
		startzeit_2 = millis();
		dhtCheck();
	}

	// Alle 150 Millisekunden...
	if (millis() - startzeit_3 >= laufzeit_150)
	{
		startzeit_3 = millis();
		motionCheckForNeopixel();
	}
}