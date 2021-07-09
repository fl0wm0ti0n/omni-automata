#ifndef _NEOPIXEL_h
#define _NEOPIXEL_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "constants.h"
#if (NodeMCUV3 == true)
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#endif

#include "actor.h"
#include "FastLED.h"
#include "logger.h"

class neopixel :
	public actor
{

private:

	// rainnbow variables
	int		rainbowCount_ = 0;
	float	ihue_ = 0;
	double	istep_ = 0.01;
	int		numstops_ = round(255 / numleds_);

	// LED properties
	int		saturation_ = 0;
	int		hue_ = 0;
	int		brightness_ = 0;
	int		numleds_ = 0;
	CRGB	ledsA_[NUM_LEDS_1];

	//FadeToTargetColor variables
	HSVHue	previousColor_;
	int		range_ = numleds_;
	int		blubb_ = 0;
	int		fromblubb_ = 0;
	HSVHue	colorium_ = {};
	String	color_;
	int		fade_hue_ = 0;
	int		fade_hue_prev_ = 0;
	int		lightcounter_ = 0;

	bool setAllLikeInput(int led, int hue, int saturation, int brightness);

public:
	neopixel(String n, int p, int numleds);
	virtual ~neopixel();
	bool setValues(int led, int hue, int sat, int val, logger &log);	// wird led NULL übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird einde LED geschalten.
	bool setSaturation(int led, int saturation, logger &log);
	bool setHue(int led, int hue, logger &log);
	bool setBrightness(int led, int brightness, logger &log);
	void fadeToTargetColor(int led, int hue, logger &log);		// Ändert die aktuellöe farbe zu einer zielfarbe
	CRGB* InitNeoPixel(int brightness, int saturation, logger &log);
	void SlowlyIncreaseOrDecreaseBrightness(int led, bool sensorResult, int maxBrightness, logger& log);
	void colorshift(int direction, bool sensorResult, logger &log);

	// Set Steps dont use full integers use range between 0.50 - 0.01
	int setStep(double step)
	{
		istep_ = step;
	}

	int GetHue()
	{
		return hue_;
	}
	int GetSaturation()
	{
		return saturation_;
	}

	int GetBrightness()
	{
		return brightness_;
	}

	int GetNumleds()
	{
		return numleds_;
	}
};
#endif