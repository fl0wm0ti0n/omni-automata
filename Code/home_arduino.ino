// @file           home_arduino.ino
// @author         flow@p0cki.net
// @date           12.2016
// @brief          main routine

#include <Bounce2.h>
#include "constants.h"		// Constanten müssen vor allem anderen initialisiert werden

// Wenn als Board das NodeMCU V3 gewählt wurde wird dies entsprechend freigeschalten.
#if (NodeMCUV3 == true)
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#endif

#include "FastLED.h"
#include <DHT.h>
#include "motionSensor.h"
#include "analogOut.h"
#include "dhtSensor.h"
#include "logger.h"
#include "decisions.h"
#include "neopixel.h"
#include "directionEncoder.h"
#include "PinChangeInt.h"
#include "pgmStrToRAM/MemoryFree.h"
#include "pgmStrToRAM/pgmStrToRAM.h"

//*******************************************************
//********************* DECLARATION *********************
//*******************************************************
// Objekte welche sofort benötigt werden.
logger* Logging_one = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, "Logging1");
analogOut LightStripe_one("lightstripe 1", PIN_PWM_1);
neopixel WS2812Stripe("WS2812", PIN_WS2812_1, NUM_LEDS_1);
motionSensor Motionsensor_one("motionsensor 1", PIN_MOTION_1);
dhtSensor DHTSensor_one("dhtsensor 1", PIN_HUM_1);
//decisions LightUpStripe(lightOn,"LichtAnAus");
decisions ChangeColor(colorChange, "FarbeNachTemp");
directionEncoder encoder_one("RichtungsEncoder", PIN_ENCODER_SW, PIN_ENCODER_CLK, PIN_ENCODER_DT);

// Variablen deklarieren in denen die Startzeiten
// der einzelnen Zeitfunktionen gespeichert werden
unsigned long startzeit_1 = 0;
unsigned long startzeit_2 = 0;
unsigned long startzeit_3 = 0;
unsigned long startzeit_4 = 0;
unsigned long startzeit_5 = 0;

/*volatile boolean volatSignal = false;
volatile boolean volatSignalSet = false;
volatile boolean volatSignalOld = false;
volatile uint16_t interruptCount = 0;*/

//*******************************************************
//********************** Methoden ***********************
//*******************************************************

void motionCheckForLight()
{
	Logging_one->LnWriteLog("Call - motionCheckForLight", extremedebug);
	bool motionResult = Motionsensor_one.getValue();
	//bool motionResult = encoder_one.getSwitchLongValue(Logging_one);
	LightStripe_one.SlowlyIncreaseOrDecreaseValue(motionResult, DEFAULT_MAXVALUE);
}

void motionCheckForNeopixel()
{
	Logging_one->WriteLog("Call - motionCheckForNeopixel", extremedebug);
	int motionResult = Motionsensor_one.getValue();
	WS2812Stripe.SlowlyIncreaseOrDecreaseBrightness(DEFAULT_ALLLEDS, motionResult, DEFAULT_MAXVALUE);
}

void dhtCheck()
{
	Logging_one->WriteLog("Call - dhtCheck", extremedebug);
	bool motionResult = Motionsensor_one.getValue(Logging_one);
	float hum = DHTSensor_one.getHumValueOnlyIfChanged(Logging_one);
	float temp = DHTSensor_one.getTempValueOnlyIfChanged(Logging_one);

	if (motionResult == true)
	{
		WS2812Stripe.setHue(DEFAULT_ALLLEDS, ChangeColor.colorTemperaturChange(temp, hum, Logging_one), Logging_one);
	}
}

/*void setSignal()
{
	volatSignal = digitalRead(PIN_ENCODER_SW);
	if (volatSignal != volatSignalOld)
	{
		if (volatSignal)
		{
			interruptCount++;
			volatSignalSet = true;
		}
	}
	volatSignalOld = volatSignal;
}*/

//*******************************************************
//************************ SETUP ************************
//*******************************************************
void setup()
{
	Logging_one.writeLog(F("Setup Begin"), debug);
	WS2812Stripe.InitNeoPixel(DEFAULT_MAXVALUE, DEFAULT_MAXVALUE, Logging_one);
	encoder_one.setClickValue(0.5, Logging_one);
	WS2812Stripe.setStep(0.05);
	Logging_one.writeLog(F("Setup End"), debug);
	WS2812Stripe.setValues(-1,0, 0, 255, Logging_one);
	WS2812Stripe.InitExitRandomPulse(Logging_one);
	Logging_one.writeLog("Free Memory: " + String(freeMemory()), error);

//******************** Interrupts ***********************
/*
attachInterrupt
LOW Interrupt wird getriggert, wenn der Pin LOW ist,
CHANGE Interrupt wird getriggert, wenn der Pin den Wert ändert
RISING Interrupt wird getriggert, wenn der Pin von LOW auf HIGH wechselt,
FALLING Interrupt wird getriggert, wenn der Pin von HIGH auf LOW wechselt.
Die Due - , Zero - und MKR1000 - Boards erlauben zusätzlich :
HIGH Interrupt wird getriggert, wenn der Pin HIGH ist.*/

	//attachPinChangeInterrupt(digitalPinToInterrupt(PIN_ENCODER_SW), setSignal, CHANGE);
	//attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_SW), setSignal, CHANGE); // pressed
	//attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_CLK), setSignal, CHANGE); // pressed
	//attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_DT), setSignal, CHANGE); // pressed
}

//*******************************************************
//************************ LOOP *************************
//*******************************************************
void loop()
{
	// Alle 1 Millisekunden...
	if (millis() - startzeit_4 >= laufzeit_1)
	{
		startzeit_4 = millis();
		WS2812Stripe.colorshift(encoder_one.getEncoderValue(Logging_one), true, Logging_one);
	}

	if (millis() - startzeit_3 >= laufzeit_50)
	{
		startzeit_3 = millis();
		WS2812Stripe.randomPulse(Logging_one);
	}

	// Alle 100 Millisekunden...
	if (millis() - startzeit_1 >= laufzeit_100)
	{
		startzeit_1 = millis();
		motionCheckForLight();
	}

		// Alle 500 Millisekunden...
	if (millis() - startzeit_2 >= laufzeit_2k5)
	{
		startzeit_2 = millis();
		Logging_one.writeLog("Free Memory: " + String(freeMemory()), error);
	}

	// Alle 500 Millisekunden...
	/*if (millis() - startzeit_2 >= laufzeit_500)
	{
		startzeit_2 = millis();
		dhtCheck();
	}*/

	// Alle 20 Millisekunden...
	/*if (millis() - startzeit_3 >= laufzeit_250)
	{
		startzeit_3 = millis();
		if (!encoder_one.getSwitchValue(Logging_one))
		{
			WS2812Stripe.twinkleRandom(-1, false, Logging_one);
		}
		else
		{
			if (!WS2812Stripe.GetHue() == 0x00)
			{
				WS2812Stripe.setValues(-1, 0x00, 0x00, 0x00, Logging_one);
			}

		}
	}*/
}