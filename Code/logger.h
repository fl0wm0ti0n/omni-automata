// @file           logger.h
// @author         flow@p0cki.at
// @date           08.2019
// @brief          baseclass of logging

#ifndef _HOME_LOG_h
#define _HOME_LOG_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include	"constants.h""

enum t_log_level
{
	disabled = -1,
	error = 0,
	warning = 1,
	sensordata = 2,
	debug = 3,
	extremedebug = 4,
};

enum t_log_target
{
	serial = 0,
	net = 1,
	archive = 2,
};

class logger
{

private:

	// Variablen des Constructors
	t_log_level		m_iLogLvl_;
	t_log_target	m_iLogTarget_;
	String			m_cName_;

	// Variablen zur Zeitberechnung
	String			sTimestamp;
	String			sSekunde;
	String			sMinute;
	String			sStunde;
	int				iSekunde = 0;
	int				iMinute = 0;
	int				iStunde = 0;

	// Variablen zur Loghochzähulung
	unsigned int	iNumErrors;
	unsigned int	iNumWarnings;
	unsigned int    iNumSensors;
	unsigned int    iNumDebugs;
	unsigned int    iNumExtremedebugs;

	// Weitere Variablen
	String			aEnumlvl[5];
	String			sLogArchive_;
	String			sLogmessage_;

	void handleLog(String time, String text, t_log_level llevel);

public:
	logger(t_log_level t, t_log_target g, String n);		// Constructor
	virtual ~logger();									// Destructor

	void writeLog(String text, t_log_level llevel);
	String getActualTimestamp();
	String getLogArchive(t_log_level llevel);

	void setLoglevel(t_log_level m_iLogLvl_)
	{
		this->m_iLogLvl_ = m_iLogLvl_;
	}

	void setLogTarget(t_log_target m_iLogTarget_)
	{
		this->m_iLogTarget_ = m_iLogTarget_;
	}

	t_log_level getLogLevel()
	{
		return m_iLogLvl_;
	}

	t_log_target getLogTarget()
	{
		return m_iLogTarget_;
	}

	String getName()
	{
		return m_cName_;
	}
};
#endif