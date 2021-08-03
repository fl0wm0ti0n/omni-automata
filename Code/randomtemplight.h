#ifndef _RANDOMTEMPLIGHT_h
#define _RANDOMTEMPLIGHT_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "constants.h"
#if (NodeMCUV3 == true)
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#endif

// ACHTUNG: Alle Arduino Bibliotheken welche in anderen Klassen verwendet werden müssen zumindest zusätzlich auch hier included werden. Obwohl diese hier ausgegraut werden.
#include "FastLED.h"
#include "logger.h"

float ihue = 0;
float istep = 0.01;
int idelay = 0;
int bright = 1;
int numstops = round(255 / NUM_LEDS_1);
CRGB ledsA[NUM_LEDS_1];
HSVHue previousColor;

inline CRGB* neopixelobjekt(int brightness)
{
#ifdef DEBUG
	logger* logger_g_;
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
	static const char* const buffer PROGMEM = "Setup WS2812B...";
	logger_g_->LnWriteLog(buffer, debug);
#endif
	LEDS.setBrightness(brightness);
	LEDS.addLeds<WS2812B, PIN_WS2812_1, GRB>(ledsA, NUM_LEDS_1);
	//memset(ledsA, 0, NUM_LEDS_1 * sizeof(struct CRGB));
	return ledsA;
}

inline void colorshift(int onoff)
{
	switch (onoff)
	{
	case 1:

		for (int i = 0;i < NUM_LEDS_1; i++)
		{
			ledsA[i] = CHSV(i*numstops + ihue, 255, 255);
			ihue += istep;
			if (ihue >= 255)
			{
				ihue = 0;
			}
		}
		break;
	default:
		for (int i = 0;i < NUM_LEDS_1; i++)
		{
			ledsA[i] = CHSV(0, 0, 0);
		}
		break;
	}
	LEDS.show();
	delay(idelay);
}

inline void rainbow_effect(int onoff)
{
	switch (onoff)
	{
	case 1:
		//Serial.println("WS on");
		for (int i = 0;i < NUM_LEDS_1; i++)
		{
			ledsA[i] = CHSV(i*numstops + ihue, 255, 255);
			ihue += istep;
			if (ihue >= 255)
			{
				ihue = 0;
			}
		}
		break;
	default:
		//Serial.println("WS off");
		for (int i = 0;i < NUM_LEDS_1; i++)
		{
			ledsA[i] = CHSV(0, 0, 0);
		}
		break;
	}
	LEDS.show();
	delay(idelay);
}

