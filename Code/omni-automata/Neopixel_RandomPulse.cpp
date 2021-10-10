// @file           Neopixel_RandomPulse.cpp
// @author         flow@p0cki.net
// @date           09.2021
// @brief          Neopixel Child Class

#include "Neopixel_RandomPulse.h"

//Constructor
Neopixel_RandomPulse::Neopixel_RandomPulse(char n[], unsigned short p, byte numleds)
	:Neopixel(n, p, numleds)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
	numleds_ = numleds;
	crgbleds_[numleds];
}

//Destructor
Neopixel_RandomPulse::~Neopixel_RandomPulse()
{
}

// Nötig damit der Zustand des Effekts randomPulse resettiert wird. Danach ist der Zustand von randomPulse gleichbedeutend als wäre randomPulse noch nie aufgerufen worden.
void Neopixel_RandomPulse::InitExitRandomPulse()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - RP InitExitRandomPulse";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	erster_aufruf_von_rp_ = true;

	for (byte i = 0; i <= numleds_; i++) {
		dunkel_[i][0] = 0;
		dunkel_[i][1] = 0;
		dunkel_[i][2] = min_helligkeit_;
		hell_[i][0] = 0;
		hell_[i][1] = 0;
		hell_[i][2] = max_helligkeit_;
		aufhellen_[i][0] = 0;
		aufhellen_[i][1] = 0;
		abdunkeln_[i][0] = 0;
		abdunkeln_[i][1] = 0;
	}
}

// Prüft anhand der in den randomPulse Arrays hinterlegten schaltern (1/0) ob randomPulse zum ersten mal aufgerufen wurde. Ist nur ein einzelner Schalter auf 1 wurde RP bereits aufgerufen.
bool Neopixel_RandomPulse::RP_CheckObErsterAufrufVonRandomPulse()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - RP_1stRandomPulseCall";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	byte checkSchalter = 0;

	if (erster_aufruf_von_rp_)
	{
		return true;
	}
	for (byte i = 0; i <= numleds_; i++) {
		checkSchalter = dunkel_[i][0];
		checkSchalter = hell_[i][0];
		checkSchalter = abdunkeln_[i][0];
		checkSchalter = aufhellen_[i][0];

		if (checkSchalter == 1)
		{
			return false;
		}
	}
	return true;
}

bool Neopixel_RandomPulse::RP_CheckTimeMoment()
{
	int timing = max_helligkeit_ - min_helligkeit_ / timing_ * 1000;

	if (millis() - startzeit_ >= timing)
	{
		startzeit_ = millis();
		return true;
	}
	return false;
}

// Es werden die aktuellen Lichtwerte ausgelesen und in die Arrays für randomPulse geladen. 
// Dies gewährleistet einen flüssigen Übergang beim wechsel zum Effekt randomPulse
void Neopixel_RandomPulse::RP_SetzeInitialWerteInArrays()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - RP Setze Initial Werte";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	for (byte i = 0; i <= numleds_; i++) {
		if (chsvleds_[i].value <= min_helligkeit_) // Leds welche dünkler sind als min_helligkeit_ werden im nächsten Zyklus in aufhellen_ gelegt und damit heller geschalten.
		{
			dunkel_[i][0] = 1;
			dunkel_[i][1] = 0;
			dunkel_[i][2] = chsvleds_[i].value;
		}

		if (chsvleds_[i].value >= max_helligkeit_) // Leds welche heller sind als max_helligkeit_ werden im nächsten Zyklus in abdunkeln_ gelegt und damit dünkler geschalten.
		{
			hell_[i][0] = 1;
			hell_[i][1] = 0;
			hell_[i][2] = chsvleds_[i].value;
		}

		if (chsvleds_[i].value > min_helligkeit_ && chsvleds_[i].value < max_helligkeit_) // Leds welche zwischen min_helligkeit_ und max_helligkeit_ liegen werden im nächsten Zyklus zufällig heller oder dünkler geschalten.
		{
			byte rand = random8(0, 1);
			if (rand == 1)
			{
				aufhellen_[i][0] = 1;
				aufhellen_[i][1] = chsvleds_[i].value;
			}
			else
			{
				abdunkeln_[i][0] = 1;
				abdunkeln_[i][1] = chsvleds_[i].value;
			}
		}
	}
}

