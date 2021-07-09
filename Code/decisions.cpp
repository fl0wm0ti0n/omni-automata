#include "decisions.h"
#include "constants.h"

decisions::decisions(t_decision_type t, String n)
	:m_iType(t), m_cName(n)
{
}

decisions::~decisions()
= default;

// TEMPERATUR LICHT
// Licht nach Temperatur muss sich sofort einschalten auch ohne Änderung bei Temperatur aber nur wenn es das erste mal startet also Bewegung erkannt wird.
// Licht muss sofort im korrekten Farbwert starten.

int decisions::colorTemperaturChange(float temp, float hum, logger &log)
{
	log.writeLog("Call - colorTempChange", extremedebug);
	if (CHANGEHUE_AQUA)		{ colorium = 128; }
	if (CHANGEHUE_BLUE)		{ colorium = 160; }
	if (CHANGEHUE_GREEN)	{ colorium = 96; }
	if (CHANGEHUE_YELLOW)	{ colorium = 64; }
	if (CHANGEHUE_ORANGE)	{ colorium = 32; }
	if (CHANGEHUE_RED)		{ colorium = 0; }
	log.writeLog("Set color " + String(colorium), debug);
	return colorium;
}

// Wenn Bewegung "light up" bis das Licht ganz an ist nach einer am Motionsensor eingestellten Zeit geht das licht wieder aus.
// Mainloop und millis unabhängig (alles muss auf diesen Prozess warten)
/*int decisions::LichtKomplettSchalten_SobaldImpuls(bool o_sensor, int o_actor, logger &log)
{
	log.writeLog("Call - LichtKomplettSchalten_SobaldImpuls", extremedebug);

	if (o_sensor == true)
	{
		if (o_actor != 255)
		{
			for (int i = 0; i <= 255; ++i)
			{
				LightStripe_one.setValue(i, Logging_one);
				delay(DEFAULT_LIGHTFDELAY);
				log.writeLog("Licht an - " + String(LightStripe_one.getValue()), debug);
			}
			LightStripe_one.setValue(255, Logging_one);
		}
	}
	else
	{
		if (LightStripe_one.getValue() != 0)
		{

			for (int j = 255; j >= 0; --j)
			{
				LightStripe_one.setValue(j, Logging_one);
				delay(DEFAULT_LIGHTFDELAY);
				log.writeLog("Licht aus - " + String(LightStripe_one.getValue()), debug);
			}
			LightStripe_one.setValue(0, Logging_one);
		}
	}
	return lightcounter;
}*/

// Wenn Bewegung "light up" - sobald keine Bewegung "light down"
// Impuls effect
// Mit Motionsensor justierbar
// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
int decisions::lichtAnSolangeInputImpulsAn(bool o_sensor, logger &log)
{
	log.writeLog("Call - lichtAnSolangeInputImpulsAn", extremedebug);

	if (o_sensor == true)
	{
		if (lightcounter != 255)
		{
			if (lightcounter < 255)
			{
				lightcounter++;
				log.writeLog("Licht an - " + String(lightcounter), debug);
			}
		}
	}
	else
	{
		if (lightcounter != 0)
		{
			if (lightcounter > 0)
			{
				lightcounter--;
				log.writeLog("Licht aus - " + String(lightcounter), debug);
			}
		}
	}
	return lightcounter;
}


