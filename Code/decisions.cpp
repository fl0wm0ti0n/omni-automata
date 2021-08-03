#include "Decisions.h"
#include "constants.h"

Decisions::Decisions(decision_type t, char n[])
	:type_(t), name_(n)
{
#ifdef DEBUG
	static char* const buffer PROGMEM = "Logging1";
	logger_g_ = logger::GetInstance(DEFAULT_LOGLEVEL, DEFAULT_LOGTARGET, buffer);
#endif
}

Decisions::~Decisions()
= default;

// TEMPERATUR LICHT
// Licht nach Temperatur muss sich sofort einschalten auch ohne Änderung bei Temperatur aber nur wenn es das erste mal startet also Bewegung erkannt wird.
// Licht muss sofort im korrekten Farbwert starten.

int Decisions::color_temperatur_change(float temp, float hum)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - colorTempChange";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	if (CHANGEHUE_AQUA)		{ colorium_ = 128; }
	if (CHANGEHUE_BLUE)		{ colorium_ = 160; }
	if (CHANGEHUE_GREEN)	{ colorium_ = 96; }
	if (CHANGEHUE_YELLOW)	{ colorium_ = 64; }
	if (CHANGEHUE_ORANGE)	{ colorium_ = 32; }
	if (CHANGEHUE_RED)		{ colorium_ = 0; }
	return colorium_;
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
int Decisions::licht_an_solange_input_impuls_an(bool o_sensor)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - lichtAnSolangeInputImpulsAn";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	if (o_sensor == true)
	{
		if (lightcounter_ != 255)
		{
			if (lightcounter_ < 255)
			{
				lightcounter_++;
#ifdef DEBUG
				if (logger_g_->GetLogLevel() >= sensordata)
				{
					static const char* const buffer PROGMEM = "Licht an - ";
					logger_g_->LnWriteLog(buffer, sensordata);
					logger_g_->WriteLog(lightcounter_, sensordata);
				}
#endif
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
#ifdef DEBUG
				if (logger_g_->GetLogLevel() >= sensordata)
				{
					static const char* const buffer PROGMEM = "Licht aus - ";
					logger_g_->LnWriteLog(buffer, sensordata);
					logger_g_->WriteLog(lightcounter_, sensordata);
				}
#endif
			}
		}
	}
	return lightcounter_;
}