inline void LED_TempColor2(String color)
{
	int rnd[NUM_LEDS_1];
	int rndbright[NUM_LEDS_1];
	int quarterRange = NUM_LEDS_1 / 4;
	int ledsonpeak[NUM_LEDS_1 / 4];
	int ledsonlow[NUM_LEDS_1 / 4];
	int ledbright[NUM_LEDS_1 / 4];
	HSVHue colorium = {};

#ifdef DEBUG
	logger* logger_g_;
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
	static const char* const buffer PROGMEM = "Range= ";
	logger_g_->LnWriteLog(buffer, debug);
	logger_g_->WriteLog(quarterRange, debug);
#endif

	if (color == "arctic") { colorium = HUE_AQUA; }
	else if (color == "blue") { colorium = HUE_BLUE; }
	else if (color == "green") { colorium = HUE_GREEN; }
	else if (color == "yellow") { colorium = HUE_YELLOW; }
	else if (color == "orange") { colorium = HUE_ORANGE; }
	else if (color == "red") { colorium = HUE_RED; }

	// Randomwert für genutze Leds erzeugen
	for (int j = 0;j <= quarterRange; j++)
	{
		rnd[j] = rand() % NUM_LEDS_1;

		for (int i = 0;i <= quarterRange; i++)
		{
			if (rnd[j] == rnd[i])
			{
				rnd[j] = rand() % NUM_LEDS_1;
			}
		}
#ifdef DEBUG
		logger* logger_g_;
		static char* const buffer PROGMEM = "Logging1";
		logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
		static const char* const buffer PROGMEM = "Random= ";
		logger_g_->LnWriteLog(buffer, debug);
		logger_g_->WriteLog(rnd[j], debug);
#endif
	}

	// Randomwert für Start-Helligkeit erzeugen
	for (int j = 0;j <= quarterRange; j++)
	{
		rndbright[j] = rand() % 255;
#ifdef DEBUG
		logger* logger_g_;
		static char* const buffer PROGMEM = "Logging1";
		logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
		static const char* const buffer PROGMEM = "RandomBright= ";
		logger_g_->LnWriteLog(buffer, debug);
		logger_g_->WriteLog(rndbright[j], debug);
#endif
	}

	// Schleife für helligkeit Up
	for (int i = 0;i <= 255; i++)
	{
#ifdef DEBUG
		logger* logger_g_;
		static char* const buffer PROGMEM = "Logging1";
		logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
		static const char* const buffer PROGMEM = "brightnessUpLoop= ";
		logger_g_->LnWriteLog(buffer, debug);
		logger_g_->WriteLog(i, debug);
#endif
		for (int j = 0;j <= quarterRange; j++)
		{
			if (i <= rndbright[j])
			{
				ledsA[rnd[j]] = CHSV(colorium, 255, i);
			}

			if (i >= rndbright[j])
			{
				ledsA[rnd[j]] = CHSV(colorium, 255, rndbright[j] + 1);
				rndbright[j] = rndbright[j] + 1;
			}

			/*if (rndbright[j] + 1 <= 255)
			{
				ledsA_[rnd[j]] = CHSV(colorium_, 255, rndbright[j] + 1);

			}*/

			if (ledsonpeak[j] = rnd[j])
			{
				ledsA[rnd[j]] = CHSV(colorium, 255, i);
			}

			if (ledsonlow[j] = rnd[j])
			{

			}

			if (ledbright[j] = 255)
			{
				ledsonpeak[j] = rnd[j];
			}

			if (ledbright[j] = 0)
			{
				ledsonlow[j] = rnd[j];
			}

		}

		LEDS.show();
		delay(3);
	}

	delay(1);

	// Schleife für helligkeit Down
	for (int x = 255;x >= 0; x--)
	{
#ifdef DEBUG
		logger* logger_g_;
		static char* const buffer PROGMEM = "Logging1";
		logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
		static const char* const buffer PROGMEM = "brightnessDownLoop= ";
		logger_g_->LnWriteLog(buffer, debug);
		logger_g_->WriteLog(x, debug);
#endif
		for (int j = 0;j <= quarterRange; j++)
		{
			if (rndbright[j] - 1 >= 0)
			{
				ledsA[rnd[j]] = CHSV(colorium, 255, rndbright[j] - 1);
				rndbright[j] = rndbright[j] - 1;
			}
		}

		LEDS.show();
		delay(3);
	}
}

inline void LED_TempColor3(String color, logger &log)
{
	int rndled;
	int number = NUM_LEDS_1 / 2;
	int range = NUM_LEDS_1;
	HSVHue colorium = {};

	if (color == "arctic") { colorium = HUE_AQUA; }
	else if (color == "blue") { colorium = HUE_BLUE; }
	else if (color == "green") { colorium = HUE_GREEN; }
	else if (color == "yellow") { colorium = HUE_YELLOW; }
	else if (color == "orange") { colorium = HUE_ORANGE; }
	else if (color == "red") { colorium = HUE_RED; }

	for (int j = 0;j <= number; j++)
	{
		rndled = rand() % range;

		for (int i = 0;i <= 255; i++)
		{
			ledsA[rndled] = CHSV(colorium, 255, i);
			LEDS.show();
			delay(3);
		}

		rndled = rand() % range;

		for (int x = 255;x >= 0; x--)
		{
			ledsA[rndled] = CHSV(colorium, 255, x);

			LEDS.show();
			delay(3);
		}
	}
}

