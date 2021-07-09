// @file           neopixel.cpp
// @author         flow@p0cki.net
// @date           09.2019
// @brief          neopixel Class


#include "constants.h"
#if (NodeMCUV3 == true)
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#endif

#include "neopixel.h"
#include "FastLED.h"


//Constructor
neopixel::neopixel(String name, int pin, int numleds)
	:actor(WS2812_act, name, pin)
{
	numleds_ = numleds;
	ledsA_[numleds];
}

//Destructor
neopixel::~neopixel()
{
}

// Initialisierung
// Der Pin muss in constants.h definiert werden
// Die Anzahl der Leds sollte in constants.h definiert werden.
CRGB* neopixel::InitNeoPixel(int brightness, int saturation, logger &log)
{
	log.writeLog("Setup WS2812...", debug);
	brightness_ = brightness;
	saturation_ = saturation;
	LEDS.setBrightness(0);
	LEDS.clear();
	LEDS.clearData();
	LEDS.setBrightness(brightness_);
	LEDS.setBrightness(saturation_);
	LEDS.addLeds<WS2812B, PIN_WS2812_1, GRB>(ledsA_, numleds_);
	//memset(ledsA_, 0, numleds_ * sizeof(struct CRGB));
	return ledsA_;
}

bool neopixel::setAllLikeInput(int led, int hue, int saturation, int brightness)
{
	if (led != -1)
	{
		ledsA_[led] = CHSV(hue_, saturation_, brightness_);
	}
	else
	{
		for (int element = 0;element <= numleds_; element++)
		{
			ledsA_[element] = CHSV(hue_, saturation_, brightness_);
		}
	}
	LEDS.show();
}

// Legt alle Werte fest
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
bool neopixel::setValues(int led, int hue, int saturation, int brightness, logger &log)
{
	log.writeLog("Call - neopixel - setValues", extremedebug);
	saturation_ = saturation;
	hue_ = hue;
	brightness_ = brightness;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Legt die Farbsättigung fest
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
bool neopixel::setSaturation(int led, int saturation, logger &log)
{
	log.writeLog("Call - neopixel - setSaturation", extremedebug);
	saturation_ = saturation;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Legt die Farbe fest
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
bool neopixel::setHue(int led, int hue, logger &log)
{
	log.writeLog("Call - neopixel - setHue", extremedebug);
	hue_ = hue;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Legt dide Helligkeit fest
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
bool neopixel::setBrightness(int led, int brightness, logger &log)
{
	log.writeLog("Call - neopixel - setBrightness", extremedebug);
	brightness_ = brightness;
	setAllLikeInput(led, hue_, saturation_, brightness_);
	return true;
}

// Helligkeit langsam erhöhen oder veringern - je nach dem ob der Input True oder False ist.
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
void neopixel::SlowlyIncreaseOrDecreaseBrightness(int led, bool sensorResult, int maxBrightness, logger& log)
{
	log.writeLog("Call - SlowlyIncreaseOrDecreaseValue", extremedebug);

	if (sensorResult)
	{
		if (lightcounter_ != maxBrightness)
		{
			if (lightcounter_ < maxBrightness)
			{
				lightcounter_++;
				log.writeLog("Value Up - " + String(lightcounter_), extremedebug);
			}
		}
	}
	else
	{
		if (lightcounter_ != 0)
		{
			if (lightcounter_ > 0)
			{
				lightcounter_--;
				log.writeLog("Value Down - " + String(lightcounter_), extremedebug);
			}
		}
	}
	setBrightness(led, lightcounter_, log);
}

// Farbänderung zu angegebenen Farbe
// wird led "-1" übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
void neopixel::fadeToTargetColor(int led, int hue, logger &log)
{
	log.writeLog("Call - fadeToTargetColor", extremedebug);

	if (hue != previousColor_)
	{
		if (fromblubb_ < blubb_)
		{
			for (int i = fromblubb_;i <= blubb_; i++)
			{
				log.writeLog("TColor - blubb++: " + String(i), extremedebug);
				for (int element = 0;element <= range_; element++)
				{
					//Logging_one.writeLog("TColor - show leds: " + String(element), extremedebug);
					ledsA_[element] = CHSV(i, 255, 255);
				}

			}
		}
		else
		{
			for (int i = fromblubb_;i >= blubb_; i--)
			{
				log.writeLog("TColor - blubb--: " + String(i), extremedebug);
				for (int element = 0;element <= range_; element++)
				{
					//Logging_one.writeLog("TColor - show leds: " + String(element), extremedebug);
					ledsA_[element] = CHSV(i, 255, 255);
				}
			}
		}
		fromblubb_ = blubb_;
		previousColor_ = colorium_;
	}
	setHue(led, lightcounter_, log);
}

void neopixel::colorshift(int direction, bool sensorResult, logger &log)
{
	if (sensorResult)
	{
		if (direction > 0)
		{
			log.writeLog("colorshift right", extremedebug);
			for (int i = 0;i < numleds_; i++)
			{
				ledsA_[i] = CHSV(i*numstops_ + ihue_, saturation_, brightness_);
				ihue_ += istep_;
				if (ihue_ >= 255)
				{
					ihue_ = 0;
				}
			}
		}
		if (direction < 0)
		{
			log.writeLog("colorshift left", extremedebug);
			for (int i = numleds_;i > 0; i--)
			{
				ledsA_[i] = CHSV(i*numstops_ + ihue_, saturation_, brightness_);
				ihue_ -= istep_;
				if (ihue_ <= 0)
				{
					ihue_ = 255;
				}
			}
		}
	}
	else
	{
		for (int i = 0;i < numleds_; i++)
		{
			ledsA_[i] = CHSV(0, 0, 0);
		}
	}
	LEDS.show();
}