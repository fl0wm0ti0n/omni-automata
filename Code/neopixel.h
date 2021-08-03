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

#include "Actor.h"
#include "FastLED.h"
#include "logger.h"

class Neopixel : public Actor
{

private:

	// rainnbow variables
	float	i_hue_								= 0;
	float	i_step_								= 0.01;
	byte	numstops_							= round(255 / numleds_);

	// LED properties
	byte	a_saturation_[NUM_LEDS_1]			= { 0 };
	byte	a_hue_[NUM_LEDS_1]					= { 0 };
	byte	a_brightness_[NUM_LEDS_1]			= { 0 };
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
	char*	color_;
	byte	lightcounter_						= 0;

	//RandomPulse variables
	byte	dunkel_		[NUM_LEDS_1 + 1][3]		= {{0}};
	byte	hell_		[NUM_LEDS_1 + 1][3]		= {{0}};
	byte	abdunkeln_	[NUM_LEDS_1 + 1][2]		= {{0}};
	byte	aufhellen_	[NUM_LEDS_1 + 1][2]		= {{0}};

	bool	erster_aufruf_von_rp_				= true;
	byte	max_dunkel_zyklen_					= DEFAULT_NEOPIXEL_MaxDunkelZyklen;
	byte	max_hell_zyklen_					= DEFAULT_NEOPIXEL_MaxHellZyklen;
	byte	max_helligkeit_						= DEFAULT_NEOPIXEL_MaxHelligkeit;
	byte	min_helligkeit_						= DEFAULT_NEOPIXEL_MinHelligkeit;
	byte	anteil_leds_zum_aufhellen_			= DEFAULT_NEOPIXEL_AnteilLedsZumAufhellen;
	byte	anteil_leds_zum_abdunkeln_			= DEFAULT_NEOPIXEL_AnteilLedsZumAbdunkeln;
	byte	inkrement_							= DEFAULT_NEOPIXEL_Inkrement;
	byte	dekrement_							= DEFAULT_NEOPIXEL_Dekrement;
	byte	timing_								= DEFAULT_NEOPIXEL_Timing;
	unsigned long startzeit_					= 0;

	void setAllLikeInput								(short led);
	void setAllLikeInputArray							(short led);
	void RP_SetzeInitialWerteInArrays					();
	void RP_ProzessDunkel								();
	void RP_ProzessAufhellen							();
	void RP_ProzessHell									();
	void RP_ProzessAbdunkeln							();
	bool RP_CheckObMaxHellOderDunkelZyklusErreicht		(byte zeile, String helldunkel);
	bool RP_CheckObMaxHellOderDunkelWertErreicht		(byte zeile, String aufhellabdunkel);
	void RP_WaehleLedAnteilZumHellOderDunkelSchalten	(String helldunkel);
	bool RP_CheckObErsterAufrufVonRandomPulse			();
	bool RP_CheckTimeMoment								();
	void RP_InDekrementiereLEDArrays					();
	byte RP_Fibanagi									(byte before, byte last);
	void RP_SetzeBerechneteLichtwerte					();

public:
	Neopixel								(char n[], byte p, byte numleds);
	virtual ~Neopixel						();
	bool setValues							(short led, byte hue, byte sat, byte val);	// wird led NULL übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird einde LED geschalten.
	bool setSaturation						(short led, byte saturation);
	bool setHue								(short led, byte hue);
	bool setBrightness						(short led, byte brightness);
	void fadeToTargetColor					(short led, byte hue);		// Ändert die aktuelle Farbe zu einer Zielfarbe
	CRGB* InitNeoPixel						(byte brightness, byte saturation);
	void SlowlyIncreaseOrDecreaseBrightness	(short led, bool sensorResult, byte maxBrightness);
	void colorshift							(short direction, bool sensorResult);
	void twinkleRandom						(short chosenColor, boolean OnlyOne);
	void randomPulse						();
	void InitExitRandomPulse				();

	void setRP_MaxHellDunkelZyklen(byte Hell, byte Dunkel)
	{
		max_hell_zyklen_ = Hell;
		max_dunkel_zyklen_ = Dunkel;
	}

	void setRP_MaxMinHelligkeit(byte Max, byte Min)
	{
		byte iMaxHelligkeit_ = 0;
		byte iMinHelligkeit_ = 0;
	}

	void setRP_AnteilLedsZumAufhellen(byte Anteil)
	{
		anteil_leds_zum_aufhellen_ = Anteil;
	}

	void setRP_InDeKrement(byte In, byte De)
	{
		inkrement_ = In;
		dekrement_ = De;
	}

	// Set Steps dont use full integers use range between 0.50 - 0.01
	void setStep(float step)
	{
		i_step_ = step;
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
		return a_brightness_;
	}

	byte* GetHueArray()
	{
		return a_hue_;
	}

	byte* GetSaturationArray()
	{
		return a_saturation_;
	}

	int GetNumleds()
	{
		return numleds_;
	}


};
#endif