inline void LED_TempColor4(String color, logger &log)
{
	int rndledArray[NUM_LEDS_1];
	int led[NUM_LEDS_1];
	bool startswitch = true;
	int halfrange = NUM_LEDS_1 / 2;
	int range = NUM_LEDS_1;
	HSVHue colorium = {};

	int rndstart[NUM_LEDS_1];
	int lightupleds[NUM_LEDS_1];
	int lightoffleds[NUM_LEDS_1];

	if (color == "arctic") { colorium = HUE_AQUA; }
	else if (color == "blue") { colorium = HUE_BLUE; }
	else if (color == "green") { colorium = HUE_GREEN; }
	else if (color == "yellow") { colorium = HUE_YELLOW; }
	else if (color == "orange") { colorium = HUE_ORANGE; }
	else if (color == "red") { colorium = HUE_RED; }

#ifdef DEBUG
	logger* logger_g_;
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
	static const char* const buffer PROGMEM = "WS2812_FadeToTargetColor";
	logger_g_->LnWriteLog(buffer, debug);
#endif

	while (true)
	{

		if (startswitch == true)
		{

			for (int i = 0;i <= range; i++)
			{
#ifdef DEBUG
				logger* logger_g_;
				static char* const buffer PROGMEM = "Logging1";
				logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
				static const char* const buffer PROGMEM = "Init RND and Arrays";
				logger_g_->LnWriteLog(buffer, debug);
#endif
				
				rndstart[i] = rand() % 255;
				rndledArray[i] = i;
				lightupleds[i] = NULL;
				lightoffleds[i] = NULL;
			}
		}

		if (startswitch == true)
		{
			for (int j = 0;j <= range; j++)
			{
#ifdef DEBUG
				logger* logger_g_;
				static char* const buffer PROGMEM = "Logging1";
				logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
				static const char* const buffer PROGMEM = "Init lightupleds";
				logger_g_->LnWriteLog(buffer, debug);
#endif
				for (int i = 0;i <= 255; i++)
				{
					if (i == rndstart[j])
					{
						lightupleds[j] = rndledArray[j];
					}

					startswitch = false;
				}
			}
		}

		/*for (int j = 0;j <= range; j++)
		{
			for (int i = 0;i <= 255; i++)
			{
				if (i == rndstart[j])
				{
					lightupleds[j] = rndled[j];
				}

				delay(3);
			}
		}*/

		for (int blubb : lightupleds)
		{
#ifdef DEBUG
			logger* logger_g_;
			static char* const buffer PROGMEM = "Logging1";
			logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
			static const char* const buffer PROGMEM = "lightupleds loop = ";
			logger_g_->LnWriteLog(buffer, debug);
			logger_g_->WriteLog(lightupleds[blubb], debug);
#endif

			if (lightupleds[blubb] != NULL)
			{
				if (rndstart[blubb] < 255)
				{
					//lightupleds[blubb] = lightupleds[blubb] + 1;
					rndstart[blubb] = rndstart[blubb] + 1;
#ifdef DEBUG
					logger* logger_g_;
					static char* const buffer PROGMEM = "Logging1";
					logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
					static const char* const buffer PROGMEM = "rndstart = ";
					logger_g_->LnWriteLog(buffer, debug);
					logger_g_->WriteLog(rndstart[blubb], debug);
#endif
				}
				else
				{
					lightoffleds[blubb] = lightupleds[blubb];
					lightupleds[blubb] = NULL;
				}
			}
		}

		for (int blubb : lightoffleds)
		{
#ifdef DEBUG
			logger* logger_g_;
			static char* const buffer PROGMEM = "Logging1";
			logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
			static const char* const buffer PROGMEM = "lightoffleds loop = ";
			logger_g_->LnWriteLog(buffer, debug);
			logger_g_->WriteLog(lightoffleds[blubb], debug);
#endif

			if (lightoffleds[blubb] != NULL)
			{
				if (rndstart[blubb] > 0)
				{
					//lightoffleds[blubb] = lightupleds[blubb] + 1;
					rndstart[blubb] = rndstart[blubb] - 1;
#ifdef DEBUG
					logger* logger_g_;
					static char* const buffer PROGMEM = "Logging1";
					logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
					static const char* const buffer PROGMEM = "rndstart = ";
					logger_g_->LnWriteLog(buffer, debug);
					logger_g_->WriteLog(rndstart[blubb], debug);
#endif
				}
				else
				{
					lightupleds[blubb] = lightoffleds[blubb];
					lightoffleds[blubb] = NULL;
				}
			}
		}

		for (int blubb : rndstart)
		{
#ifdef DEBUG
			logger* logger_g_;
			static char* const buffer PROGMEM = "Logging1";
			logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
			static const char* const buffer PROGMEM = "show LEDS loop";
			logger_g_->LnWriteLog(buffer, debug);
			logger_g_->WriteLog(rndstart[blubb], debug);
#endif

			ledsA[blubb] = CHSV(colorium, 255, rndstart[blubb]);
			LEDS.show();
		}
		delay(10);
	}
}