// Wenn Bewegung "light up" bis volle Stärke - erst danach "light off"
// NICHT mit Motionsensor justierbar
// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
int Decisions::licht_an_solange_input_impuls_an_aus_erlaubt_nach255(bool o_sensor, int o_actor)
{
#ifdef DEBUG
	if (logger_g_->GetLogLevel() >= extremedebug)
	{
		static const char* const buffer PROGMEM = "Call - LichtAnSolangeInputImpulsAn_AusErlaubtNach255";
		logger_g_->LnWriteLog(buffer, extremedebug);
	}
#endif
	if (LightStripe_one.getValue() != 255 && lightdoggle_ == 0)
	{
		if (LightStripe_one.getValue() <= 255 && Motionsensor_one.getValue() == true)
		{
			lightcounter_++;
			LightStripe_one.setValue(lightcounter_);
			lightdoggle_ = 0;
			lightswitch_ = 0;
#ifdef DEBUG
			if (logger_g_->GetLogLevel() >= sensordata)
			{
				static const char* const buffer PROGMEM = "Licht an - ";
				logger_g_->LnWriteLog(buffer, sensordata);
				logger_g_->WriteLog(lightcounter_, sensordata);
			}
#endif
		}
		else if (lightcounter_ <= 255 && Motionsensor_one.getValue() == false)
		{
			LightStripe_one.setValue(lightcounter_);
			if (lightswitch_ == 0) { lightcounter_++; }
#ifdef DEBUG
			if (logger_g_->GetLogLevel() >= sensordata)
			{
				static const char* const buffer PROGMEM = "Licht an - ";
				logger_g_->LnWriteLog(buffer, sensordata);
				logger_g_->WriteLog(lightcounter_, sensordata);
			}
#endif
		}
	}
	else
	{
		lightdoggle_ = 1;
	}

	if (LightStripe_one.getValue() != 0 && lightdoggle_ == 1 && Motionsensor_one.getValue() == false)
	{
		if (LightStripe_one.getValue() > 0)
		{
			lightcounter_--;
			LightStripe_one.setValue(lightcounter_);
			lightdoggle_ = 1;
			lightswitch_ = 1;
#ifdef DEBUG
			if (logger_g_->GetLogLevel() >= sensordata)
			{
				static const char* const buffer PROGMEM = "Licht an - ";
				logger_g_->LnWriteLog(buffer, sensordata);
				logger_g_->WriteLog(lightcounter_, sensordata);
			}
#endif
		}
	}
	else
	{
		lightdoggle_ = 0;
	}
	return lightcounter_;
}
	
	// Wenn Bewegung "light up" bis das Licht ganz an ist nach einer am Motionsensor eingestellten Zeit geht das licht wieder aus.
	// Mainloop und millis unabhängig (alles muss auf diesen Prozess warten)
	//void Decisions::licht_komplett_schalten_sobald_impuls(bool o_sensor, int o_actor)
	//{
	//	log.writeLog("Call - LichtKomplettSchalten_SobaldImpuls", extremedebug);

	//	if (Motionsensor_one.getValue() == true)
	//	{
	//		if (LightStripe_one.getValue() != 255)
	//		{
	//			for (int i = 0; i <= 255; ++i)
	//			{
	//				LightStripe_one.setValue(i);
	//				delay(DEFAULT_LIGHTFDELAY);
	//				log.writeLog("Licht an - " + String(LightStripe_one.getValue()), debug);
	//			}
	//			LightStripe_one.setValue(255);
	//		}
	//	}
	//	else
	//	{
	//		if (LightStripe_one.getValue() != 0)
	//		{

	//			for (int j = 255; j >= 0; --j)
	//			{
	//				LightStripe_one.setValue(j);
	//				delay(DEFAULT_LIGHTFDELAY);
	//				log.writeLog("Licht aus - " + String(LightStripe_one.getValue()), debug);
	//			}
	//			LightStripe_one.setValue(0);
	//		}
	//	}
	//}

	// Wenn Bewegung "light up" - sobald keine Bewegung "light down"
	// Impuls effect
	// Mit Motionsensor justierbar
	// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
	//void Decisions::licht_an_solange_input_impuls_an(Sensor o_sensor, actor o_actor)
	//{

	//	log.writeLog("Call - lichtAnSolangeInputImpulsAn", extremedebug);

	//	if (Motionsensor_one.getValue() == true)
	//	{
	//		if (LightStripe_one.getValue() != 255)
	//		{
	//			if (LightStripe_one.getValue() <= 255)
	//			{
	//				lightcounter_++;
	//				LightStripe_one.setValue(lightcounter_);
	//				log.writeLog("Licht an - " + String(lightcounter_), debug);
	//			}
	//		}
	//	}
	//	else
	//	{
	//		if (LightStripe_one.getValue() != 0)
	//		{
	//			if (LightStripe_one.getValue() >= 0)
	//			{
	//				lightcounter_--;
	//				LightStripe_one.setValue(lightcounter_);
	//				log.writeLog("Licht an - " + String(lightcounter_), debug);
	//			}
	//		}
	//	}
	//}

	// Wenn Bewegung "light up" bis volle Stärke - erst danach "light off"
	// NICHT mit Motionsensor justierbar
	// Mainloop und millis abhängig (nichts muss auf diesen Prozess warten)
	//void Decisions::licht_an_solange_input_impuls_an_aus_erlaubt_nach255(Sensor o_sensor, actor o_actor)
	//{
	//	log.writeLog("Call - LichtAnSolangeInputImpulsAn_AusErlaubtNach255", extremedebug);

	//	if (LightStripe_one.getValue() != 255 && lightdoggle_ == 0)
	//	{
	//		if (LightStripe_one.getValue() <= 255 && Motionsensor_one.getValue() == true)
	//		{
	//			lightcounter_++;
	//			LightStripe_one.setValue(lightcounter_);
	//			lightdoggle_ = 0;
	//			lightswitch_ = 0;
	//			log.writeLog("Licht an - " + String(lightcounter_), debug);
	//		}
	//		else if (lightcounter_ <= 255 && Motionsensor_one.getValue() == false)
	//		{
	//			LightStripe_one.setValue(lightcounter_);
	//			if (lightswitch_ == 0) { lightcounter_++; }
	//			log.writeLog("Licht an - " + String(lightcounter_), debug);
	//		}
	//	}
	//	else
	//	{
	//		lightdoggle_ = 1;
	//	}

	//	if (LightStripe_one.getValue() != 0 && lightdoggle_ == 1 && Motionsensor_one.getValue() == false)
	//	{
	//		if (LightStripe_one.getValue() > 0)
	//		{
	//			lightcounter_--;
	//			LightStripe_one.setValue(lightcounter_);
	//			lightdoggle_ = 1;
	//			lightswitch_ = 1;
	//			log.writeLog("Licht aus - " + String(lightcounter_), debug);
	//		}
	//	}
	//	else
	//	{
	//		lightdoggle_ = 0;
	//	}
	//}