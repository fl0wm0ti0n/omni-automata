// @file           Neopixel_RandomPulse.h
// @author         flow@p0cki.net
// @date           09.2021
// @brief          Neopixel Child Class

#ifndef _NEOPIXEL_RANDOMPULSE_h
#define _NEOPIXEL_RANDOMPULSE_h

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

class Neopixel_RandomPulse : public Neopixel
{
private:
	//RandomPulse variables
	byte			dunkel_[NUM_LEDS_1 + 1][3] = { {0} };
	byte			hell_[NUM_LEDS_1 + 1][3] = { {0} };
	byte			abdunkeln_[NUM_LEDS_1 + 1][2] = { {0} };
	byte			aufhellen_[NUM_LEDS_1 + 1][2] = { {0} };

	bool			erster_aufruf_von_rp_ = true;
	byte			max_dunkel_zyklen_ = DEFAULT_NEOPIXEL_MaxDunkelZyklen;
	byte			max_hell_zyklen_ = DEFAULT_NEOPIXEL_MaxHellZyklen;
	byte			max_helligkeit_ = DEFAULT_NEOPIXEL_MaxHelligkeit;
	byte			min_helligkeit_ = DEFAULT_NEOPIXEL_MinHelligkeit;
	byte			anteil_leds_zum_aufhellen_ = DEFAULT_NEOPIXEL_AnteilLedsZumAufhellen;
	byte			anteil_leds_zum_abdunkeln_ = DEFAULT_NEOPIXEL_AnteilLedsZumAbdunkeln;
	byte			inkrement_ = DEFAULT_NEOPIXEL_Inkrement;
	byte			dekrement_ = DEFAULT_NEOPIXEL_Dekrement;
	byte			timing_ = DEFAULT_NEOPIXEL_Timing;
	unsigned long	startzeit_ = 0;
	
	void RP_SetzeInitialWerteInArrays();
	void RP_ProzessDunkel();
	void RP_ProzessAufhellen();
	void RP_ProzessHell();
	void RP_ProzessAbdunkeln();
	bool RP_CheckObMaxHellOderDunkelZyklusErreicht(byte zeile, String helldunkel);
	bool RP_CheckObMaxHellOderDunkelWertErreicht(byte zeile, String aufhellabdunkel);
	void RP_WaehleLedAnteilZumHellOderDunkelSchalten(String helldunkel);
	bool RP_CheckObErsterAufrufVonRandomPulse();
	bool RP_CheckTimeMoment();
	void RP_InDekrementiereLEDArrays();
	byte RP_Fibanagi(byte before, byte last);
	void RP_SetzeBerechneteLichtwerte();


	
public:
	Neopixel_RandomPulse(char n[], unsigned short p, byte numleds);
	~Neopixel_RandomPulse();

	void randomPulse();
	void InitExitRandomPulse();
	void setRP_MaxHellDunkelZyklen(byte Hell, byte Dunkel)	{ max_hell_zyklen_ = Hell; max_dunkel_zyklen_ = Dunkel; }
	void setRP_MaxMinHelligkeit(byte Max, byte Min)			{ byte iMaxHelligkeit_ = 0; byte iMinHelligkeit_ = 0; }
	void setRP_AnteilLedsZumAufhellen(byte Anteil)			{ anteil_leds_zum_aufhellen_ = Anteil; }
	void setRP_InDeKrement(byte In, byte De)				{ inkrement_ = In; dekrement_ = De; }

};
#endif