// Langsamer übergang von einer zu nächsten farbe
inline void WS2812_FadeToTargetColor(float temp, float hum, logger &log)
{
#ifdef DEBUG
	logger* logger_g_;
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
	static const char* const buffer PROGMEM = "Call - WS2812_FadeToTargetColor";
	logger_g_->LnWriteLog(buffer, debug);
#endif

	int range = NUM_LEDS_1;
	int blubb = 0;
	int fromblubb = 0;
	HSVHue colorium = {};
	String color;

	// In decisions verschieben:
	if (			  temp	<= 20 && hum <= 50)	{ colorium = HUE_AQUA; blubb = 128; }
	if (temp >	20 && temp	<= 23 && hum <= 50) { colorium = HUE_BLUE;  blubb = 160; }
	if (temp >	23 && temp	<= 25 && hum >	55)	{ colorium = HUE_GREEN;  blubb = 96; }
	if (temp >	25 && temp	<= 27 && hum >= 60) { colorium = HUE_YELLOW; blubb = 64; }
	if (temp >	27 && temp	<= 30 && hum >= 70) { colorium = HUE_ORANGE; blubb = 32; }
	if (temp >	30				  && hum >= 80) { colorium = HUE_RED; blubb = 0; }

#ifdef DEBUG
	logger* logger_g_;
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
	static const char* const buffer PROGMEM = "Set color: ";
	logger_g_->LnWriteLog(buffer, debug);
	logger_g_->WriteLog(colorium, debug);
#endif
	
	// Entfernen und von neopixels nutzen
	if (colorium != previousColor)
	{
		if (fromblubb < blubb)
		{
			for (int i = fromblubb;i <= blubb; i++)
			{
#ifdef DEBUG
				logger* logger_g_;
				static char* const buffer PROGMEM = "Logging1";
				logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
				static const char* const buffer PROGMEM = "TColor - blubb++: ";
				logger_g_->LnWriteLog(buffer, debug);
				logger_g_->WriteLog(i, debug);
#endif
				for (int element = 0;element <= range; element++)
				{
					//log.writeLog("TColor - show leds: " + String(element), extremedebug);
					ledsA[element] = CHSV(i, 255, 255);
					delay(5);
				}
				LEDS.show();
			}
		}
		else
		{
			for (int i = fromblubb;i >= blubb; i--)
			{
#ifdef DEBUG
				logger* logger_g_;
				static char* const buffer PROGMEM = "Logging1";
				logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
				static const char* const buffer PROGMEM = "TColor - blubb--: ";
				logger_g_->LnWriteLog(buffer, debug);
				logger_g_->WriteLog(i, debug);
#endif
				for (int element = 0;element <= range; element++)
				{
					//log.writeLog("TColor - show leds: " + String(element), extremedebug);
					ledsA[element] = CHSV(i, 255, 255);
					delay(5);
				}
				LEDS.show();
			}
		}
		fromblubb = blubb;
		previousColor = colorium;
	}
}
#endif