// Stellt das ene eines Zykluses dar und
void Neopixel_RandomPulse::RP_InDekrementiereLEDArrays()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - RP InDekrementiere";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	for (byte i = 0; i <= numleds_; i++) {
		if (hell_[i][0] == 1)
		{
#ifdef DEBUG
			if (logger_g_->GetLogLevel() >= debug)
			{
				static const char* const buffer PROGMEM = "hell_: ";
				logger_g_->LnWriteLog(buffer, debug);
				logger_g_->WriteLog(hell_[i][1], debug);
			}
#endif
			hell_[i][1] = hell_[i][1] + 1;
		}
		if (dunkel_[i][0] == 1)
		{
#ifdef DEBUG
			if (logger_g_->GetLogLevel() >= debug)
			{
				static const char* const buffer PROGMEM = "dunkel_: ";
				logger_g_->LnWriteLog(buffer, debug);
				logger_g_->WriteLog(dunkel_[i][1], debug);
			}
#endif
			dunkel_[i][1] = dunkel_[i][1] + 1;
		}
		if (aufhellen_[i][0] == 1)
		{
#ifdef DEBUG
			if (logger_g_->GetLogLevel() >= debug)
			{
				static const char* const buffer PROGMEM = "aufhellen_: ";
				logger_g_->LnWriteLog(buffer, debug);
				logger_g_->WriteLog(aufhellen_[i][1], debug);
			}
#endif
			aufhellen_[i][1] = aufhellen_[i][1] + DEFAULT_NEOPIXEL_Inkrement;
		}
		if (abdunkeln_[i][0] == 1)
		{
#ifdef DEBUG
			if (logger_g_->GetLogLevel() >= debug)
			{
				static const char* const buffer PROGMEM = "abdunkeln_: ";
				logger_g_->LnWriteLog(buffer, debug);
				logger_g_->WriteLog(abdunkeln_[i][1], debug);
			}
#endif
			abdunkeln_[i][1] = abdunkeln_[i][1] - DEFAULT_NEOPIXEL_Dekrement;
		}

	}
}

byte Neopixel_RandomPulse::RP_Fibanagi(byte before, byte last)
{
	return before + last;
}

// Stellt das ene eines Zykluses dar und
void Neopixel_RandomPulse::RP_SetzeBerechneteLichtwerte()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - RP Setze Lichtwerte";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	for (byte i = 0; i <= numleds_; i++) {
		if (hell_[i][0] == 1)
		{
			chsvleds_[i].value = hell_[i][2];
		}
		if (dunkel_[i][0] == 1)
		{
			chsvleds_[i].value = dunkel_[i][2];
		}
		if (aufhellen_[i][0] == 1)
		{
			chsvleds_[i].value = aufhellen_[i][1];
		}
		if (abdunkeln_[i][0] == 1)
		{
			chsvleds_[i].value = abdunkeln_[i][1];
		}
	}
}

void Neopixel_RandomPulse::RP_ProzessDunkel()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - RP ProzessDunkel";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	for (byte i = 0; i <= numleds_; i++) {

		if (RP_CheckObMaxHellOderDunkelZyklusErreicht(i, "dunkel")) // Leds welche max_hell_zyklen_ Zyklen Hell waren werden in abdunkeln_ gelegt und damit dünkler geschalten.
		{
			dunkel_[i][0] = 0;
			dunkel_[i][1] = 0;
			dunkel_[i][2] = min_helligkeit_;
			aufhellen_[i][0] = 1;
			aufhellen_[i][1] = dunkel_[i][2];
		}
	}
}

