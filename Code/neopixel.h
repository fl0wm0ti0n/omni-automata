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
	float	ihue_								= 0;
	float	istep_								= 0.01;
	byte		numstops_							= round(255 / numleds_);

	// LED properties
	byte	aSaturation_[NUM_LEDS_1]			= { 0 };
	byte	aHue_[NUM_LEDS_1]					= { 0 };
	byte	aBrightness_[NUM_LEDS_1]			= { 0 };
	byte	saturation_							= 0;
	byte	hue_								= 0;
	byte	brightness_							= 0;
	byte	numleds_							= 0;
	CRGB	ledsA_[NUM_LEDS_1]					= { 0 };

	//FadeToTargetColor variables
	HSVHue	previousColor_						= {};
	byte	range_								= numleds_;
	byte	blubb_								= 0;
	byte	fromblubb_							= 0;
	HSVHue	colorium_							= {};
	String	color_								= "";
	byte	lightcounter_						= 0;

	//RandomPulse variables
	byte	aDunkel_	[NUM_LEDS_1 + 1][3]		= {{0}};
	byte	aHell_		[NUM_LEDS_1 + 1][3]		= {{0}};
	byte	aAbdunkeln_	[NUM_LEDS_1 + 1][2]		= {{0}};
	byte	aAufhellen_	[NUM_LEDS_1 + 1][2]		= {{0}};

	boolean	bErsterAufrufVonRP_					= true;
	byte	iMaxDunkelZyklen_					= DEFAULT_NEOPIXEL_MaxDunkelZyklen;
	byte	iMaxHellZyklen_						= DEFAULT_NEOPIXEL_MaxHellZyklen;
	byte	iMaxHelligkeit_						= DEFAULT_NEOPIXEL_MaxHelligkeit;
	byte	iMinHelligkeit_						= DEFAULT_NEOPIXEL_MinHelligkeit;
	byte	iAnteilLedsZumAufhellen_			= DEFAULT_NEOPIXEL_AnteilLedsZumAufhellen;
	byte	iAnteilLedsZumAbdunkeln_			= DEFAULT_NEOPIXEL_AnteilLedsZumAbdunkeln;
	byte	iInkrement_							= DEFAULT_NEOPIXEL_Inkrement;
	byte	iDekrement_							= DEFAULT_NEOPIXEL_Dekrement;
	byte	iTiming_							= DEFAULT_NEOPIXEL_Timing;
	unsigned long istartzeit_					= 0;

	void setAllLikeInput								(short led);
	void setAllLikeInputArray							(short led);
	void RP_SetzeInitialWerteInArrays					(logger &log);
	void RP_ProzessDunkel								(logger &log);
	void RP_ProzessAufhellen							(logger &log);
	void RP_ProzessHell									(logger &log);
	void RP_ProzessAbdunkeln							(logger &log);
	bool RP_CheckObMaxHellOderDunkelZyklusErreicht		(byte zeile, String helldunkel);
	bool RP_CheckObMaxHellOderDunkelWertErreicht		(byte zeile, String aufhellabdunkel);
	void RP_WaehleLedAnteilZumHellOderDunkelSchalten	(String helldunkel, logger &log);
	bool RP_CheckObErsterAufrufVonRandomPulse();
	bool RP_CheckTimeMoment();
	void RP_InDekrementiereLEDArrays					(logger &log);
	byte RP_Fibanagi(byte before, byte last);
	void RP_SetzeBerechneteLichtwerte					(logger &log);

public:
	neopixel								(String n, byte p, byte numleds);
	virtual ~neopixel						();
	bool setValues							(short led, byte hue, byte sat, byte val, logger &log);	// wird led NULL übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird einde LED geschalten.
	bool setSaturation						(short led, byte saturation, logger &log);
	bool setHue								(short led, byte hue, logger &log);
	bool setBrightness						(short led, byte brightness, logger &log);
	void fadeToTargetColor					(short led, byte hue, logger &log);		// Ändert die aktuelle Farbe zu einer Zielfarbe
	CRGB* InitNeoPixel						(byte brightness, byte saturation, logger &log);
	void SlowlyIncreaseOrDecreaseBrightness	(short led, bool sensorResult, byte maxBrightness, logger& log);
	void colorshift							(short direction, bool sensorResult, logger &log);
	void twinkleRandom						(short chosenColor, boolean OnlyOne, logger &log);
	void randomPulse						(logger &log);
	void InitExitRandomPulse				(logger &log);

	void setRP_MaxHellDunkelZyklen(byte Hell, byte Dunkel)
	{
		iMaxHellZyklen_ = Hell;
		iMaxDunkelZyklen_ = Dunkel;
	}

	void setRP_MaxMinHelligkeit(byte Max, byte Min)
	{
		byte iMaxHelligkeit_ = 0;
		byte iMinHelligkeit_ = 0;
	}

	void setRP_AnteilLedsZumAufhellen(byte Anteil)
	{
		iAnteilLedsZumAufhellen_ = Anteil;
	}

	void setRP_InDeKrement(byte In, byte De)
	{
		iInkrement_ = In;
		iDekrement_ = De;
	}

	// Set Steps dont use full integers use range between 0.50 - 0.01
	void setStep(float step)
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

	byte* GetBrightnessArray()
	{
		return aBrightness_;
	}

	byte* GetHueArray()
	{
		return aHue_;
	}

	byte* GetSaturationArray()
	{
		return aSaturation_;
	}

	int GetNumleds()
	{
		return numleds_;
	}


};
#endif