// Wenn Bewegung "light up" bis volle Stärke - erst danach "light off"
// NICHT mit Motionsensor justierbar
// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
/*int decisions::LqichtAnSolangeInputImpulsAn_AusErlaubtNach255(bool o_sensor, int o_actor, logger &log)
{
	log.writeLog("Call - LichtAnSolangeInputImpulsAn_AusErlaubtNach255", extremedebug);

	if (LightStripe_one.getValue() != 255 && lightdoggle == 0)
	{
		if (LightStripe_one.getValue() <= 255 && Motionsensor_one.getValue(Logging_one) == true)
		{
			lightcounter++;
			LightStripe_one.setValue(lightcounter, Logging_one);
			lightdoggle = 0;
			lightswitch = 0;
			log.writeLog("Licht an - " + String(lightcounter), debug);
		}
		else if (lightcounter <= 255 && Motionsensor_one.getValue(Logging_one) == false)
		{
			LightStripe_one.setValue(lightcounter, Logging_one);
			if (lightswitch == 0) { lightcounter++; }
			log.writeLog("Licht an - " + String(lightcounter), debug);
		}
	}
	else
	{
		lightdoggle = 1;
	}

	if (LightStripe_one.getValue() != 0 && lightdoggle == 1 && Motionsensor_one.getValue(Logging_one) == false)
	{
		if (LightStripe_one.getValue() > 0)
		{
			lightcounter--;
			LightStripe_one.setValue(lightcounter, Logging_one);
			lightdoggle = 1;
			lightswitch = 1;
			log.writeLog("Licht aus - " + String(lightcounter), debug);
		}
	}
	else
	{
		lightdoggle = 0;
	}
	return lightcounter;
}*/
	/*
	// Wenn Bewegung "light up" bis das Licht ganz an ist nach einer am Motionsensor eingestellten Zeit geht das licht wieder aus.
	// Mainloop und millis unabhängig (alles muss auf diesen Prozess warten)
	void decisions::LichtKomplettSchalten_SobaldImpuls(bool o_sensor, int o_actor, logger &log)
	{
		log.writeLog("Call - LichtKomplettSchalten_SobaldImpuls", extremedebug);

		if (Motionsensor_one.getValue(Logging_one) == true)
		{
			if (LightStripe_one.getValue() != 255)
			{
				for (int i = 0; i <= 255; ++i)
				{
					LightStripe_one.setValue(i, Logging_one);
					delay(DEFAULT_LIGHTFDELAY);
					log.writeLog("Licht an - " + String(LightStripe_one.getValue()), debug);
				}
				LightStripe_one.setValue(255, Logging_one);
			}
		}
		else
		{
			if (LightStripe_one.getValue() != 0)
			{

				for (int j = 255; j >= 0; --j)
				{
					LightStripe_one.setValue(j, Logging_one);
					delay(DEFAULT_LIGHTFDELAY);
					log.writeLog("Licht aus - " + String(LightStripe_one.getValue()), debug);
				}
				LightStripe_one.setValue(0, Logging_one);
			}
		}
	}

	// Wenn Bewegung "light up" - sobald keine Bewegung "light down"
	// Impuls effect
	// Mit Motionsensor justierbar
	// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
	void decisions::lichtAnSolangeInputImpulsAn(sensor o_sensor, actor o_actor, logger &log)
	{

		log.writeLog("Call - lichtAnSolangeInputImpulsAn", extremedebug);

		if (Motionsensor_one.getValue(Logging_one) == true)
		{
			if (LightStripe_one.getValue() != 255)
			{
				if (LightStripe_one.getValue() <= 255)
				{
					lightcounter++;
					LightStripe_one.setValue(lightcounter, Logging_one);
					log.writeLog("Licht an - " + String(lightcounter), debug);
				}
			}
		}
		else
		{
			if (LightStripe_one.getValue() != 0)
			{
				if (LightStripe_one.getValue() >= 0)
				{
					lightcounter--;
					LightStripe_one.setValue(lightcounter, Logging_one);
					log.writeLog("Licht an - " + String(lightcounter), debug);
				}
			}
		}
	}

	// Wenn Bewegung "light up" bis volle Stärke - erst danach "light off"
	// NICHT mit Motionsensor justierbar
	// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
	void decisions::LichtAnSolangeInputImpulsAn_AusErlaubtNach255(sensor o_sensor, actor o_actor, logger &log)
	{
		log.writeLog("Call - LichtAnSolangeInputImpulsAn_AusErlaubtNach255", extremedebug);

		if (LightStripe_one.getValue() != 255 && lightdoggle == 0)
		{
			if (LightStripe_one.getValue() <= 255 && Motionsensor_one.getValue(log) == true)
			{
				lightcounter++;
				LightStripe_one.setValue(lightcounter, Logging_one);
				lightdoggle = 0;
				lightswitch = 0;
				log.writeLog("Licht an - " + String(lightcounter), debug);
			}
			else if (lightcounter <= 255 && Motionsensor_one.getValue(log) == false)
			{
				LightStripe_one.setValue(lightcounter, Logging_one);
				if (lightswitch == 0) { lightcounter++; }
				log.writeLog("Licht an - " + String(lightcounter), debug);
			}
		}
		else
		{
			lightdoggle = 1;
		}

		if (LightStripe_one.getValue() != 0 && lightdoggle == 1 && Motionsensor_one.getValue(log) == false)
		{
			if (LightStripe_one.getValue() > 0)
			{
				lightcounter--;
				LightStripe_one.setValue(lightcounter, log);
				lightdoggle = 1;
				lightswitch = 1;
				log.writeLog("Licht aus - " + String(lightcounter), debug);
			}
		}
		else
		{
			lightdoggle = 0;
		}*/