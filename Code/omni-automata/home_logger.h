/*
* @file           logger.h
* @author         flow@p0cki.at
* @date           04.2016
* @brief          class for all error channels.
*/

#ifndef _HOME_LOGGER_h
#define _HOME_LOGGER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <QTextStream>
#include <QString>

#define VERSION "1.0"
#define LOG(l,m) \
{ \
	QString __debug_string__; \
	QTextStream __debug_stream__(&__debug_string__); \
	__debug_stream__ << m; \
	__debug_stream__.flush(); \
	*logger::getInstance() << logger::logType::l << __debug_string__.toStdString().c_str(); \
}

using namespace std;

class logger
{
public:
	explicit logger(const char *tc_vers, const char *fname = "tc_log.txt");  //constructor
	virtual ~logger();

	enum logType {
		fatal,          //Log fatal errors
		error,          //Log errors
		warning,        //Log warnings
		info,           //Log info messages
	};

	static logger * getInstance();

	// Overload << operator using log type
	friend logger &operator <<(logger &logger1, const logType l_type);


	// Overload << operator using C style strings
	// No need for std::string objects here
	friend logger &operator <<(logger &logger1, const char *text);

private:
	std::ofstream           file;
	static logger *			log;
	unsigned int            numWarnings;
	unsigned int            numErrors;
	unsigned int            numFatals;
	unsigned int            numInfos;
};

//logger &operator <<(logger &logger1, const logger::logType l_type);

//logger &operator <<(logger &logger1, const char *text);
