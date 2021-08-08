#include <iostream>
#include <fstream>
#include "home_logger.h"

using namespace std;

logger * logger::log = 0;
logger::logger(const char *tc_vers, const char *fname)
	: numWarnings(0U),
	numErrors(0U),
	numFatals(0U),
	numInfos(0U)
{

	file.open(fname);

	// Write the first lines
	if (file.is_open()) {
		file << "TerraControll Version: " << tc_vers << endl;
		file << "Log file created" << endl << endl;
	}

}

logger::~logger()
{
	if (file.is_open()) {
		file << endl << endl;

		// Report number of errors and warnings
		file << numFatals << " fatals" << endl;
		file << numErrors << " errors" << endl;
		file << numWarnings << " warnings" << endl;
		file << numInfos << " infos" << endl;

		file.close();
	}

}

logger * logger::getInstance()
{
	if (!log)
		log = new logger(VERSION);

	return log;
}

logger &operator <<(logger &logger1, const logger::logType l_type) {

	switch (l_type) {
	case logger::logType::error:
		logger1.file << "[ERROR]: ";
		++logger1.numErrors;
		break;

	case logger::logType::warning:
		logger1.file << "[WARNING]: ";
		++logger1.numWarnings;
		break;

	case logger::logType::fatal:
		logger1.file << "[FATAL]: ";
		++logger1.numFatals;
		break;

	default:
		logger1.file << "[INFO]: ";
		++logger1.numInfos;
		break;
	}

	return logger1;

}

logger &operator <<(logger &logger1, const char *text) {

	logger1.file << text << endl;
	return logger1;

}