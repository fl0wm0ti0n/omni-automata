// @file      analogIn.cpp
// @author    flow@p0cki.net
// @date      08.2019
// @brief     baseclass of logging

#include "logger.h"
#include "Streaming.h"

logger::logger(t_log_level t, t_log_target g, String n)
	:m_iLogLvl_(t), m_iLogTarget_(g), m_cName_(n)
{
	switch (m_iLogTarget_)
	{
	case 0:
		Serial.begin(DEFAULT_BAUTRATE);
			break;
	case 1:
		 // Netzwerk init - noch nicht implementiert!
		break;
	case 2:
		// Archiv init - noch nicht implementiert!
		break;
	default:
		break;
	}

	// inizialisiere Array für Loglevel Ausgabe
	aEnumlvl[0] = "error";
	aEnumlvl[1] = "warni";
	aEnumlvl[2] = "senso";
	aEnumlvl[3] = "debug";
	aEnumlvl[4] = "exdeb";
}

logger::~logger()
= default;

void logger::writeLog(String text, t_log_level llevel)
{
	if (getLogLevel() != disabled)
	{
	handleLog(getActualTimestamp(), text, llevel);
	}
}

String logger::getActualTimestamp()
{
	iSekunde = millis() / 1000;
	if (iSekunde >= 3600)
	{
		iStunde = 0;
		while (iSekunde >= 3600)
		{
			iStunde++;
			iSekunde = iSekunde - 3600;
		}
	}

	if (iSekunde >= 60)
	{
		iMinute = 0;
		while (iSekunde >= 60)
		{
			iMinute++;
			iSekunde = iSekunde - 60;
		}
	}

	sStunde = String(iStunde);
	sMinute = String(iMinute);
	sSekunde = String(iSekunde);

	if (sStunde.length()	== 1) { sStunde		= "0" + sStunde; }
	if (sMinute.length()	== 1) { sMinute		= "0" + sMinute; }
	if (sSekunde.length()	== 1) { sSekunde	= "0" + sSekunde; }

	sTimestamp = sStunde + ":" + sMinute + ":" + sSekunde;

	return sTimestamp;
}

String logger::getLogArchive(t_log_level llevel)
{
	String output;
	if (getLogLevel() != disabled)
	{
		if (m_iLogTarget_ == archive)
		{
			if (m_iLogLvl_ = llevel)
			{
				//noch nicht implementiert!
				output = "Funktion wurde noch nicht implementiert und benötigt ein Hardwaremodul!";
			}
		}
		else
		{
			output = "Das Archivieren der Protokolle ist deaktiviert!";
		}
		output = "Das Logging wurde deaktiviert!";
	}
	return output;
}

void logger::handleLog(String time, String text, t_log_level llevel)
{
	if (m_iLogLvl_ >= llevel)
	{
		switch (m_iLogTarget_)
		{
		case 0:
			//Serial.println(String(time) + " : " + String(aEnumlvl[llevel]) + " : " + String(text));
			/*Serial.print(String(time));
			Serial.print(" : ");
			Serial.print(String(aEnumlvl[llevel]));
			Serial.print(" : ");
			Serial.println(String(text));*/
			Serial << time << " : " << aEnumlvl[llevel] << " : " << text << endl;
			break;
		case 1:
			// Netzwerk Stream - noch nicht implementiert!
			break;
		case 2:
			// Archivdata - noch nicht implementiert!
			break;
		default:
			//Serial.println(String(time) + " : " + String(aEnumlvl[llevel]) + " : " + String(text));
			Serial << time << " : " << aEnumlvl[llevel] << " : " << text << endl;
			break;
		}
	}
}