void Neopixel_RandomPulse::RP_ProzessAufhellen()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - RP ProzessAufhellen";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	for (byte i = 0; i <= numleds_; i++) {

		if (RP_CheckObMaxHellOderDunkelWertErreicht(i, "aufhellen")) // Leds welche max_hell_zyklen_ Zyklen Hell waren werden in abdunkeln_ gelegt und damit dünkler geschalten.
		{
			aufhellen_[i][0] = 0;
			aufhellen_[i][1] = min_helligkeit_;
			hell_[i][0] = 1;
			hell_[i][1] = 0;
			hell_[i][2] = aufhellen_[i][1];
		}
	}
}

void Neopixel_RandomPulse::RP_ProzessHell()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - RP ProzessHell";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	for (byte i = 0; i <= numleds_; i++) {

		if (RP_CheckObMaxHellOderDunkelZyklusErreicht(i, "hell")) // Leds welche max_hell_zyklen_ Zyklen Hell waren werden in abdunkeln_ gelegt und damit dünkler geschalten.
		{
			hell_[i][0] = 0;
			hell_[i][1] = 0;
			hell_[i][2] = max_helligkeit_;
			abdunkeln_[i][0] = 1;
			abdunkeln_[i][1] = hell_[i][2];
		}
	}
}

void Neopixel_RandomPulse::RP_ProzessAbdunkeln()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - RP ProzessAbdunkeln";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	for (byte i = 0; i <= numleds_; i++) {

		if (RP_CheckObMaxHellOderDunkelWertErreicht(i, "abdunkeln")) // Leds welche max_hell_zyklen_ Zyklen Hell waren werden in abdunkeln_ gelegt und damit dünkler geschalten.
		{
			abdunkeln_[i][0] = 0;
			abdunkeln_[i][1] = max_helligkeit_;
			dunkel_[i][0] = 1;
			dunkel_[i][1] = 0;
			dunkel_[i][2] = abdunkeln_[i][1];
		}
	}
}

// Prüft ob die Zyklusschwelle um das Led dunkel oder Hell zu schalten bereist erreicht ist.
// Parameter: "zeile" übergibt die Zeile welche geprüft wird. Wird in "helldunkel" "hell" übergeben wird auf Hellzyklus geprüft wird "dunkel" übergeben wird auf Dunkelzyklus geprüft.
bool Neopixel_RandomPulse::RP_CheckObMaxHellOderDunkelZyklusErreicht(byte zeile, String helldunkel)
{
	if (helldunkel == "hell")
	{
		if (hell_[zeile][1] >= max_hell_zyklen_ && hell_[zeile][0] == 1) // Leds welche max_hell_zyklen_ Zyklen Hell waren werden in abdunkeln_ gelegt und damit dünkler geschalten.
		{
			return true;
		}
	}
	if (helldunkel == "dunkel")
	{
		if (dunkel_[zeile][1] >= max_dunkel_zyklen_ && dunkel_[zeile][0] == 1) // Leds welche max_dunkel_zyklen_ Zyklen Dunkel waren werden in aufhellen_ gelegt und damit heller geschalten.
		{
			return true;
		}
	}
	return false;
}

bool Neopixel_RandomPulse::RP_CheckObMaxHellOderDunkelWertErreicht(byte zeile, String aufhellabdunkel)
{
	if (aufhellabdunkel == "aufhellen")
	{
		if (aufhellen_[zeile][1] >= max_helligkeit_ && aufhellen_[zeile][0] == 1) // Leds welche max_hell_zyklen_ Zyklen Hell waren werden in abdunkeln_ gelegt und damit dünkler geschalten.
		{
			return true;
		}
	}
	if (aufhellabdunkel == "abdunkeln")
	{
		if (abdunkeln_[zeile][1] <= min_helligkeit_ && abdunkeln_[zeile][0] == 1) // Leds welche max_dunkel_zyklen_ Zyklen Dunkel waren werden in aufhellen_ gelegt und damit heller geschalten.
		{
			return true;
		}
	}
	return false;
}

