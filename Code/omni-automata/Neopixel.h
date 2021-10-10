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

protected:

	// LED properties
	CHSV	chsvleds_[NUM_LEDS_1]				= {  };
	//byte	a_saturation_[NUM_LEDS_1]			= { 0 };
	//byte	a_hue_[NUM_LEDS_1]					= { 0 };
	//byte	a_brightness_[NUM_LEDS_1]			= { 0 };
	byte	saturation_							= 0;
	byte	hue_								= 0;
	byte	brightness_							= 0;
	byte	numleds_							= 0;
	CRGB	crgbleds_[NUM_LEDS_1]				= { 0 };

	// rainnbow variables
	float	i_hue_ = 0;
	float	i_step_ = 0.01;
	byte	numstops_ = round(255 / numleds_);

	// FadeToTargetColor variables
	HSVHue	previous_hue_						= {};
	byte	range_								= numleds_;
	byte	to_huecount_						= 0;
	byte	from_huecount_						= 0;
	HSVHue	colorium_							= {};
	//char*	color_;
	byte	lightcounter_						= 0;

	// Functions
	void	setAllLikeInput						(short led);
	void	setAllLikeInputArray				(short led);

public:
	Neopixel(char n[], unsigned short p, unsigned short numleds);
	virtual ~Neopixel();

	/*common functions*/
	bool	fireEvent()						override;
	bool	setEvent(actor_event newevent)	override;
	
	bool	setValues							(short led, byte hue, byte sat, byte val);	// wird led -1 übergeben werden alle geschalten, wird eine bestimmte Zahl mitgegeben wird eine LED geschalten.
	bool	setSaturation						(short led, byte saturation);
	bool	setHue								(short led, byte hue);
	bool	setBrightness						(short led, byte brightness);
	void	fadeToTargetColor					(short led, byte hue);						// Ändert die aktuelle Farbe zu einer Zielfarbe
	CRGB*	InitNeoPixel						(byte brightness, byte saturation);
	void	SlowlyIncreaseOrDecreaseBrightness	(short led, bool sensorResult, byte maxBrightness);
	void	colorshift							(short direction, bool sensorResult);
	void	twinkleRandom						(short chosenColor, boolean OnlyOne);

	// Set Steps dont use full integers use range between 0.50 - 0.01
	void	setStep(float step)		{ i_step_ = step; }
	byte	GetHue()				{ return hue_; }
	byte	GetSaturation()			{ return saturation_; }
	byte	GetBrightness()			{ return brightness_; }
	byte	GetHue(short led)		{ return chsvleds_[led].hue; }
	byte	GetSaturation(short led){ return chsvleds_[led].saturation; }
	byte	GetBrightness(short led){ return chsvleds_[led].value; }
	CHSV*	GetChsvLeds()			{ return chsvleds_; }
	int		GetNumleds()			{ return numleds_; }

};
#endif