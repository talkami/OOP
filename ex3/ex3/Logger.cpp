#include "Logger.h"
#include <ctime>
#include <iostream>
#include <iomanip>

void Logger::InitLog(std::string& path) {
	this->logFile.open(path);
}

Logger::~Logger() {
	if (this->logFile.is_open()){
		this->logFile.close();
	}
}

void Logger::logMessage(const std::string& msg) {
	if (this->logFile.is_open()){
		time_t now = time(0);
		tm currTime;
		localtime_s(&currTime, &now);
		this->logFile << std::setfill('0') << std::setw(2) << currTime.tm_mday << "/";
		this->logFile << std::setfill('0') << std::setw(2) << 1 + currTime.tm_mon << "/";
		this->logFile << 1900 + currTime.tm_year << " ";
		this->logFile << std::setfill('0') << std::setw(2) << currTime.tm_hour << ":";
		this->logFile << std::setfill('0') << std::setw(2) << currTime.tm_min << ":";
		this->logFile << std::setfill('0') << std::setw(2) << currTime.tm_sec << " - ";
		this->logFile << msg << "\n";
	}
}