// Es wird ein Anteil an Leds gewählt welcher zufällig im nächsten Zyklus Heller oder DUnkle rgeschaltenm wird gewählt.
// Der die Konstanten "anteil_leds_zum_abdunkeln_" und "anteil_leds_zum_aufhellen_" stellen den Divisor dar, die Leds welche derzeit Hell oder Dunkel sind stellen den Dividenden dar. 
void Neopixel_RandomPulse::RP_WaehleLedAnteilZumHellOderDunkelSchalten(String helldunkel)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - RP Led Anteil";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	byte ledarray[NUM_LEDS_1] = { 0 };
	byte countLedsWelcheOn = 0;
	byte anteilLeds = 0;
	byte x = 0;
	byte led = 0;

	if (helldunkel == "hell")
	{
		for (byte i = 0; i <= numleds_; i++) {
			if (hell_[i][0] == 1)
			{
				ledarray[countLedsWelcheOn] = i;
				countLedsWelcheOn++;
			}
		}
		anteilLeds = round(countLedsWelcheOn / anteil_leds_zum_abdunkeln_);
		while (x <= anteilLeds)
		{
			led = ledarray[random8(countLedsWelcheOn)];
			hell_[led][1] = max_hell_zyklen_;
			x++;
#ifdef DEBUG
			if (logger_g_->GetLogLevel() >= extremedebug)
			{
				static const char* const buffer PROGMEM = "ledarray: ";
				logger_g_->LnWriteLog(buffer, debug);
				logger_g_->WriteLog(led, debug);
			}
#endif
		}
	}

	if (helldunkel == "dunkel")
	{
		for (byte i = 0; i <= numleds_; i++) {
			if (dunkel_[i][0] == 1)
			{
				ledarray[countLedsWelcheOn] = i;
				countLedsWelcheOn++;
			}
		}
		anteilLeds = round(countLedsWelcheOn / anteil_leds_zum_aufhellen_);

		while (x <= anteilLeds)
		{
			led = ledarray[random8(countLedsWelcheOn)];
			dunkel_[led][1] = max_dunkel_zyklen_;
			x++;
#ifdef DEBUG
			if (logger_g_->GetLogLevel() >= extremedebug)
			{
				static const char* const buffer PROGMEM = "ledarray: ";
				logger_g_->LnWriteLog(buffer, debug);
				logger_g_->WriteLog(led, debug);
			}
#endif
		}
	}
}

// Effekt randomPulse: Lässt jenachdem wieviele leds konfigurioert sind diese in zufälligen Mustern Pulsieren.
// Jedes LED wird also smooth heller und dünkler geschalten aber jedes einzelne Led zufällig.
// Die Funktion arbeitet Zyklisch d.h. Jeder Aufruf der Funktion stellt einen Zyklus dar und die lichter werden um einen Helligkeitsgrad dünkler oder heller geschalten.
void Neopixel_RandomPulse::randomPulse()
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - randomPulse";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	// Prüfe ob erster Aufruf von RP
	if (RP_CheckObErsterAufrufVonRandomPulse())
	{
#ifdef DEBUG
		if (logger_g_->GetLogLevel() >= debug)
		{
			static const char* const buffer PROGMEM = "RP: Erster Aufruf";
			logger_g_->LnWriteLog(buffer, debug);
		}
#endif
		RP_SetzeInitialWerteInArrays();
		erster_aufruf_von_rp_ = false;
	}
	//Dunkler Zyklus
	RP_WaehleLedAnteilZumHellOderDunkelSchalten("dunkel");
	RP_ProzessDunkel();
	//Aufhellen Zyklus
	RP_ProzessAufhellen();
	//Hell Zyklus
	RP_WaehleLedAnteilZumHellOderDunkelSchalten("hell");
	RP_ProzessHell();
	//Abdunkeln Zyklus
	RP_ProzessAbdunkeln();
	//Inkrementiere alle Arrays
	RP_InDekrementiereLEDArrays();
	RP_SetzeBerechneteLichtwerte();
	setAllLikeInputArray(-1);
}