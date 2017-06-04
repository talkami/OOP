#pragma once
#include <string>
#include <fstream>

class Logger {
	std::ofstream logFile;
public:
	Logger(){}
	~Logger();	
	void InitLog(std::string& path);
	void logMessage(const std::string& msg);
};